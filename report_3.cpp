#include <map>
#include <string>
#include <vector>
#include "log.h"
#include "report.h"
//Includes for the Graph_B work around
#include <iostream>
#include <fstream>
#include <deque>
//End includes for the Graph_B work around
using namespace std;

class Report3 {
public:
	static vector<char> codes;
	static vector<vector<string>> reportData;
	static ReportMetadata metadata;

  static void generateReport() {
    metadata.filename = "PhaseThreeReport3";
    metadata.title = "Report 3";
    metadata.explanation = "This report shows how many minutes were spent by each team member on each of the activity codes.";
    metadata.classId = Logs::logs[0].classId;

		vector<string> headers = {"Names/Activity Code"};

		for (char code : codes) {
			headers.push_back(string() + code);
		}

		reportData.push_back(headers);
		
		for (auto &log : Logs::logs) {
			metadata.people.push_back(getFullName(log.firstName, log.lastName));
			map<char, int> aggregatedActivities = aggregateActivities(log);

			vector<string> userData = {getFullName(log.firstName, log.lastName)};

			for (auto const &activity : aggregatedActivities) {
				userData.push_back(to_string(activity.second));
			}

			reportData.push_back(userData);
		}
		//GRAPH_B CSV FILE FUNCTION
		//Justin
		//This code is a bit of a hack on my part, I just needed a
		//PhaseThreeReportThree.csv file to be created in order for
		//Graph_B To work so I included it in here since 
		//this has the relevant informaiton
		ofstream PhaseThreeReportThreeCsv("PhaseThreeReportThree.csv", ios_base::out);
		deque<string> names;
		for(string name : metadata.people){
			names.push_back(name);
		}
		for( char c : {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D'} ){
		PhaseThreeReportThreeCsv << c + ',';
		}
		PhaseThreeReportThreeCsv << "\n";
		for(vector<string> row : reportData){
			PhaseThreeReportThreeCsv << names.front() + ',';
			names.pop_front();
			for(string num : row){
				PhaseThreeReportThreeCsv << num + ',';
			}
			PhaseThreeReportThreeCsv << "\n";
		}
		PhaseThreeReportThreeCsv.close();
		//END GRAPH_B CSV FILE FUNCTION
		Report::buildReport(reportData, metadata);
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
ReportMetadata Report3::metadata;
