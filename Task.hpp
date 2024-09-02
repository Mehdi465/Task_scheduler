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

    public:
        Time();

        Time(int h,int m);

        void addTime(Time time_to_add);

        bool isInferior(Time compared_time);
};



class Task {

    private:
        std::string name;
        double probability;
        
    public:
        Task();

        Task(std::string line);

        Task (std::string name_task,double probability);

        std::string getName();

        double getProbability();
    };


class Schedule{
    
    private:
        std::map<int,Task> tasks;
        std::vector<double> probability_tasks;
        Time begin_t;
        Time end_t;

    public:
        Schedule();

        Schedule(const std::string file_name,Time start,Time end);

        void displaySchedule() const;

        void writeTask(std::string file_name) const;

};

#endif // TASK_HPP

