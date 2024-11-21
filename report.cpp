#include "report.h"
#include <iostream>
#include <fstream>

using namespace std;

void Report::buildReport(vector<vector<string>> data, string fileName) {
  ofstream reportFile(fileName + ".txt", ios_base::out);

  int tableWidth = data[0].size();
  vector<int> columnWidths(tableWidth, 0);

  // calculate column widths
  for (vector<string> row : data) {
    for (int i = 0; i < row.size(); i++) {
      int width = row[i].length() + 1;

      if (columnWidths[i] < width) {
        columnWidths[i] = width;
      }
    }
  }

  // print top divider
  for (int i = 0; i < tableWidth; i++) {
    string filler;

    for (int j = 0; j < columnWidths[i]; j++) {
      filler += "_";
    }

    reportFile << "_" << setw(columnWidths[i]) << filler;
  }

  reportFile << "_" << endl;

  for (vector<string> row : data) {
    for (int i = 0; i < tableWidth; i++) {
      reportFile << "|" << setw(columnWidths[i]) << row[i];
    }

    reportFile << "|" << endl;

    for (int i = 0; i < tableWidth; i++) {
      string filler;

      for (int j = 0; j < columnWidths[i]; j++) {
        filler += "_";
      }

      reportFile << "|" << setw(columnWidths[i]) << filler;
    }

    reportFile << "|" << endl;
  }
}
