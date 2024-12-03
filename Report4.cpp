#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include "log.h"
#include "report.h"

using namespace std;

class Report4 {
public:
    static vector<vector<string>> reportData;
    static ReportMetadata metadata;

    static void generateReport() {
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
                string dayOfWeek = getDayOfWeek(activity.date); // Function to get the day
                weeklyTotals[dayOfWeek] += activity.minutes;
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
        // Replace this with actual date-to-day mapping logic
        static const map<int, string> days = {
            {0, "Sunday"}, {1, "Monday"}, {2, "Tuesday"},
            {3, "Wednesday"}, {4, "Thursday"},
            {5, "Friday"}, {6, "Saturday"}
        };
        return days.at(rand() % 7); // Dummy logic for now
    }
};

// Define static members
vector<vector<string>> Report4::reportData;
ReportMetadata Report4::metadata;



