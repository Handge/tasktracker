#ifndef MONTH_HPP
#define MONTH_HPP

#include <string>
#include <vector>
#include <algorithm>

#include "date.hpp"

class Month {
    private:
        // Static Variables
        static std::string monthNames[12];

        std::string _name;
        int _index;
        int _year;

        std::vector<Date> _dates;

    public:
        // Constructor
        Month(int index, int year);

        // Getters
        std::string getName();
        int getDaysInMonth();
        std::vector<Date>& getDates();
        Date& getDateWithDate(std::string date);

        // Setters
        void setDates(std::vector<Date> dates);

        // Miscellaneous
        void sortTasksOnDates();
};

#endif