#include <iostream>
#include <sstream>
#include "Task.hpp"

// Function to parse the time from a command line argument
Time parseTime(const std::string& timeStr) {
    int h, m;
    char delimiter;
    std::istringstream timeStream(timeStr);
    timeStream >> h >> delimiter >> m;

    if (delimiter != '-') {
        throw std::invalid_argument("Invalid time format. Use 'hh-mm'.");
    }

    return Time(0, h, m);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <start_time> <end_time>" << std::endl;
        std::cerr << "Example: " << argv[0] << " 18-30 23-0" << std::endl;
        return 1;
    }

    try {
        // Parse start and end times from command line
        Time startTime = parseTime(argv[1]);
        Time endTime = parseTime(argv[2]);

        // If the end time is earlier than the start time, increment the day for the end time
        if (!startTime.isInferior(endTime)) {
            endTime = Time(1, endTime.getHour(), endTime.getMinute());
        }

        // Create the schedule
        Schedule schedule("tasks.txt", startTime, endTime);
        schedule.renderSchedule();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}