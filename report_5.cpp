#include <map>
#include <string>
#include <vector>
#include "log.h"
#include "report.h"
#include <iostream>

// using namespace std;

struct Meeting {
    time_t date;
    time_t startTime;
    time_t endTime;
    int numberOfParticipants;
    time_t totalElapsedTime; // in minutes

    Meeting(const time_t& date, const time_t& startTime, const time_t& endTime, int numberOfParticipants, time_t totalElapsedTime)
        : date(date), startTime(startTime), endTime(endTime), numberOfParticipants(numberOfParticipants), totalElapsedTime(totalElapsedTime) {}
};

class Report5 {
    private:
        /*
            * Determine if two meeting logs are part of the same meeting
            *
            * Parameter startTime1 - a time_t representing the start time of the first meeting
            * Parameter endTime1 - a time_t representing the end time of the first meeting
            * Parameter startTime2 - a time_t representing the start time of the second meeting
            * Parameter endTime2 - a time_t representing the end time of the second meeting
            *
            * Returns true if the meeting logs are for the same meeting, false otherwise
        */
        static bool isRelated(time_t startTime1, time_t endTime1, time_t startTime2, time_t endTime2) {
            // Set the actual meeting start time to be the later of the two start times
            time_t actualStartTime = startTime1 > startTime2 ? startTime2 : startTime1;
            // Set the actual meeting end time to be the earlier of the two end times
            time_t actualEndTime = endTime1 < endTime2 ? endTime2 : endTime1;
            // Set the meeting duration to be the difference between the actual end time and the actual start time
            time_t duration = actualEndTime - actualStartTime;

            // Calculate the meeting start/stop time offset
            // subtract the smaller start time from the larger start time
            time_t startOffset = startTime1 > startTime2 ? startTime1 - startTime2 : startTime2 - startTime1;
            // subtract the smaller end time from the larger end time
            time_t endOffset = endTime1 > endTime2 ? endTime1 - endTime2 : endTime2 - endTime1;
            // set the offset to be the larger of the two offsets
            time_t offset = startOffset > endOffset ? startOffset : endOffset;

            return duration > offset;
        };
        /*
            * Verify that all meetings are related to each other
            *
            * Parameter baseMeeting - a Meeting object that all other meetings should be related to
            * Parameter meetings - a vector of Meeting objects
            *
            * Returns a vector of Meeting objects that are related to each other
        */
        static vector<Meeting> verifyMeetingsRelated(Meeting baseMeeting, const std::vector<Meeting>& meetings) {
            vector<Meeting> verifiedMeetings;
            map<int, int> headcount;

            // For each meeting, verify that it is related to all other meetings
            for (size_t i = 0; i < meetings.size(); ++i) {
                const Meeting& currentMeeting = meetings[i];

                bool relatedToAll = true;
                for (size_t j = i + 1; j < meetings.size(); ++j) {
                    const Meeting& testMeeting = meetings[j]; // inner loop meeting being tested for relation

                    // If the current meeting is not related to the test meeting, set relatedToAll to false and stop the loop
                    if (!isRelated(currentMeeting.startTime, currentMeeting.endTime, testMeeting.startTime, testMeeting.endTime)) {
                        relatedToAll = false;
                        break;
                    }
                }

                // If the current meeting is related to all the other meetings, add the meeting to the list of verified meetings and the meeting headcount to the headcount map
                if (relatedToAll) {
                    headcount[currentMeeting.numberOfParticipants]++;
                    verifiedMeetings.push_back(currentMeeting);
                }
            }

            // Filter meetings by headcount
            verifiedMeetings = verifyHeadCount(baseMeeting, headcount, verifiedMeetings);

            // return the list of verified meetings
            return verifiedMeetings;
        };
        /*
            * Verify that all meetings have the same head count
            *
            * Parameter baseMeeting - a Meeting object that all other meetings are being compared to
            * Parameter headCountMap - a map of head counts and the number of meetings with that head count
            * Parameter meetings - a vector of Meeting objects
            *
            * Returns a vector of filtered Meeting objects that have the same head count as the base meeting
        */
        static vector<Meeting> verifyHeadCount(Meeting baseMeeting, map<int, int> headCountMap, const std::vector<Meeting>& meetings) {
            vector<Meeting> verifiedMeetings = meetings;

            // If the meetings have different headcounts, filter them based on headcount options
            if (headCountMap.size() > 1) {
                int headcountOverTwo = 0;
                for (const auto& pair : headCountMap) {
                    if (pair.second > 2) {
                        headcountOverTwo++;
                    }
                }

                // If there were multiple meetings, but only one meeting has a head count over 2, set the head count of the other meetings to the base meeting's head count
                if (headcountOverTwo == 1) {
                    for (Meeting meeting : verifiedMeetings) {
                        if (meeting.numberOfParticipants != baseMeeting.numberOfParticipants) {
                            meeting.numberOfParticipants = baseMeeting.numberOfParticipants;
                        }
                    }
                }

                // If multiple meetings have a head count greater than two, only keep the meetings that have the same head count as the base meeting
                if (headcountOverTwo > 1) {
                    for (Meeting meeting : verifiedMeetings) {
                        if (meeting.numberOfParticipants != baseMeeting.numberOfParticipants) {
                            verifiedMeetings.erase(
                                std::remove_if(verifiedMeetings.begin(), verifiedMeetings.end(),
                                            [&baseMeeting](const Meeting& meeting) {
                                                return meeting.numberOfParticipants != baseMeeting.numberOfParticipants;
                                            }),
                                verifiedMeetings.end());
                        }
                    }
                }
            }

            return verifiedMeetings;
        };
        /*
            * Create a meeting object from a list of meetings
            *
            * Parameter meetings - a vector of Meeting objects
            *
            * Returns a Meeting object with the final meeting details
        */
        static Meeting createMeeting(const std::vector<Meeting>& meetings) {
            time_t date = meetings[0].date;
            time_t actualStartTime;
            time_t actualEndTime;
            int numberOfParticipants = meetings[0].numberOfParticipants;
            time_t totalElapsedTime = 0;

            for (Meeting meeting : meetings) {
                // If the actual start time is earlier than the meeting's start time, set the actual start time to the meeting's start time
                if (actualStartTime < meeting.startTime) actualStartTime = meeting.startTime;
                // If the actual end time is later than the meeting's end time, set the actual end time to the meeting's end time
                if (actualEndTime > meeting.endTime) actualEndTime = meeting.endTime;
            }

            totalElapsedTime = actualEndTime - actualStartTime;

            return Meeting(date, actualStartTime, actualEndTime, numberOfParticipants, totalElapsedTime);
        }
        /*
        */
        static void buildReport(vector<vector<string>> reportData, ReportMetadata metadata) {
            Report::buildReport(reportData, metadata);
        };

