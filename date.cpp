#include "date.hpp"

/*
    Constructor
*/
Date::Date(std::string date) {
    auto startTime = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(startTime);
	_tm = *localtime(&currentTime);
    _date = date;

    setDate(_date);
}

/*
    Getters
*/
int Date::getTodaysMonthIndex() {
    auto startTime = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(startTime);
	tm mtm = *localtime(&currentTime);

    return mtm.tm_mon;
}

int Date::getTodaysYear() {
    auto startTime = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(startTime);
	tm mtm = *localtime(&currentTime);

    return 1900 + mtm.tm_year;
}

std::string Date::getTodaysDate() {
    auto startTime = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(startTime);
	tm mtm = *localtime(&currentTime);
    
    return std::to_string(mtm.tm_mon + 1) + "/" + std::to_string(mtm.tm_mday) + "/" + std::to_string(mtm.tm_year + 1900);
}

std::string Date::getTimeAsOfNow() {
    auto startTime = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(startTime);
	tm mtm = *localtime(&currentTime);

    return std::to_string(mtm.tm_hour) + ":" + std::to_string(mtm.tm_min);
}

std::string Date::getDate() {
    return _date;
}

TaskManager& Date::getTaskManager() {
    return _taskManager;
}

/*
    Setters
*/
void Date::setDate(std::string date) {
    std::vector<std::string> dateExploded = util::explode(date, '/');
    int month = std::stoi(dateExploded[0]);
    int day = std::stoi(dateExploded[1]);
    int year = std::stoi(dateExploded[1]);

    _tm.tm_mon = month - 1;
    _tm.tm_mday = day;
    _tm.tm_year = year - 1900;
    setTimeToMidnight();

    time_t rawTime;
    time(&rawTime);
    tm *timeInfo = localtime(&rawTime);
    timeInfo->tm_mon = _tm.tm_mon;
    timeInfo->tm_mday = _tm.tm_mday;
    timeInfo->tm_year = _tm.tm_year;
    mktime(timeInfo);
}

void Date::setTimeToMidnight() {
    _tm.tm_sec = 0;
    _tm.tm_min = 0;
    _tm.tm_hour = 0;
}

void Date::setTaskManager(TaskManager taskManager) {
    _taskManager = taskManager;
}

/*
    Miscellaneous
*/
float Date::convertTimeToInt(std::string time) {
    std::vector<std::string> timeExploded = util::explode(time, ':');
    int hour = std::stoi(timeExploded[0]);
    float minutes = std::stoi(timeExploded[1]);
    minutes /= 100;
    return hour + minutes;
}

void Date::newTask(std::string name, std::string description, std::string time, bool completed) {
    _taskManager.createNewTask(name, description, time, completed);
}

std::string Date::to12HourClock(std::string time) {
    // Setup time into different variables
    float timeAsInt = convertTimeToInt(time);
    int timeHour = std::floor(timeAsInt);
    int timeMinute = std::floor((timeAsInt - std::floor(timeAsInt)) * 100);

    // Conver the timeMinute to a string
    std::string timeMinuteAsString = std::to_string(timeMinute);

    // Format the time minutes to 12:00 or 12:09
    if (timeMinute == 0) {
        timeMinuteAsString += "0";
    } else if (timeMinute <= 9) {
        timeMinuteAsString = "0" + timeMinuteAsString;
    }

    // Format the time as a whole i.e. 12:34 AM or 3:30 PM
    if (timeHour == 0) {
        return std::to_string(12) + ":" + timeMinuteAsString + " AM";
    } else if (timeHour >= 1 && timeHour <= 11) {
        return std::to_string(timeHour) + ":" + timeMinuteAsString + " AM";
    } else if (timeHour == 12) {
        return std::to_string(timeHour) + ":" + timeMinuteAsString + " PM";
    } else if (timeHour >= 13) {
        return std::to_string(timeHour - 12) + ":" + timeMinuteAsString + " PM";
    }

    // Just return the time if all else fails
    return time;
}