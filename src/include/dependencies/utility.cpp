#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <cmath>

#include "size.hpp"
#include "snake.hpp"

#include "utility.hpp"

void update(Snake* snake, sf::Vector2f* velocity, sf::RectangleShape* map, int* input){

    sf::Vector2f position;
    snake->prev_direction = snake->direction[0];

    if (*input == 22){
        snake->direction[0] = 3;
    }

    else if (*input == 0){
        snake->direction[0] = 2;
    }
      
    else if (*input == 18){
        snake->direction[0] = 1;
    }
      
    else if (*input == 3){
        snake->direction[0] = 0;
    }

    if(snake->direction[0] != snake->prev_direction){
        snake->position_change = snake->snake[0].getPosition();
    }
      
    for(int i = 0; i<snake->snake.size();i++){
        sf::Vector2f current_position = snake->snake[i].getPosition();
        if((int)current_position.x == (int)snake->position_change.x  && (int)current_position.y == (int)snake->position_change.y){
            //std::cout<<i<<" ha cambiato posizione\n";
            snake->direction[i] = snake->direction[0];
        }

        switch (snake->direction[i]){
        case 0:
            velocity->y = 0;
            velocity->x = .001f;
            break;
        case 1:
            velocity->x = 0;
            velocity->y = .001f;
            break;
        case 2:
            velocity->y = 0;
            velocity->x = -.001f;
            break;
        case 3:
            velocity->x = 0;
            velocity->y = -.001f;
            break;
        default:
            break;
        }
        position.x = snake->snake[i].getPosition().x;
        position.y = snake->snake[i].getPosition().y;

        position.x += velocity->x;
        position.y += velocity->y;

        snake->snake[i].setPosition(position);
    }

}

