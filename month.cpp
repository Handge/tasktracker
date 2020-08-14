#include "month.hpp"

/*
    Static Variables
*/
std::string Month::monthNames[12] = {
    "January", "Feburary", "March", "April", "May", "June", "July", "August", "September", "October", "Novemeber", "December"
};

/*
    Constructor
*/
Month::Month(int index, int year) {
    _index = index;
    _year = year;
    _name = Month::monthNames[_index];

    for (int i = 0; i < getDaysInMonth(); i++) {
        _dates.emplace_back(std::to_string(_index + 1) + "/" + std::to_string(i + 1) + "/" + std::to_string(_year));
    }
}

/*
    Getters
*/
std::string Month::getName() {
    return _name;
}

int Month::getDaysInMonth() {
    if (_index == 3 || _index == 5 || _index == 8 || _index == 10) {
        return 30;
    } else if (_index == 1) {
        if ((_year % 4 == 0 && _year % 100 != 0) || (_year % 400 == 0)) {
            return 29;
        } else {
            return 28;
        }
    }
    return 31;
}

std::vector<Date>& Month::getDates() {
    return _dates;
}

Date& Month::getDateWithDate(std::string date) {
    for (int i = 0; i < _dates.size(); i++) {
        if (_dates[i].getDate() == date) {
            return _dates[i];
        }
    }
    throw std::invalid_argument("no date found");
}

/*
    Setters
*/
void Month::setDates(std::vector<Date> dates) {
    _dates = dates;
}


/*
    Miscellaneous
*/
void Month::sortTasksOnDates() {
    for (int d = 0; d < _dates.size(); d++) {
        TaskManager taskManager = _dates[d].getTaskManager();
        std::vector <Task> tasks = taskManager.getTasks();
        std::vector <float> dateAsInts;
        
        for (int i = 0; i < tasks.size(); i++) {
            dateAsInts.push_back(tasks[i].getTimeAsInt());
        }

        std::sort(dateAsInts.begin(), dateAsInts.end());
        std::vector <Task> tasksSorted;

        for (int i = 0; i < dateAsInts.size(); i++) {
            for (int f = 0; f < tasks.size(); f++) {
                if (!tasks[f].isSorted() && tasks[f].getTimeAsInt() == dateAsInts[i]) {
                    tasks[f].setIsSorted(true);
                    tasksSorted.push_back(tasks[f]);
                }
            }
        }

        taskManager.setTasksIsSorted(false); // reset _isSorted on all tasks

        taskManager.setTasks(tasksSorted);
        _dates[d].setTaskManager(taskManager);
    }
}