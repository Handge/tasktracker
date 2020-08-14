#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <string>
#include <vector>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "month.hpp"

class Engine {
    private:
        // Window
        sf::RenderWindow _window;

        // SFML Stuff
        sf::Image _windowIcon;
        sf::Font _fontHeading;
        sf::Font _fontText;

        int _fps = 60;
        int _monthCount = 3;
        bool _running = true;

        Month _month;

        // Private Functions
        void run();
        void inputKeyRelease(sf::Event event);
        void draw();
        void setupTasks();
        void saveTasks();

    public:
        Engine() : _month(Date::getTodaysMonthIndex(), Date::getTodaysYear()) {
            _window.create(sf::VideoMode(800, 600), "Task Tracker", sf::Style::Titlebar | sf::Style::Close);
            _window.setFramerateLimit(_fps);
            _fontHeading.loadFromFile("fonts/Arial.ttf");
            _fontText.loadFromFile("fonts/Courier.ttf");

            _windowIcon.loadFromFile("images/blueball.png");
            _window.setIcon(_windowIcon.getSize().x, _windowIcon.getSize().y, _windowIcon.getPixelsPtr());
        };
        void start();
};

#endif