#include <iostream>
#include "Task.hpp"

int main(){
    
    Schedule schedule = Schedule("tasks.txt",Time(18,30),Time(23,30));
    schedule.renderSchedule();

}