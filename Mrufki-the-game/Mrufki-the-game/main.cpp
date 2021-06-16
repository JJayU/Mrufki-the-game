#include "game.h"

int main() 
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Mrufki", sf::Style::Close);

    sf::RectangleShape kwadrat;
    kwadrat.setFillColor(sf::Color(100, 0, 0));
    kwadrat.setSize(sf::Vector2f(16, 16));
    kwadrat.setPosition(0, 0);

    game game;
    game.mainView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));

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

        window.clear(sf::Color(150,150,255));

        window.draw(kwadrat);

        game.update();      
        window.setView(game.mainView);
        game.draw(&window);
       
        window.display();
    }

    return 0;
}