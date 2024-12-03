#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <iostream>
#include "log.h"
#include "report.h"

// using namespace std;

class Report1 {
public:
    static vector<vector<string>> reportData;
    static ReportMetadata metadata;

    static void generateReport() {
        if (Logs::logs.empty()) {
            throw runtime_error("Error: No logs available to generate the report.");
        }

        metadata.filename = "PhaseThreeReport1";
        metadata.title = "Report 1";
        metadata.explanation = "This report lists each name and the total number of minutes entered into their time log.";
        metadata.classId = Logs::logs[0].classId;

        vector<string> headers = {"Name", "Total Minutes Logged"};
        reportData.push_back(headers);

        map<string, int> memberMinutes;

        for (const auto &log : Logs::logs) {
            string fullName = getFullName(log.firstName, log.lastName);
            metadata.people.push_back(fullName);

            if (log.activities.empty()) {
                cout << "Warning: No activities found for " << fullName << endl;
                continue;
            }

            for (const auto &activity : log.activities) {
                string identifier = log.classId + " - " + fullName; // Unique identifier
                memberMinutes[identifier] += activity.minutes;
            }
        }

        for (const auto &entry : memberMinutes) {
            reportData.push_back({entry.first, to_string(entry.second)});
        }

        // Build the report using the shared Report class
        Report::buildReport(reportData, metadata);
    }

    static string getFullName(const string &firstName, const string &lastName) {
        return firstName + " " + lastName;
    }
};

// Define static members
vector<vector<string>> Report1::reportData;
ReportMetadata Report1::metadata;



