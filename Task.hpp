#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>

#ifndef TASK_HPP
#define TASK_HPP

class Time{
    private :
        int hour;
        int minute;
        int day; // start from 0 from the day the schedule starts

    public:
        Time();

        Time(int d, int h, int m);

        void addTime(Time time_to_add);

        bool isInferior(Time compared_time);

        int getMinute();

        int getHour();

        void printTime() const;
};


class Task {

    private:
        std::string name;
        double probability;
        
    public:
        Task();

        Task(std::string line);

        Task (std::string name_task,double probability);

        std::string getName() const;

        double getProbability();
    };


class Schedule{
    
    private:
        std::vector<Task> tasks;
        std::vector<double> probability_tasks;
        Time begin_t;
        Time end_t;

    public:
        Schedule();

        Schedule(const std::string file_name,Time start,Time end);

        void displayScheduleInTerminal() const;

        void renderSchedule() const;

        void writeTask(std::string file_name) const;

};

#endif // TASK_HPP

