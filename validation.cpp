#include <string>
#include <vector>
#include <regex>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

#include "log.h"

using namespace std;

struct DateTime {
	int year;
	int month;
	int day;
	int hour;
	int minute;
};

struct Error {
	string message;
	int line;
};


class Validator {
public:
	static void validateFiles() {
		collectLogFiles();

		for (auto &log : Logs::logs) {
			try {
				validateFile(log);
			} catch(const Error &error) {
				throw string("Error [" + log.name + " Line " + to_string(error.line) + "]: " + error.message);
			}
		}
	}

private:
	/**
	 * Searches in the current directory for log files and throws an error if none, only one, or more than ten are found
	 * Also throws an error if a file is found with the same name
	 *
	 * Populates the list of Logs
	 *
	 * Sources for implementation:
	 * https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
	 */
	static void collectLogFiles() {
		regex pattern("^[a-zA-Z]+Log\\.csv$", regex_constants::icase);

	    for (const auto & entry : filesystem::directory_iterator(filesystem::current_path())) {
	    	string fileName = entry.path().filename().string();

	    	if (regex_search(fileName, pattern)) {
			    for (auto &log : Logs::logs) {
			    	if (log.name == fileName) {
			    		throw string("[ERROR] Duplicate file name found: " + fileName);
			    	}
			    }

					Logs::addLog(Log(fileName));
	    	}
	    }

		if (Logs::logs.empty()) {
			throw string("[ERROR] No log files found. Please ensure there are at least two time log files in the program's directory");
		}

		if (Logs::logs.size() == 1) {
			throw string("[ERROR] Only one log file found. Please ensure there are at least two time log files in the program's directory");
		}

		if (Logs::logs.size() > 10) {
			throw string("[ERROR] More than ten log files found. Please ensure there are no more than ten log files in the program's directory");
		}
	}

	/**
	 *  Validates the name and class ID rows of the file and subsequent log entries, if any exist
	 *
	 *  Parameter Log - the current log being validated
	 */
	static void validateFile(Log &log) {
		ifstream stringFile(log.name);
		string line;

		if (stringFile.fail()) {
			throw string("[ERROR] Unable To Open Log File: " + log.name);
		}

		if (getline(stringFile, line)) {
			regex pattern("^([A-Z][a-z]*),([A-Z][a-z]*)[\\S\\s]*");
			smatch match;

			if (regex_match(line, match, pattern)) {
				string firstName = match[2];
				string lastName = match[1];

				// checks that this name does not appear previously
				for (auto &previousLog : Logs::logs) {
					if (previousLog.firstName == firstName && previousLog.lastName == lastName) {
						throw string("[ERROR] More than one file found with the same first and last names: " + previousLog.name + " and " + log.name);
					}
				}

				log.setFirstName(firstName);
				log.setLastName(lastName);
			} else {
				throw Error {"Invalid Name", 1};
			}
		} else {
			throw Error {"Name Row Is Missing", 1};
		}

		if (getline(stringFile, line)) {
			// matches one or more capital characters followed by one or more white spaces followed by one or more numbers
			regex pattern("^([A-Z]+\\s+[0-9]+)[\\S\\s]*");
			smatch match;

			if (regex_match(line, match, pattern)) {
				string classId = match[1];

				// checks that all class IDs are the same
				// assume the first log file contains the canonical class ID and then check every other file against it
				if (Logs::logs.size() > 0 && !Logs::logs[0].classId.empty() && Logs::logs[0].classId != classId) {
					throw string("[ERROR] Mismatched class IDs found in " + Logs::logs[0].name + " (" + Logs::logs[0].classId + ") and " + log.name + " (" + classId + ")");
				}

				log.setClassId(classId);
			} else {
				throw Error {"Invalid Class ID", 2};
			}
		} else {
			throw Error {"Class ID Row Is Missing", 2};
		}

		int lineNumber = 3;

		while (getline(stringFile, line)) {
			try {
				validateRow(line, log);
			} catch(Error &error) {
				error.line = lineNumber;
				stringFile.close();
				throw error;
			}

			lineNumber++;
		}

		stringFile.close();
	}

