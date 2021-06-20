#include "game.h"
#include "chunk.h"

int main() 
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Mrufki", sf::Style::Close);

    game game;

    sf::Clock clock;
    sf::Time deltaTime = clock.restart();

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
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    game.world.setBlock(mouse_position, 1);
                }
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    game.world.setBlock(mouse_position, 0);
                }
            }
        }

        window.clear(sf::Color(150,150,255));

        deltaTime = clock.restart();
        game.update(&deltaTime);   
        window.draw(game);
        
        window.display();
    }

    return 0;
}