#include"game.h"

#include <SFML/Graphics.hpp>

namespace agario
{

Game::Game(){

}

Game::~Game(){

}

void Game::run(){
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Agario");
    window.setFramerateLimit(60);

    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition({350.f, 250.f});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }
}
    
}
