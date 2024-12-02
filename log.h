#ifndef LOG_H
#define LOG_H

#include <string>
#include <vector>
#include <ctime> // For DateTime representation
using namespace std;

// Define the Activity structure
struct Activity {
  char code;
  time_t date;    // Using time_t to represent DateTime
  time_t minutes; // Duration
  time_t startTime; // Time the activity started
  time_t endTime; // Time the activity ended
  int numberOfParticipants; // Number of participants (default = 1)
};

// Define the Log class
class Log {
public:
  // Member variables
  string classId;
  string firstName;
  string lastName;
  string name;
  vector<Activity> activities; // Using std::vector for the list of activities

  // Constructor (optional)
  Log(const string&);

  void setClassId(const string&);
  void setFirstName(const string&);
  void setLastName(const string&);

  // Add activity method (optional)
  void addActivity(Activity);
};

class Logs {
public:
  static vector<Log> logs; // Using std::vector for the list of logs
  static void addLog(Log);
};

vector<Log> Logs::logs;

#endif
