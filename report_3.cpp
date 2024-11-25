#include <map>
#include <string>
#include <vector>
#include "log.h"
#include "report.h"

using namespace std;

class Report3 {
public:
	static vector<char> codes;
	static vector<vector<string>> reportData;

  static void generateReport() {
		vector<string> headers = {"Names/Activity Code"};

		for (char code : codes) {
			headers.push_back(string() + code);
		}

		reportData.push_back(headers);
		
		for (auto &log : Logs::logs) {
			map<char, int> aggregatedActivities = aggregateActivities(log);

			vector<string> userData = {getFullName(log.firstName, log.lastName)};

			for (auto const &activity : aggregatedActivities) {
				userData.push_back(to_string(activity.second));
			}

			reportData.push_back(userData);
		}

		Report::buildReport(reportData, "PhaseThreeReport3");
	}


	static map<char, int> aggregateActivities(Log log) {
			map<char, int> activityMap;

			for (char code : codes) {
				activityMap.insert({code, 0});
			}

			for (Activity activity : log.activities) {
				activityMap[activity.code] += activity.minutes;
			}
			
			return activityMap;
	}

	static string getFullName(string firstName, string lastName) {
		return firstName + " " + lastName;
	}
};

vector<vector<string>> Report3::reportData;

vector<char> Report3::codes = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D'};
