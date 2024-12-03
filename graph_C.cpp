#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include "log.h"

using namespace std;


class GraphC {
public:
  static map<string, int> datesMap;

  static void generateGraph() {
    for (auto const &log : Logs::logs) {
			for (Activity activity : log.activities) {
        time_t current_time = activity.date;

        // Convert time_t to struct tm
        struct tm *local_time = localtime(&current_time);

        // Extract day, month, and year
        string day = to_string(local_time->tm_mday);
        string month = to_string(local_time->tm_mon + 1); // tm_mon is 0-based, so add 1
        string year = to_string(local_time->tm_year + 1900); // tm_year is years since 1900


        // Insert 0s at the beginning
        if (day.length() < 2) {
            day.insert(0, 1, '0');
        }

        if (month.length() < 2) {
          month.insert(0, 1, '0');
        }

        string date = month + "/" + day;

				datesMap[date] += activity.minutes;
			}
		}

    drawGraph();
  };

  static void drawGraph() {
    int min = 0;
    int max = 0;
    int scale = 40;

    // scale = 40

    // find max minutes
    for (auto const& [key, val] : datesMap) {
        if (max < val) {
          max = val;
        }
    }

    int interval = max / scale;


    for (int i = 0; i < scale; i++) {
      int currentValue = max - interval * i;
      cout << setw(5) << currentValue << "|";

      for (auto const& [key, val] : datesMap) {
        if (val > (currentValue - interval)) {
          cout << "##### ";
        } else {
          cout << "      ";
        }
      }

      cout << endl;
    }


    // DRAW X-AXIS
    cout << "      ";

    for (auto const& [key, val] : datesMap) {
      cout << "______";
    }

    cout << endl;

    cout << "      ";

    for (auto const& [key, val] : datesMap) {
      cout << key << "|";
    }

    cout << endl;

  }
};

map<string, int> GraphC::datesMap;
