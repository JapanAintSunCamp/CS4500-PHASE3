



#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <dirent.h>

using namespace std;


struct TimeLogEntry {
        string dayOfWeek;
        int minutes;
    };
    struct TimeLog {
        string firstName;
        string lastName;
        vector<TimeLogEntry> entries;
    };
    
    bool parseLogFile(const string& filePath, TimeLog& log) {
        ifstream file(filePath.c_str());
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filePath << endl;
            return false;
        }
        
        string line;
        bool firstLine = true;
        while (getline(file, line)) {
            stringstream ss(line);
            if (firstLine) {
                firstLine = false;
                ss >> log.firstName >> log.lastName;
            } else {
                string day;
                int minutes;
                if (ss >> day >> minutes) {
                    log.entries.push_back({day, minutes});
                    
                } else {
                        cerr << "Error: Invalid time format in file " << filePath << endl;
                        return false;
                    }
                }
            }
            
            return true;
        }
    void generateReport4(const vector<TimeLog>& logs, const string& outputPath) {
        map<string, int> weeklyMinutes;
        weeklyMinutes["Sunday"] = 0;
        weeklyMinutes["Monday"] = 0;
        weeklyMinutes["Tuesday"] = 0;
        weeklyMinutes["Wednesday"] = 0;
        weeklyMinutes["Thursday"] = 0;
        weeklyMinutes["Friday"] = 0;
        weeklyMinutes["Saturday"] = 0;
        
    for (size_t i = 0; i < logs.size(); ++i) {
        for (size_t j = 0; j < logs[i].entries.size(); ++j) {
            string day = logs[i].entries[j].dayOfWeek;
            int minutes = logs[i].entries[j].minutes;
            if (weeklyMinutes.find(day) != weeklyMinutes.end()) {
                weeklyMinutes[day] += minutes;
            } else {
                cerr << "Warning: Invalid day of the week '" << day << "' in log." << endl;
            }
        }
    }
    
    
ofstream report(outputPath.c_str());
if (!report.is_open()) {
    cerr << "Error: Could not create report file " << outputPath << endl;
    return;
 }
 
 report << "Report 4: Total Team Minutes by Day of the week\n";
 report << "-------------------------------------------------\n";
 report << setw(15) << left << "Day of week"
        << setw(10) << "Total Minutes\n";
 report << "--------------------------------------------------\n";
 
 for (map<string, int>::iterator it = weeklyMinutes.begin(); it != weeklyMinutes.end(); ++it) {
    report << setw(15) << left << it->first
    << setw(10) << it->second << "\n";
    }

report.close();

cout << "report 4 generated at: " << outputPath << endl;
}

int main() {
    string directory = "."; // Current directory
    vector<TimeLog> logs;

    // Open directory and read files
    DIR* dir;
    struct dirent* ent;

    if ((dir = opendir(directory.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            string fileName = ent->d_name;

            // Only process files ending with "Log.csv"
            if (fileName.find("Log.csv") != string::npos) {
                TimeLog log;
                if (parseLogFile(fileName, log)) {
                    logs.push_back(log);
                } else {
                    cerr << "Skipping file due to errors: " << fileName << endl;
                }
            }
        }
        closedir(dir);
    } else {
        cerr << "Error: Could not open directory " << directory << endl;
        return 1;
    }

    if (logs.empty()) {
        cerr << "Error: No valid time log files found in the directory." << endl;
        return 1;
    }

    generateReport4(logs, "PhaseThreeReport4.txt");

    return 0;
}
