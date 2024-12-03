#include <map>
#include <iostream>
#include <fstream>
#include <cmath>
#include "log.h"


class GraphA {
public:
  static map<string, int> minutesMap;

  static void generateGraph() {
    for (auto const &log : Logs::logs) {
      string fullName = getFullName(log.firstName, log.lastName);
      minutesMap[fullName] = 0;
    }

    for (auto const &log : Logs::logs) {
      string fullName = getFullName(log.firstName, log.lastName);

      for (auto const &activity : log.activities) {
        minutesMap[fullName] += activity.minutes;
      }
    }

    drawChart();
  }

  static void drawChart() {
    int yAxisLabelWidth = 0;
    int maxMinutes = 0;

    for (const auto& [name, minutes] : minutesMap) {
      if (yAxisLabelWidth < name.length()) {
        yAxisLabelWidth = name.length();
      }

      if (maxMinutes < minutes) {
        maxMinutes = minutes;
      }
    }

    maxMinutes = findMax(maxMinutes);

    for (const auto& [name, minutes] : minutesMap) {
        cout << setw(yAxisLabelWidth) << " " << "|";
        cout << endl;
        cout << setw(yAxisLabelWidth) << " " << "|";
        int num_hashes = ceil((minutes * 100) / (float) maxMinutes);
        for (int j = 0; j < num_hashes; ++j) {
            cout << "#";
        }
        cout << endl;
        cout << setw(yAxisLabelWidth) << name << "|";
        for (int j = 0; j < num_hashes; ++j) {
            cout << "#";
        }
        cout << " (" << minutes << ")";
        cout << endl;
        cout << setw(yAxisLabelWidth) << " " << "|";
        for (int j = 0; j < num_hashes; ++j) {
            cout << "#";
        }
        cout << endl;
    }

    cout << setw(yAxisLabelWidth) << " " << "|";

    for (int i = 0; i <= 100; i++) {
      cout << "_";
    }

    cout << endl << setw(yAxisLabelWidth) << " ";

    int interval = 0;

    for (int i = 0; i <= 100; i += 5) {
      cout << left << setw(5) << interval;
      interval += (maxMinutes * 5 / 100);
    }

    cout << endl << endl;
  }

  static int findMax(int maxMinutes) {
    do {
      if (maxMinutes % 100 == 0) {
        return maxMinutes;
      }
    } while (maxMinutes++);

    return maxMinutes;
  }

  static string getFullName(string firstName, string lastName) {
		return firstName + " " + lastName;
	}
};

map<string, int> GraphA::minutesMap;