	/**
	 *  Validates an entry row (rows 3-X of the time log file)
	 *
	 *  Parameter row - the comma-delimited row of the CSV file
	 *  Parameter log - the log currently being validated
	 */
	static void validateRow(string row, Log &log) {
		stringstream stream(row);
		string token;

		DateTime start;
		DateTime end;

		Activity activity;

		// VALIDATE DATE
		if (getline(stream, token, ',')) {
			validateDate(token, start, end);
		} else {
			throw Error {"Missing Date Column"};
		}

		// VALIDATE START TIME
		if (getline(stream, token, ',')) {
			validateTime(token, "Start Time: ", start);
		} else {
			throw Error {"Missing Start Time Column"};
		}

		// VALIDATE END TIME
		if (getline(stream, token, ',')) {
			validateTime(token, "End Time: ", end);
		} else {
			throw Error {"Missing End Time Column"};
		}

		// VALIDATE END TIME IS IN THE PAST
		// Note: we only need to validate the end time because if the end time is in the past
		// and the start time is in the future, that means the start time is after the end
		// time and we will receive a different error later
		validateEndTime(end);

		// VALIDATE START AND END TIMES
		activity.minutes = validateStartAndEndTimes(start, end);
		tm startTm = convertToCTime(start);
		activity.date =  mktime(&startTm);

		// VALIDATE NUMBER OF PARTICIPANTS
		if (getline(stream, token, ',')) {
			validateNumberOfParticipants(token);
			activity.numberOfParticipants = stoi(token);
		} else {
			throw Error {"Missing Activity Code Column"};
		}

		bool isActivityNoteRequired;

		// VALIDATE ACTIVITY CODE
		if (getline(stream, token, ',')) {
			char code = validateActivityCode(token);
			isActivityNoteRequired = code == 'D';
			activity.code = code;
		} else {
			throw Error {"Missing Participants Number Column"};
		}

		// VALIDATE ACTIVITY NOTE
		if (getline(stream, token)) {
			validateActivityNote(token);
		} else if (isActivityNoteRequired) {
			throw Error {"Missing Activity Note Column For Activity D"};
		}

		log.addActivity(activity);
	}

	/**
	 * Validates the date and time using a regular expression
	 *
	 * Parameters date - the date that appears in the first column of an entry
	 * Parameters start - a dereferenced pointer where the components of the date (if valid will be stored)
	 * Parameters end - a dereferenced pointer where the components of the date (if valid will be stored)
	 *
	 */
	static void validateDate(const string date, DateTime &start, DateTime &end) {
		regex pattern("^([0-9]{2})/([0-9]{2})/([0-9]{4})$");
		smatch match;

		if (!regex_match(date, match, pattern)) {
			throw Error {"Invalid Date Format."};
		}

		int month = stoi(match[1]);
		int day = stoi(match[2]);
		int year = stoi(match[3]);

		if (!isValidMonth(month)) {
			throw Error {"Invalid Month."};
		}

		if (!isValidDay(day)) {
			throw Error {"Invalid Day."};
		}

		if (!isValidYear(year)) {
			throw Error {"Invalid Year."};
		}

		start.month = end.month = month;
		start.day = end.day = day;
		start.year = end.year = year;
	}

	/**
	 * Validates the start and end times using a regular expression
	 *
	 * Parameters time - the time that appears in the second and third columns of the entry
	 * Prefix string - the type of date (start or end)
	 * Parameters dateTime - a dereferenced pointer where the components of the time (if valid) will be stored
	 *
	 */
	static void validateTime(const string time, const string prefix, DateTime &dateTime) {
		regex pattern("^([0-9]{2}):([0-9]{2})$");
		smatch match;

		if (!regex_match(time, match, pattern)) {
			throw Error {prefix + "Invalid Time Format."};
		}

	    int hour = stoi(match[1]);
	    int minute = stoi(match[2]);

	    if (!isValidHour(hour)) {
	    	throw Error {prefix + "Invalid Hour."};
	    }

	    if (!isValidMinute(minute)) {
	    	throw Error {prefix + "Invalid Minute."};
	    }

	    dateTime.hour = hour;
	    dateTime.minute = minute;
	}

	/**
	 * Validates that the end time is not in the future
	 *
	 * Parameter end - the end DateTime for an activity
	 */
	static void validateEndTime(DateTime end) {
		tm then_tm = convertToCTime(end);

		time_t then = mktime(&then_tm);
		time_t now = time(nullptr);

		if (difftime(then, now) / 60 > 0) {
			throw Error {"End Date Is In The Future"};
		}
	}

