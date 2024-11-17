#include <iostream>
using namespace std;

void printProgramDescription() {
	cout << "CS 4500 PHASE 3" << endl;
	cout << endl;
	cout << "This program will produce five reports and three graphs summarizing data from multiple (no more than ten) time log files." << endl;
	cout << endl;
	cout << "The program will look for CSV files in the same directory that are named LastnameFirstnameLog.csv. ";
	cout << "Each log file should have the following structure: " << endl;

	cout << endl;
	cout << "____________________________________________________________________" << endl;
	cout << "|Last Name|First Name|        |                |             |     |" << endl;
	cout << "|_________|__________|________|________________|_____________|_____|" << endl;
	cout << "|ClassID  |          |        |                |             |     |" << endl;
	cout << "|_________|__________|________|________________|_____________|_____|" << endl;
	cout << "|Date     |Start Time|End Time|Number of People|Activity Code|Notes|" << endl;
	cout << "|_________|__________|________|________________|_____________|_____|" << endl;
	cout << "|...      |...       |...     |...             |...          |...  |" << endl;
	cout << "|_________|__________|________|________________|_____________|_____|" << endl;
	cout << endl;

	cout << "After making sure each time log file is valid, the program will produce a text file for each of the following reports:" << endl;
	cout << " Report 1: A table showing each team member's name and the total number of minutes entered into their time log." << endl;
	cout << " Report 2: A table showing how many total minutes were spent by all team members on each of the activity codes." << endl;
	cout << " Report 3: A table showing how many minutes were spent by each team member on each of the activity codes." << endl;
	cout << " Report 4: A table showing the total number of minutes for the whole team for each day of the week." << endl;
	cout << " Report 5: A sorted list showing of all the times that team members logged a team meeting." << endl;
	cout << endl;
	cout << "The program will also print the following graphs to the screen:" << endl;
	cout << " Graph A: Displays Report 1 (total number of minutes by team member) as a bar graph." << endl;
	cout << " Graph B: Displays Report 3 (number of minutes spent on each activity by team member) as a heat map." << endl;
	cout << " Graph C: Displays a graph showing number of total minutes per day over time." << endl;
	cout << endl;
}
