
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <dirent.h> // For directory traversal

using namespace std;


class Report1{
public:

    struct TimeLog {
        string firstName;
        string lastName;
        int totalMinutes;
    };

    static bool parseLogFile(const string& filePath, TimeLog& log) {
        ifstream file(filePath.c_str());
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filePath << endl;
            return false;
        }
        
        string line;
        bool firstLine = true;
        int totalMinutes = 0;
        
        while (getline(file, line)) {
            stringstream ss(line);
            if (firstLine) {
                firstLine = false;
                ss >> log.firstName >> log.lastName;
            } else {
                int minutes;
                if (ss >> minutes) {
                    totalMinutes += minutes;
                } else {
                    cerr << "Error: Invalidddd time format in file " << filePath << endl;
                    return false;
                }
                }
            }
            
            log.totalMinutes = totalMinutes;
            return true;
            }
            static void generateReport1(const vector<TimeLog>& logs, const string& outputPath)  {
        ofstream report(outputPath.c_str());
        if (!report.is_open()) {
            cerr << "Error: Could not create report file " << outputPath << endl;
            return;
        }

        report << "Report 1: Total Minutes Logged\n";
        report << "--------------------------------\n";
        report << setw(20) << left << "Name"
            << setw(10) << "Total Minutes\n";
        report << "--------------------------------\n";

        for (size_t i = 0; i < logs.size(); ++i) {
            report << setw(20) << left << (logs[i].firstName + " " + logs[i].lastName)
                << setw(10) << logs[i].totalMinutes << "\n";
        }
        report.close();
        cout << "Report 1 generated at: " << outputPath << endl;
        }
        
        static int generateReport() {
            string directory = ".";
            vector<TimeLog> logs;
            
            DIR* dir;
            struct dirent* ent;
            if ((dir = opendir(directory.c_str())) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                string fileName = ent->d_name;

                
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

        generateReport1(logs, "PhaseThreeReport1.txt");

        return 0;
    }



};
        

