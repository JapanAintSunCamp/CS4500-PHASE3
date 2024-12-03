/**
 * Phase 3 Program, Written In C++
 * Written using Eclipse IDE for C/C++ Developers V4.15.0 (Build ID: 20200313-1211)
 * Developed and Tested on macOS Catalina V10.15.7
 * Tested on macOS Catalina V10.15.7 and Windows 10
 *
 * COMPILATION INSTRUCTIONS:
 *
 * MacOS
 *
 * Use the built-in GNU compiler to compile the program
 * 1) In the MacOS Terminal enter: g++ -std=c++17 driver.cpp
 * 2) The compiled program will be generated and placed into a file named a.out
 * 3) Run the program from the MacOS Terminal by entering: ./a.out
 *
 * Windows
 *
 * You must install a GNU compiler to compile the program
 * 1) Install MinGW-64 for Windows; this will install and place a binary into C:\msys64\ucrt64\bin
 * 2) In the Windows Command Prompt enter: <path to compiler binary> -static driver.cpp
 * 3) The statically-linked compiled program will be generated and placed into a file named a.exe
 * 4) Double-click a.exe to start the program
 *
 * PROGRAMMER(S): Grant Hughes, Samuel Irvin, Vladic Kostin, Justin Macapanpan, Dat Nguyen, Keewon Owens, Rett Swyers
 *
 * DATE: December 3rd, 2024
 *
 * CLASS: CS 4500
 *
 * DESCRIPTION:
 * This program looks for time log files in its directory named XLog.csv (case-insensitive), where X is an alphabetic string.
 * It opens each file and validates them in turn. The validation checks for the presence of a first name and last name on the
 * first row and a class ID on the second row. Subsequent rows are optional, but if they exist, each one is checked to have a
 * valid date, start time, end time, number of people involved in the activity, activity code, and activity note. When the
 * validation is done, the program generates five reports and three graphs; the reports are sent to files named PhaseThreeReport{1-5}.txt
 * and the graphs are sent to the terminal:
 * 	- Report 1: Keewon Owens
 * 	- Report 2: Vladic Kostin
 * 	- Report 3: Vladic Kostin
 * 	- Report 4: Keewon Owens
 * 	- Report 5: Samuel Irvin
 * 	- Graph 1: Justin Macapanpan
 * 	- Graph 2: Dat Nguyen
 * 	- Graph 3: Justin Macapanpan
 * 
 * Included alongside the program are three design documents:
 * 	- Pseudo-Code: Rett Swyers
 * 	- Call Graph: Grant Hughes
 * 	- Level 0/1 Data Flow: Vladic Kostin
 *
 * EXTERNAL FILES/DEPENDENCIES:
 * The program checks for the presence of time log files in its directory that are named XLog.csv and prints a message and halts
 * if no such files are found.
 *
 * SOURCES:
 * Stack Overflow: https://stackoverflow.com/ (exact links are located throughout the code where relevant)
 * CPlusPlus Reference: https://cplusplus.com/reference/ (general reference for the C++ language)
 * Starting Out With C++: From Control Structures Through Objects, Ninth Ed. by Tony Gaddis (general reference for the C++ language)
 *
 */
#include <iostream>
#include "log.cpp"
#include "description.cpp"
#include "validation.cpp"
#include "report_2.cpp"
#include "report_3.cpp"
#include "report_5.cpp"
#include "report.cpp"
#include "graph_A.cpp"
#include "graph_B.cpp"
#include "graph_C.cpp"
#include "Report1.cpp"
#include "Report4.cpp"
using namespace std;

int main() {
	printProgramDescription();

	cout << "Please press ENTER to continue..." << endl;
	cin.get();

	try {
		Validator::validateFiles();
		Report2::generateReport();
		Report3::generateReport();
		GraphA::generateGraph();

		cout << "Please press ENTER to continue..." << endl;
		cin.get();

		//REPORT 3 MUST BE EXECUTED PRIOR TO GRAPH B. GRAPH B IS DEPENDENT ON THE RESLTS OF REPORT 3
		GraphB::generateGraph();

		cout << "Please press ENTER to continue..." << endl;
		cin.get();

		GraphC::generateGraph();

		cout << "Please press ENTER to continue..." << endl;
		cin.get();

		Report1::generateReport();
		Report4::generateReport();
		Report5::generateReport();
		// GraphA::generateGraph();
		// GraphC::generateGraph();
	} catch(const string &errorMessage) {
		cout << errorMessage << endl;
	}
}