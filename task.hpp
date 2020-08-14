#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <string>
#include <vector>

#include "util.hpp"

class Task {
    private:
        std::string _name;
        std::string _description;
        std::string _time = "1:00"; // 24 hour clock
        bool _isCompleted = false;
        bool _isSorted = false;
        bool _isSelected = false;

    public:
        // Constructor
        Task(std::string name, std::string description, std::string time, bool completed = false);

        // Getters
        std::string getName();
        std::string getDescription();
        std::string getTime();
        bool isCompleted();
        bool isSorted();
        bool isSelected();
        float getTimeAsInt();

        // Setters
        void setIsSorted(bool isSorted);
        void setIsSelected(bool isSelected);
        void setIsCompleted(bool isCompleted);

};

#endif