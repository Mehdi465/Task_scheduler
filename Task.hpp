#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>

class Time{

    private :
        int hour;
        int minute;

    public:
        Time();

        Time(int h,int m);

        Time addTime(Time time_to_add);
};

class Task {

    private:
        std::string name;
        double probability;
        
    public:
        Task(){};

        Task(std::string line);

        Task (std::string name_task,double probability);

        std::string getName();
    };


class Schedule{
    
    private:
        std::map<std::string,Task> tasks;
        Time begin_t;
        Time end_t;

    public:
        Schedule(){};

        Schedule(const std::string file_name,Time start,Time end){};

        void displaySchedule() const;

        void writeTask(std::string file_name) const;

        void addTask(Task new_task);
        
        

};

