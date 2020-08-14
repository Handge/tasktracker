#ifndef DATE_HPP
#define DATE_HPP

#include <string>
#include <ctime>
#include <chrono>
#include <cmath>

#include "taskmanager.hpp"
#include "util.hpp"

class Date {
    private: 
        tm _tm;
        TaskManager _taskManager;
        std::string _date;

    public:
        // Constructor
        Date(std::string date);

        // Getters
        std::string getDate();
        TaskManager& getTaskManager();

        // Setters
        void setDate(std::string date);
        void setTimeToMidnight();
        void setTaskManager(TaskManager taskManager);

        // Miscellaneous
        void newTask(std::string name, std::string description, std::string time, bool completed = false);

        // Static Functions
        // Getters
        static int getTodaysMonthIndex();
        static int getTodaysYear();
        static std::string getTodaysDate();
        static std::string getTimeAsOfNow();

        // Miscellaneous
        static float convertTimeToInt(std::string time);
        static std::string to12HourClock(std::string time);
};

#endif