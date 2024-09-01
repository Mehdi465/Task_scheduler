#include "Task.hpp"
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cmath>


// Time part
Time::Time() : hour(0), minute(0){};

Time::Time(int h,int m){
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

Time Time::addTime(Time time_to_add){
    
    this->hour = (time_to_add.hour+this->hour)%24 + (this->minute+time_to_add.minute)/60;

    
}


// Task part
Task::Task() : name(""), probability(0.0){};

Task::Task(std::string name_task,double probability){
    this->name = name_task;
    this->probability = probability;
}

Task::Task(std::string line){
    std::size_t commaPos = line.find(',');
    // if no comma
    if (commaPos == std::string::npos) {
        throw std::invalid_argument("Invalid format: missing comma");
    }

    // extract the name
    std::string name = line.substr(0,commaPos);
    std::string probability_string = line.substr(commaPos + 1);

    // remove the %
    if (!probability_string.empty() && probability_string.back() == '%') {
        probability_string.pop_back();
    }

    double probabilty;
    try {
        probability = std::stod(probability_string) / 100.0;
    } catch (const std::invalid_argument& e){
        throw std::invalid_argument("probabilty does not respect the format");
    }

    this->name = name;
    this->probability = probability;
}        

std::string Task::getName(){
            return this->name;
        }


// Schedule part

Schedule::Schedule() : begin_t(Time()), end_t(Time(23,59)){};


Schedule::Schedule(const std::string file_name,Time start, Time end){

    Schedule res_schedule = Schedule();

    std::ifstream inputFile("tasks.txt");
    if (!inputFile.is_open()){
        std::cerr << "Cant find the file or open it" << std::endl;
        throw std::runtime_error("Cant find the file or open it");
    } 

    std::string line;
    // for every tasks, do:
    while(getline(inputFile,line)){
        Task new_task = Task(line);
    }


    

}

void Schedule::addTask(Task new_task){
            this->tasks[new_task.getName()] = new_task;
        }

        