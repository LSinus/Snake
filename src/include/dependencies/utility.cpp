#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <cmath>

#include "size.hpp"
#include "snake.hpp"

#include "utility.hpp"

bool update(Snake* snake, sf::Vector2f* velocity, sf::RectangleShape* map, int* input, int* change_direction_countdown, texture* snake_texture){

    std::cout<<*input<<'\n';

    int prev_direction = snake->body[0].direction;
    if((*change_direction_countdown)<=0){
        if (*input == 22 && prev_direction != 1){
            snake->body[0].direction = 3;
            snake->body[0].square.setTexture(snake_texture->head[3], false);
        }

        else if (*input == 0 && prev_direction != 0){
            snake->body[0].direction = 2;
            snake->body[0].square.setTexture(snake_texture->head[2], false);
        }
        
        else if (*input == 18 && prev_direction != 3){
            snake->body[0].direction = 1;
            snake->body[0].square.setTexture(snake_texture->head[1], false);
        }
        
        else if (*input == 3 && prev_direction != 2){
            //snake->body[0].square.setTexture()
            snake->body[0].direction = 0;
            snake->body[0].square.setTexture(snake_texture->head[0], false);
        }/**/

    }

    
    if(snake->body[0].direction != prev_direction){
        snake->body[0].position_change = snake->body[0].square.getPosition();
        *change_direction_countdown = 40;
    }
    
      
    //std::cout<<"direction: "<<snake->body[0].direction<<'\n';

    switch (snake->body[0].direction){
        case 0:
            velocity->y = 0;
            velocity->x = 1.f;
            break;
        case 1:
            velocity->x = 0;
            velocity->y = 1.f;
            break;
        case 2:
            velocity->y = 0;
            velocity->x = -1.f;
            break;
        case 3:
            velocity->x = 0;
            velocity->y = -1.f;
            break;
        default:
            break;
        }

    snake->body[0].position.x += velocity->x;
    snake->body[0].position.y += velocity->y;

    snake->body[0].square.setPosition(snake->body[0].position);

    snake->move(snake_texture);

    (*change_direction_countdown)--;

    return snake->die();
}

