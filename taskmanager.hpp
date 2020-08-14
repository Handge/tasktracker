#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP

#include <string>
#include <vector>

#include "task.hpp"

class TaskManager {
    private:
        std::vector<Task> _tasks;
        int _taskCount = 0;

        int _selectTaskIndex = 0;

    public:
        // Constructor
        TaskManager();

        // Getters
        std::vector<Task>& getTasks();
        int getTaskCount();
        int getSelectTaskIndex();
        Task& getTaskWithIndex(int index);

        // Setters
        void setTasks(std::vector<Task> tasks);
        void setTasksIsSorted(bool isSorted);
        void setSelectTaskIndex(int index);
        void setTasksIsSelected(bool isSelected);

        // Miscellaneous
        void createNewTask(std::string name, std::string description, std::string time, bool completed = false);
};

#endif