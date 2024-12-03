/*
 * GroupNumber: 1
 * People working on the feature: Keewon Owens
 * Class: CS 4500
 * Date: 11/30/2024
*/

#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <stdexcept>
#include "log.h"
#include "report.h"

using namespace std;

/**
 * Generates a table showing how many minutes were spent by each team member on each of the activity codes.
 */
class Report4 {
public:
    static vector<vector<string>> reportData;
    static ReportMetadata metadata;

    static void generateReport() {
        if (Logs::logs.empty()) {
            throw runtime_error("No logs available to generate the report.");
        }

        metadata.filename = "PhaseThreeReport4";
        metadata.title = "Report 4";
        metadata.explanation = "This report shows total team minutes for each day of the week.";
        metadata.classId = Logs::logs[0].classId;

        // Headers for the report
        vector<string> headers = {"Day of the Week", "Total Team Minutes"};
        reportData.push_back(headers);

        // Map to store total minutes per day
        map<string, int> weeklyTotals;

        // Process each log
        for (const auto &log : Logs::logs) {
            metadata.people.push_back(getFullName(log.firstName, log.lastName));

            for (const auto &activity : log.activities) {
                if (activity.date == 0) { // Check for invalid time_t value
                    cerr << "Warning: Skipping activity with invalid date." << endl;
                    continue;
                }

                try {
                    string dayOfWeek = getDayOfWeek(activity.date); // Use updated getDayOfWeek
                    weeklyTotals[dayOfWeek] += activity.minutes;
                } catch (const exception &e) {
                    cerr << "Error processing activity date: " << e.what() << endl;
                    continue; // Skip invalid dates
                }
            }
        }

        // Populate the report data
        for (const auto &entry : weeklyTotals) {
            reportData.push_back({entry.first, to_string(entry.second)});
        }

        // Build the report using the shared Report class
        Report::buildReport(reportData, metadata);
    }

    static string getFullName(const string &firstName, const string &lastName) {
        return firstName + " " + lastName;
    }

    static string getDayOfWeek(const time_t &timestamp) {
        // Convert time_t to a tm structure using localtime
        tm *timeStruct = localtime(&timestamp);
        if (timeStruct == nullptr) {
            throw runtime_error("Failed to convert time_t to tm structure.");
        }

        // Days of the week
        static const string days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        return days[timeStruct->tm_wday]; // Return the day of the week
    }
};

// Define static members
vector<vector<string>> Report4::reportData;
ReportMetadata Report4::metadata;



