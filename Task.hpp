#include <iostream>

class Time{
    int hour;
    int minute;

    Time(int h,int m){
        // secure condition for hour
        if (h>23 || h<0)
        {
            throw std::invalid_argument("hour is below 0 or above 24");
        }

        // secure condition for minute
        if (m>59 || m<0)
        {
            throw std::invalid_argument("minute is below 0 or above 59");
        }

        this->hour = h;
        this->minute = m;
    }

    
};

class Task {
    public:
        std::string name;
        double probability;
        Time begin_time;
        Time end_time;

        Task (std::string name_task,Time begin_t, Time end_t){
            this->name = name_task;
            
            }


    };