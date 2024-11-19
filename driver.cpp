#include <iostream>
#include "log.cpp"
#include "description.cpp"
#include "validation.cpp"

using namespace std;

void printLogFileData() {
	for (auto &log : Logs::logs) {
		cout << "File: " << log.name << endl;
		cout << "ClassID: " << log.classId << endl;
		cout <<  "First Name: " << log.firstName << endl;
		cout <<  "Last Name: " << log.lastName << endl;

		for (auto &activity : log.activities) {
			cout << "\tCode: " << activity.code << ", ";
			cout << "Date: " << activity.date << ", ";;
			cout << "Duration: " << activity.minutes << endl;
		}
	}
}

int main() {
	printProgramDescription();

	cout << "Please press ENTER to continue..." << endl;
	cin.get();

	try {
		Validator::validateFiles();
		printLogFileData();
	} catch(const string &errorMessage) {
		cout << errorMessage << endl;
	}
}
