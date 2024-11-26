#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>

using namespace std;

class ReportMetadata {
public:
  string filename;
  string title;
  string classId;
  vector<string> people;
  string explanation;
};

class Report {
public:
  static void buildReport(vector<vector<string>>, ReportMetadata);
};

#endif
