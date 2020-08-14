#include "taskmanager.hpp"

/*
    Constructor
*/
TaskManager::TaskManager() {
    _taskCount = 0;
}

/*
    Getters
*/
std::vector<Task>& TaskManager::getTasks() {
    return _tasks;
}

int TaskManager::getTaskCount() {
    return _taskCount;
}

int TaskManager::getSelectTaskIndex() {
    return _selectTaskIndex;
}

Task& TaskManager::getTaskWithIndex(int index) {
    if (index >= 0 && index < _tasks.size()) {
        return _tasks[index];
    }
    throw std::invalid_argument("no task found");
}

/*
    Setters
*/
void TaskManager::setTasksIsSorted(bool isSorted) {
    for (int i = 0; i < _tasks.size(); i++) {
        _tasks[i].setIsSorted(isSorted);
    }
}

void TaskManager::setTasks(std::vector<Task> tasks) {
    _tasks = tasks;
}

void TaskManager::setSelectTaskIndex(int index) {
    if (index < 0) index = _tasks.size() - 1;
    if (index >= _tasks.size()) index = 0;

    if (index >= 0 && index < _tasks.size()) {
        setTasksIsSelected(false);
        _selectTaskIndex = index;
        _tasks[index].setIsSelected(true);
    }
}

void TaskManager::setTasksIsSelected(bool isSelected) {
    for (int i = 0; i < _tasks.size(); i++) {
        _tasks[i].setIsSelected(isSelected);
    }
}

/*
    Miscellaneous
*/
void TaskManager::createNewTask(std::string name, std::string description, std::string time, bool completed) {
    _tasks.emplace_back(name, description, time, completed);
    _taskCount++;
}