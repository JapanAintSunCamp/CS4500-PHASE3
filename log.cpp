#include "log.h"
using namespace std;

Log::Log(const string& name) : name(name) {}

void Log::addActivity(Activity activity) {
  activities.push_back(activity);
}

void Log::setClassId(const string& classId) {
  this->classId = classId;
}

void Log::setFirstName(const string& firstName) {
  this->firstName = firstName;
}

void Log::setLastName(const string& lastName) {
  this->lastName = lastName;
}

void Logs::addLog(Log log) {
	logs.push_back(log);
}
