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

    if (*input == 22){
        velocity->x = 0;
        velocity->y = -.0008f;
    }

    else if (*input == 0){
        velocity->y = 0;
        velocity->x = -.0008f;
    }
      
    else if (*input == 18){
        velocity->x = 0;
        velocity->y = .0008f;
    }
      
    else if (*input == 3){
        velocity->y = 0;
        velocity->x = .0008f;
    }
      
    for(int i = 0; i<snake->snake.size();i++){
        position.x = snake->snake[i].getPosition().x;
        position.y = snake->snake[i].getPosition().y;

        position.x += velocity->x;
        position.y += velocity->y;

        snake->snake[i].setPosition(position);
    }

}

