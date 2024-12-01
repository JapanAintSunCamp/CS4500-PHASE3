#include <map>
#include <string>
#include <vector>
#include "log.h"
#include "report.h"

using namespace std;

class Report5 {
public:
  static map<char, int> codesMap;
  static vector<vector<string>> reportData;
  static ReportMetadata metadata;

  static void generateReport() {
    metadata.filename = "PhaseThreeReport5";
    metadata.title = "Report 5";
    metadata.explanation = "This report displays a list of all meetings performed by the team members.";
    metadata.classId = Logs::logs[0].classId;

    vector<string> headers = {"Activity Code", "Minutes Spent By All Team Members"};
    reportData.push_back(headers);

		for (auto &log : Logs::logs) {
      metadata.people.push_back(getFullName(log.firstName, log.lastName));

			for (Activity activity : log.activities) {
				codesMap[activity.code] += activity.minutes;
			}
		}

    for (auto const &codeAggregate : codesMap) {
      reportData.push_back({string() + codeAggregate.first, to_string(codeAggregate.second)});
    }

    Report::buildReport(reportData, metadata);
  }

  static string getFullName(string firstName, string lastName) {
		return firstName + " " + lastName;
	}
};

vector<vector<string>> Report5::reportData;

map<char, int> Report5::codesMap = {
  {'0', 0},
  {'1', 0},
  {'2', 0},
  {'3', 0},
  {'4', 0},
  {'5', 0},
  {'6', 0},
  {'7', 0},
  {'8', 0},
  {'9', 0},
  {'A', 0},
  {'B', 0},
  {'C', 0},
  {'D', 0}
};
ReportMetadata Report5::metadata;
