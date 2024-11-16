#include <string>
#include <vector>
#include <ctime> // For DateTime representation

// Define the Activity structure
struct Activity {
    int code;
    std::time_t date;    // Using time_t to represent DateTime
    std::time_t minutes; // Assuming this is a duration represented in time_t
};

// Define the Log class
class Log {
public:
    // Member variables
    std::string classId;
    std::string firstName;
    std::string lastName;
    std::string name;
    std::vector<Activity> activities; // Using std::vector for the list of activities

    // Constructor (optional)
    Log(const std::string& classId, const std::string& firstName, const std::string& lastName, const std::string& name)
        : classId(classId), firstName(firstName), lastName(lastName), name(name) {}

    // Add activity method (optional)
    void addActivity(int code, std::time_t date, std::time_t minutes) {
        activities.push_back({code, date, minutes});
    }
};