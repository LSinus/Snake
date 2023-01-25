#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "size.hpp"
#include "snake.hpp"
#include "apple.hpp"
#include "scoreboard.hpp"

#include <iostream>
#include <cmath>

#include "rendering.hpp"

void renderingThread(sf::RenderWindow* window,sf::RectangleShape* background, sf::Text* text, sf::RectangleShape* map, Scoreboard* scoreboard, const Snake* snake, Apple* apple){
    
    window->setActive(true);
    sf::Clock clock;
    sf::Time time1;
    clock.restart();   

    while (window->isOpen()){

        clock.restart();
        //std::cout<<snake->snake.size()<<'\n';
        window->clear(sf::Color(22, 102, 44, 255));
        window->draw(*background);
        //window->draw(*text);

        //window->draw(scoreboard->background);
        window->draw(scoreboard->score);
        window->draw(scoreboard->bestScore);
        //window->draw(*map);
         for(int i=0; i<(apple->apple.size()); i++){
            window->draw(apple->apple[i].circle);
        }
        window->draw(apple->apple[0].circle);
        for(int i=0; i<(snake->body.size()); i++){
            //std::cout<<i<<": "<<snake->body[i].square.getPosition().x<<" "<<snake->body[i].square.getPosition().x<<'\n';
            window->draw(snake->body[i].square);
        }
        //std::cout<<'\n';

        //std::cout<<"change direction detected at: "<<snake->position_change.x<<" "<<snake->position_change.y<<'\n';
        //std::cout<<"next segment position: "<<snake->snake[1].getPosition().x<<" "<<snake->snake[1].getPosition().y<<'\n';
        
        window->display();

        time1 = clock.getElapsedTime();
        float frametime = time1.asMicroseconds();
        int framerate = roundf(pow(10,6)/frametime);
        std::string fps = std::to_string(framerate) + "FPS";
        std::string score = "SCORE: " + std::to_string(snake->body.size()-2);
        text->setString(fps);
        scoreboard->score.setString(score);
        //std::cout<<*eat<<'\n';
        //std::cout<<"x: "<<*x<<" y: "<<*y<<"\tVelocity: "<<velocity->x<<" "<<velocity->y<<'\n';
    }

    //window->setActive(false);

}