    public:
        static map<char, int> codesMap;
        static ReportMetadata metadata;

    static void generateReport() {
        string filename = "PhaseThreeReport5";
        string title = "Report 5";
        string explanation = "This report displays a list of all meetings performed by the team members.";
        string classId = Logs::logs[0].classId;
        vector<Meeting> potentialMeetings;
        vector<Meeting> confirmedMeetings;

        // Filter all activities that are meetings into a list of potential meetings
        for (auto &log : Logs::logs) {
            for (Activity activity : log.activities) {
                if ( activity.code == '4' ) {
                    potentialMeetings.push_back(Meeting(activity.date, activity.startTime, activity.endTime, activity.numberOfParticipants, 0));
                }
            }
        }

        // Verify each potential meeting and add it to the confirmed meetings list
        for (size_t i = 0; i < potentialMeetings.size(); ++i) {
            Meeting& meeting = potentialMeetings[i];
            vector<Meeting> relatedMeetings;

            // Find all realted meeting logs and add them to the related meetings list
            for (size_t j = i + 1; j < potentialMeetings.size(); ++j) {
                Meeting& otherMeeting = potentialMeetings[j];

                if (otherMeeting.date == meeting.date && isRelated(meeting.startTime, meeting.endTime, otherMeeting.startTime, otherMeeting.endTime)) {
                    relatedMeetings.push_back(meeting);
                }
            }

            // Filter relatedMeetings to only contain meeting logs verfied to be the same meeting
            relatedMeetings = verifyMeetingsRelated(meeting, relatedMeetings);

            // Create a meeting log from the related meetings
            Meeting newMeeting = createMeeting(relatedMeetings);

            // Add the new meeting to the confirmed meetings list
            confirmedMeetings.push_back(newMeeting);

            // Remove relatedMeetings from potentialMeetings
            potentialMeetings.erase(
                std::remove_if(potentialMeetings.begin(), potentialMeetings.end(),
                            [&relatedMeetings](const Meeting& m) {
                                return std::find(relatedMeetings.begin(), relatedMeetings.end(), m) != relatedMeetings.end();
                            }),
                potentialMeetings.end());
        }

    }
};