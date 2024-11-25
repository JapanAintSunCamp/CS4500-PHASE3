#include <iostream>
#include "log.cpp"
#include "description.cpp"
#include "validation.cpp"
#include "report_2.cpp"
#include "report_3.cpp"
#include "report.cpp"

using namespace std;

<<<<<<< HEAD
int main(){
    int foo;
}
=======
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
		Report2::generateReport();
		Report3::generateReport();
	} catch(const string &errorMessage) {
		cout << errorMessage << endl;
	}
}
>>>>>>> refs/remotes/origin/dev
