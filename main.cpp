#include <iostream>
#include "Task.hpp"

int main(){

    Schedule schedule = Schedule("tasks.txt",Time(0,18,30),Time(0,23,0));
    schedule.renderSchedule();

}