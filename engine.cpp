#include "engine.hpp"

/*
    Processes
*/
void Engine::setupTasks() {
    std::string fileContent = "";
    std::string line;
    std::fstream file("task.txt");
    if (file.is_open()) {
        while(std::getline(file, line)) {
            fileContent += line + "\n";
        }
        file.close();
    }

    std::vector<std::string> lines = util::explode(fileContent, '\n');
    for (int i = 0; i < lines.size(); i++) {
        std::vector<std::string> task = util::explode(lines[i], '|');
        std::vector<Date>& dates = _month.getDates();
        for (int i = 0; i < dates.size(); i++) {
            if (dates[i].getDate() == task[0]) {
                bool isCompleted = false;
                if (task[4] == "true") isCompleted = true;
                dates[i].newTask(task[2], task[3], task[1], isCompleted);
            }
        }
    }

    _month.sortTasksOnDates();

    Date& date = _month.getDateWithDate(Date::getTodaysDate());
    TaskManager& taskManager = date.getTaskManager();
    taskManager.setSelectTaskIndex(taskManager.getTaskCount()-1); 
}

void Engine::saveTasks() {
    std::ofstream file("task.txt");
    if (file.is_open()) {
        std::vector<Date> dates = _month.getDates();
        for (int i = 0; i < dates.size(); i++) {
            TaskManager taskManager = dates[i].getTaskManager();
            std::vector<Task> tasks = taskManager.getTasks();
            for (int f = 0; f < tasks.size(); f++) {
                if (f > 0) file << "\n";
                file << dates[i].getDate() + "|" + tasks[f].getTime() + "|" + tasks[f].getName() + "|" + tasks[f].getDescription() + "|" + util::bool_to_string(tasks[f].isCompleted());
            }
        }

        file.close();
    }
}

/*
    Main Loop
*/
void Engine::start() {
    setupTasks();
    
    sf::Clock clock;
    sf::Time totalTime;

    while(_window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        totalTime += deltaTime;

        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) _window.close();
            if (event.type == sf::Event::KeyReleased) inputKeyRelease(event);
        }

        if (totalTime.asSeconds() >= 60) {
            setupTasks();
            saveTasks();
            totalTime = deltaTime;
        }

        //update(deltaTime.asSeconds());
        draw();
    }
}

/*
    Input Handling
*/
void Engine::inputKeyRelease(sf::Event event) {
    if (event.key.code == sf::Keyboard::Right) { // Right Arrow
        Date& date = _month.getDateWithDate(Date::getTodaysDate());
        TaskManager& taskManager = date.getTaskManager();
        taskManager.setSelectTaskIndex(taskManager.getSelectTaskIndex() + 1);
    }

    if (event.key.code == sf::Keyboard::Left) { // DLeftown Arrow
        Date& date = _month.getDateWithDate(Date::getTodaysDate());
        TaskManager& taskManager = date.getTaskManager();
        taskManager.setSelectTaskIndex(taskManager.getSelectTaskIndex() - 1);
    }

    if (event.key.code == sf::Keyboard::Enter) { // Enter
        TaskManager& taskManager = _month.getDateWithDate(Date::getTodaysDate()).getTaskManager();
        Task& task = taskManager.getTaskWithIndex(taskManager.getSelectTaskIndex());
        task.setIsCompleted(!task.isCompleted());

        saveTasks();
    }

    if (event.key.code == sf::Keyboard::Escape) {
        saveTasks();
        _window.close();
    }
}

/*
    Drawing
*/
void Engine::draw() {
    _window.clear(sf::Color::White);
    
    sf::Color colorGreen(0, 120, 16);

    sf::Text text;
    text.setFont(_fontHeading);
    text.setCharacterSize(24);
    text.setString(Date::getTodaysDate() + ", " + Date::to12HourClock(Date::getTimeAsOfNow()));
    text.setFillColor(sf::Color::Black);

    TaskManager taskManager = _month.getDateWithDate(Date::getTodaysDate()).getTaskManager();
    std::vector<Task> tasks = taskManager.getTasks();

    std::vector<sf::Text> taskText;
    std::vector<bool> taskSelected;
    std::vector<bool> taskCompleted;

    std::vector<sf::Text> taskPassedText;
    std::vector<bool> taskPassedSelected;
    std::vector<bool> taskPassedCompleted;

    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].getTimeAsInt() >= Date::convertTimeToInt(Date::getTimeAsOfNow())) {
            sf::Text text;
            text.setString(Date::to12HourClock(tasks[i].getTime()) + " -- " + tasks[i].getName() + " -- " + tasks[i].getDescription());
            taskText.push_back(text);
            taskSelected.push_back(tasks[i].isSelected());
            taskCompleted.push_back(tasks[i].isCompleted());
        } else {
            sf::Text text;
            text.setString(Date::to12HourClock(tasks[i].getTime()) + " -- " + tasks[i].getName() + " -- " + tasks[i].getDescription());
            taskPassedText.push_back(text);
            taskPassedSelected.push_back(tasks[i].isSelected());
            taskPassedCompleted.push_back(tasks[i].isCompleted());
        }
    }

    _window.draw(text);

    for (int i = 0; i < taskText.size(); i++) {
        taskText[i].setFont(_fontText);
        taskText[i].setFont(_fontText);
        taskText[i].setCharacterSize(16);

        if (taskCompleted[i]) taskText[i].setFillColor(colorGreen);
        else taskText[i].setFillColor(sf::Color::Black);

        if (taskSelected[i]) {
            taskText[i].setString(">> " + taskText[i].getString() + " <<");
            taskText[i].setPosition(sf::Vector2f(16, 50 + 18 * i));
        } else {
            taskText[i].setPosition(sf::Vector2f(32, 50 + 18 * i));
        }

        _window.draw(taskText[i]);
    }

    for (int i = 0; i < taskPassedText.size(); i++) {
        taskPassedText[i].setFont(_fontText);
        taskPassedText[i].setFont(_fontText);
        taskPassedText[i].setCharacterSize(16);
        taskPassedText[i].setFillColor(sf::Color::Black);

        if (taskPassedCompleted[i]) taskPassedText[i].setFillColor(colorGreen);
        else taskPassedText[i].setFillColor(sf::Color::Black);

        if (taskPassedSelected[i]) {
            taskPassedText[i].setString(">> " + taskPassedText[i].getString() + " <<");
            taskPassedText[i].setPosition(sf::Vector2f(16, 100 + 18 * taskText.size() + 18 * i));
        } else {
            taskPassedText[i].setPosition(sf::Vector2f(32, 100 + 18 * taskText.size() + 18 * i));
        }

        _window.draw(taskPassedText[i]);
    }

    _window.display();
}