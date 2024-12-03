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

        // These are the headers for the report
        vector<string> headers = {"Day of the Week", "Total Team Minutes"};
        reportData.push_back(headers);

        // Map to store total minutes per day
        map<string, int> weeklyTotals;

        // Helps Process each log
        for (const auto &log : Logs::logs) {
            metadata.people.push_back(getFullName(log.firstName, log.lastName));

            for (const auto &activity : log.activities) {
                if (activity.date.empty()) {
                    cerr << "Warning: Skipping activity with empty date." << endl;
                    continue;
                }

                try {
                    string dayOfWeek = getDayOfWeek(activity.date);
                    weeklyTotals[dayOfWeek] += activity.minutes;
                } catch (const exception &e) {
                    cerr << "Error processing date " << activity.date << ": " << e.what() << endl;
                    continue;
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

    static string getDayOfWeek(const string &date) {
        if (date.empty()) {
            throw runtime_error("Date is empty.");
        }

        // Parse the date (assumes format "YYYY-MM-DD")
        int year, month, day;
        if (sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day) != 3) {
            throw runtime_error("Invalid date format. Expected YYYY-MM-DD.");
        }

        // Populate a tm structure
        tm timeStruct = {};
        timeStruct.tm_year = year - 1900; // Years since 1900
        timeStruct.tm_mon = month - 1;    // Months are zero-based
        timeStruct.tm_mday = day;

        // Convert to time_t to get the day of the week
        if (mktime(&timeStruct) == -1) {
            throw runtime_error("Failed to convert date to day of the week.");
        }

        // Days of the week
        static const string days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        return days[timeStruct.tm_wday];
    }
};

// Define static members
vector<vector<string>> Report4::reportData;
ReportMetadata Report4::metadata;

