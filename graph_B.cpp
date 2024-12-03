#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <filesystem>
using namespace std;

class GraphB{
public:
    static void printHeatmapLegend(vector<vector<int>> activityCodes) {  // LEGEND FOR HEAT MAP
        int maxVal = numeric_limits<int>::min();

        for (const auto& activity : activityCodes) { // Find max value
            for (int code : activity) {
                maxVal = max(maxVal, code);
            }
        }

        maxVal = ((maxVal + 99) / 100) * 100; // Update max value to nearest 100

        // Print out legend
        cout << "\033[48;5;117m  ""\033[48;5;117m  ""\033[48;5;117m  ""\033[48;5;117m  " << "\033[0m";
        cout << "\033[48;5;123m  ""\033[48;5;123m  ""\033[48;5;123m  ""\033[48;5;123m  " << "\033[0m";
        cout << "\033[48;5;33m  ""\033[48;5;33m  ""\033[48;5;33m  ""\033[48;5;33m  " << "\033[0m";
        cout << "\033[48;5;19m  ""\033[48;5;19m  ""\033[48;5;19m  ""\033[48;5;19m  " << "\033[0m";
        cout << endl;
        cout << " 0-" << maxVal / 5;
        cout << "    " << (maxVal / 5) + 1 << "-" << maxVal / 2;
        cout << "  " << (maxVal / 2) + 1 << "-" << maxVal * 4 / 5;
        cout << " " << (maxVal * 4 / 5) + 1 << "-" << maxVal;
    }

    static string mapToColor(double value, vector<vector<int>> activityCodes) { // Color the heat map.

        int maxVal = numeric_limits<int>::min(); // Initialize to min.

        for (const auto& activity : activityCodes) { // Find max value
            for (int code : activity) {
                maxVal = max(maxVal, code);
            }
        }

        maxVal = ((maxVal + 99) / 100) * 100; // Update max value to nearest 100

        // Heatmap coloring based on values.
        if (value >= 0 && value < maxVal / 5)
            return "\033[48;5;117m  "; // Light Blue
        else if (value >= maxVal / 5 && value < maxVal / 2)
            return "\033[48;5;123m  "; // Sky Blue
        else if (value >= maxVal / 2 && value < maxVal * 4 / 5)
            return "\033[48;5;33m  "; // Medium Blue
        else if (value >= maxVal * 4 / 5 && value <= maxVal)
            return "\033[48;5;19m  "; // Dark Blue
    }

    // Function to print the meat hap
    static void printHeatmap(const vector<vector<double>> &data, const vector<string> names, const vector<vector<int>> activityCodes) {
        char activities[4] = {'A', 'B', 'C', 'D'};

        int i = 0;
        for (const auto& row : data) { // Printing the actual heat map

            for (double val : row) {
                cout << mapToColor(val, activityCodes) << "  \033[0m ";
            }
            cout << '\n';

            for (double val : row) {
                cout << mapToColor(val, activityCodes) << "  \033[0m ";
            }
            cout << names[i]; // Y AXIS LABELS
            cout << '\n';

            for (double val : row) {
                cout << mapToColor(val, activityCodes) << "  \033[0m ";
            }
            cout <<'\n';
            i++;
        }

        // X AXIS LABELS
        cout << "  0";
        for (int i = 1; i < 10; i++) {
            cout << "    " << i;
        }

        for (int i = 0; i < 4; i++) {
            cout << "    " << activities[i];
        }

    }

    static int generateGraph() {
        ifstream file("PhaseThreeReportThree.csv"); // FILE CHECKING
        if (!file.is_open()) {
            cerr << "Failed to open file.\n";
            return 1;
        }

        // VARIABLES
        vector<string> names;
        vector<vector<int>> activityCodes;
        string line;
        bool isHeader = true;

        while (getline(file, line)) { // EXTRACTING DATA FROM CSV FILE
            stringstream ss(line);

            if (isHeader) { // SKIP HEADER
                isHeader = false;
                continue;
            }

            string name;
            string code;
            vector<int> codes;

            if (getline(ss, name, ',')) {
                names.push_back(name);
            }

            while (getline(ss, code, ',')) {
                if (!code.empty() && isdigit(code[0])) { // Check for non-empty and valid numeric code
                    codes.push_back(std::stoi(code));
                }
            }

            activityCodes.push_back(codes);
        }


            vector<vector<double>> heatmapData;
            for (const auto& codes : activityCodes) {
                vector<double> row;
                for (int code : codes) {
                    row.push_back(static_cast<double>(code));
                }
                heatmapData.push_back(row);
            }

        printHeatmap(heatmapData, names, activityCodes);

        // SPACING FOR HEAT MAP LEGEND
        cout << endl;
        cout << endl;
        cout << endl;

        printHeatmapLegend(activityCodes);
        cout << "\033[0m";

        file.close();

        filesystem::remove("PhaseThreeReportThree.csv");

        return 0;
    }
};