	/**
	 * Validates the start and end times in conjunction
	 *
	 * Parameter start - the start DateTime for an activity
	 * Parameter end - the end DateTime for an activity
	 */
	static double validateStartAndEndTimes(DateTime start, DateTime end) {
		double difference = getTimeDiff(start, end);

		if (difference < 0) {
			throw Error {"Start Time Is Later Than End Time"};
		}

		if (difference == 0) {
			throw Error {"Start Time And End Time Are The Same"};
		}

		return difference;
	}

	/**
	 * Validates the number of participants for an activity
	 *
	 * Parameter numberOfParticipants - the number in the fourth column of the entry
	 *
	 */
	static void validateNumberOfParticipants(const string numberOfParticipants) {

		regex pattern("^(-?[0-9]+)$");
		smatch match;

		if (!regex_match(numberOfParticipants, match, pattern)) {
			throw Error {"Number Of Participants Is Not An Integer Number."};
		}

		int participants = stoi(match[1]);

		if (participants < 1) {
			throw Error {"Number Of Participants Is Less Than One"};
		}

		if (participants > 50) {
			throw Error {"Number Of Participants Is Greater Than Fifty"};
		}
	}

	/**
	 * Validates the activity code
	 *
	 * Parameter activityCode - the hexadecimal value found in the fifth column of the entry
	 *
	 * Returns the activity code as a char type (used to validate the activity note)
	 */
	static char validateActivityCode(const string activityCode) {
		regex pattern("^([0-9ABCD])$");
		smatch match;

		if (!regex_match(activityCode, match, pattern)) {
			throw Error {"Invalid Activity Code."};
		}

		return activityCode[0];
	}

	/**
	 *  Validates the activity note for an activity
	 *
	 *  Parameter activityNote - the note found in the sixth column of the entry
	 */
	static void validateActivityNote(const string activityNote) {
		if (activityNote.length() > 80) {
			throw Error {"Activity Note Exceeds 80 Characters"};
		}

		if (activityNote.find(',') != string::npos) {
			throw Error {"Activity Note Contains Illegal Comma Character"};
		}
	}

	/**
	 * A rudimentary check for a valid year
	 *
	 * Parameter year - an integer representing the year
	 *
	 * Returns true if the year is valid, false otherwise
	 */
	static bool isValidYear(int year) {
		return year >= 0;
	}

	/**
	 * A check for a valid month
	 *
	 * Parameter month - an integer representing the month
	 *
	 * Returns true if the month is valid, false otherwise
	 */
	static bool isValidMonth(int month) {
		return month > 0 && month < 13;
	}

	/**
	 * A check for a valid day of the month
	 *
	 * Parameter day - an integer representing the day
	 *
	 * Returns true if the day is valid, false otherwise
	 */
	static bool isValidDay(int day) {
		return day > 0 && day < 32;
	}

	/**
	 * A check for a valid minute
	 *
	 * Parameter minute - an integer representing the minute
	 *
	 * Returns true if the minute is valid, false otherwise
	 */
	static bool isValidMinute(int minute) {
		return minute >= 0 && minute < 60;
	}

	/**
	 * A check for a valid hour
	 *
	 * Parameter hour - an integer representing the hour
	 *
	 * Returns true if the hour is valid, false otherwise
	 */
	static bool isValidHour(int hour) {
		return hour >= 0 && hour < 25;
	}

	/**
	 * Converts a DateTime structure to C time
	 *
	 * Parameter DateTime
	 *
	 * Return tm
	 */
	static tm convertToCTime(DateTime dateTime) {
		return {
				0,
				dateTime.minute,
				dateTime.hour,
				dateTime.day,
				dateTime.month - 1,
				dateTime.year - 1900,
		};
	}

	/**
	 * Uses the internal C++ tm structure to calculate the difference in hours between two dates
	 *
	 * Parameter startDateTime - a DateTime structure containing the start date and time of an activity
	 * Parameter endDateTime - a DateTime structure containing the end date and time of an activity
	 *
	 * Sources:
	 * https://stackoverflow.com/questions/9987562/determining-the-difference-between-dates
	 */
	static double getTimeDiff(DateTime startDateTime, DateTime endDateTime) {
		tm start = convertToCTime(startDateTime);
		tm end = convertToCTime(endDateTime);

		time_t time1 = mktime(&start);
		time_t time2 = mktime(&end);

		return difftime(time2, time1) / 60;
	}
};
