#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "Task.hpp"

#define TIME_PER_TASK 45


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

void Time::addTime(Time time_to_add){
    this->minute += time_to_add.minute;
    this->hour = (this->hour + time_to_add.hour + this->minute / 60) % 24;
    this->minute %= 60;
}

bool Time::isInferior(Time compared_time){
    bool res = true;
    if (this->hour > compared_time.hour){
        res = false;
    }
    else if (this->hour == compared_time.hour){
        if (this->minute >= compared_time.minute){
           res = false;
        }
    }
    return res;
}

int Time::getMinute(){
    return this->minute;
}

int Time::getHour(){
    return this->hour;
}


// Task part
Task::Task() : name(""), probability(0.0){};

Task::Task(std::string name_task,double probability){
    this->name = name_task;
    this->probability = probability;
}

double Task::getProbability(){
    return this->probability;
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

std::string Task::getName() const {
            return this->name;
        }


// Schedule part

Schedule::Schedule() : begin_t(Time()), end_t(Time(23,59)){};


Schedule::Schedule(const std::string file_name,Time start, Time end){

    Schedule res_schedule = Schedule();

    this->begin_t = start;
    this->end_t = end;

    std::ifstream inputFile("tasks.txt");
    if (!inputFile.is_open()){
        std::cerr << "Cant find the file or open it" << std::endl;
        throw std::runtime_error("Cant find the file or open it");
    } 

    std::string line;
    double sum_proba = 0.0;
    int index = 0;
    Task new_task;
    std::vector<Task> tasks_inter;

    while(getline(inputFile,line)){
        new_task = Task(line); 
        sum_proba += new_task.getProbability();
        this->probability_tasks.push_back(new_task.getProbability());
        tasks_inter.push_back(new_task);
        index++;
    }

    Time current_time = start;
    // activate random
    srand (time(NULL));
    
    // randomize tasks 
    while(current_time.isInferior(end)){

        // add 45 minutes for each task
        current_time.addTime(Time(0,TIME_PER_TASK));

        double current_task_proba = (rand() % 100)/100.0;

        // get the current task
        int index = 0;
        double sum_index_proba = this->probability_tasks[0];
        while(sum_index_proba<current_task_proba){
            index++;
            sum_index_proba+=this->probability_tasks[index];
            
        }
        this->tasks.push_back(tasks_inter[index]);
    }
}

void Schedule::displayScheduleInTerminal() const {
    for (const Task& task : this->tasks){
        std::cout << task.getName() << std::endl;
    }
}

void Schedule::renderSchedule() const {
    std::ofstream outputFile("schedule_output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Cannot open output file" << std::endl;
        return;
    }

    Time current_time = this->begin_t;
    for (const Task& task : this->tasks) {
        outputFile << current_time.getHour() << ":" << (current_time.getMinute() < 10 ? "0" : "") << current_time.getMinute();
        current_time.addTime(Time(0, TIME_PER_TASK));
        outputFile << " - " << current_time.getHour() << ":" << (current_time.getMinute() < 10 ? "0" : "") << current_time.getMinute();
        outputFile << " : " << task.getName() << std::endl;
    }

    outputFile.close();
    // run automatically the Python script
    int result = system("python3 generate_schedule.py");
    if (result != 0) {
        std::cerr << "Error executing the Python script" << std::endl;
    }
}




        