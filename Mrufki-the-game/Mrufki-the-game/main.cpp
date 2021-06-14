#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "game.h"

int main() 
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Mrufki", sf::Style::Close);

    Game game;

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            } 
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        window.clear(sf::Color::Black);

        //
       
        window.display();
    }

    return 0;
}