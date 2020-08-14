#include "task.hpp"

/*
    Constructor
*/
Task::Task(std::string name, std::string description, std::string time, bool completed) {
    _name = name;
    _description = description;
    _time = time;
    _isCompleted = completed;
}

/*
    Getters
*/
std::string Task::getName() {
    return _name;
}

std::string Task::getDescription() {
    return _description;
}

std::string Task::getTime() {
    return _time;
}

bool Task::isCompleted() {
    return _isCompleted;
}

float Task::getTimeAsInt() {
    std::vector<std::string> timeExploded = util::explode(_time, ':');
    int hour = std::stoi(timeExploded[0]);
    float minutes = std::stoi(timeExploded[1]);
    minutes /= 100;
    float time = hour + minutes;
    return time;
}

bool Task::isSorted() {
    return _isSorted;
}

bool Task::isSelected() {
    return _isSelected;
}

/*
    Setters
*/
void Task::setIsSorted(bool isSorted) {
    _isSorted = isSorted;
}

void Task::setIsSelected(bool isSelected) {
    _isSelected = isSelected;
}

void Task::setIsCompleted(bool isCompleted) {
    _isCompleted = isCompleted;
}