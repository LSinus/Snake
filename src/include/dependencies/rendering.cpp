#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "size.hpp"
#include "snake.hpp"
#include "apple.hpp"

#include <iostream>
#include <cmath>

#include "rendering.hpp"

void renderingThread(sf::RenderWindow* window,const Snake* snake, sf::Text* text, sf::RectangleShape* rectangle, sf::Vector2f* velocity, Apple* apple, bool* eat){
    
    window->setActive(true);
    sf::Clock clock;
    sf::Time time1;
    clock.restart();   

    while (window->isOpen()){

        clock.restart();
        std::cout<<snake->snake.size()<<'\n';
        window->clear(sf::Color(22, 102, 44, 255));
        window->draw(*text);
        window->draw(*rectangle);
        window->draw(apple->apple);
        for(int i=0; i<(snake->snake.size()); i++){
            window->draw(snake->snake[i]);
        }

        //std::cout<<"change direction detected at: "<<snake->position_change.x<<" "<<snake->position_change.y<<'\n';
        //std::cout<<"next segment position: "<<snake->snake[1].getPosition().x<<" "<<snake->snake[1].getPosition().y<<'\n';
        
        window->display();

        time1 = clock.getElapsedTime();
        float frametime = time1.asMicroseconds();
        int framerate = roundf(pow(10,6)/frametime);
        std::string fps = std::to_string(framerate) + "FPS";
        text->setString(fps);
        //std::cout<<*eat<<'\n';
        //std::cout<<"x: "<<*x<<" y: "<<*y<<"\tVelocity: "<<velocity->x<<" "<<velocity->y<<'\n';
    }

    //window->setActive(false);

}