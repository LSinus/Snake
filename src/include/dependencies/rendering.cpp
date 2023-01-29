#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "size.hpp"
#include "snake.hpp"
#include "apple.hpp"
#include "scoreboard.hpp"

#include <iostream>
#include <cmath>

#include "rendering.hpp"

void renderingThread(sf::RenderWindow* window, backgrounds_shapes* backgrounds_shape, menu_textures* menu_texture, button_shapes* button_shapes,
sf::RectangleShape* map, Scoreboard* scoreboard, const Snake* snake, 
Apple* apple, flags* flag, int* bestscore, int* score){
    
    window->setActive(true);
    sf::Clock clock;
    sf::Time time1;
    clock.restart();   

    while (window->isOpen()){

        clock.restart();
        //std::cout<<snake->snake.size()<<'\n';
        window->clear(sf::Color(22, 102, 44, 255));
        if(flag->isWelcomeMenu){
            window->draw(backgrounds_shape->menu_welcome_background);
            if(flag->isPlaySelected)
                window->draw(button_shapes->playbutton);
            if(flag->isResetSelected)
                window->draw(button_shapes->resetbutton);
            if(flag->isExitSelected)
                window->draw(button_shapes->exitbutton);
        }
        else if(flag->isLoseMenu){
            window->draw(backgrounds_shape->menu_lose_background);
            window->draw(scoreboard->score);
            if(flag->isPlayAgainSelected)
                window->draw(button_shapes->playagainlosebutton);
            if(flag->isResetSelected)
                window->draw(button_shapes->resetlosebutton);
            if(flag->isExitSelected)
                window->draw(button_shapes->exitbutton);
        }

        else if(flag->isMenuClicked){
            window->draw(backgrounds_shape->menu_pause_background);
            if(flag->isResumeSelected)
                window->draw(button_shapes->resumebutton);
            if(flag->isResetSelected)
                window->draw(button_shapes->resetbutton);
            if(flag->isExitSelected)
                window->draw(button_shapes->exitbutton);
            if(flag->isPlayAgainSelected)
                window->draw(button_shapes->playagainbutton);
        }
        else{
            window->draw(backgrounds_shape->background);
            //window->draw(*text);

            //window->draw(scoreboard->background);
            window->draw(scoreboard->score);
            window->draw(scoreboard->bestScore);

            if(flag->isMenuSelected)
                window->draw(button_shapes->menubutton);

            //window->draw(*map);
            for(int i=0; i<(apple->apple.size()); i++){
                window->draw(apple->apple[i].circle);
            }
            window->draw(apple->apple[0].circle);
            for(int i=0; i<(snake->body.size()); i++){
                //std::cout<<i<<": "<<snake->body[i].square.getPosition().x<<" "<<snake->body[i].square.getPosition().x<<'\n';
                window->draw(snake->body[i].square);
            }
        }
        
        
        //std::cout<<'\n';

        //std::cout<<"change direction detected at: "<<snake->position_change.x<<" "<<snake->position_change.y<<'\n';
        //std::cout<<"next segment position: "<<snake->snake[1].getPosition().x<<" "<<snake->snake[1].getPosition().y<<'\n';
        
        window->display();

        std::string score_s = "SCORE: " + std::to_string(snake->body.size()-2);
        scoreboard->score.setString(score_s);
        *bestscore = stoi(scoreboard->pickUpData());
        score_s.erase(0,7);
        *score = stoi(score_s);
        //std::cout<<*eat<<'\n';
        //std::cout<<"x: "<<*x<<" y: "<<*y<<"\tVelocity: "<<velocity->x<<" "<<velocity->y<<'\n';
    }

    //window->setActive(false);

}