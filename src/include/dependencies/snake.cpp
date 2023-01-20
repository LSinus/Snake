#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "size.hpp"
#include <iostream>

#include <vector>

#include "snake.hpp"


Snake::Snake(const size map_size, const int seed){
    direction.push_back(0);
    sf::RectangleShape block;
    block.setSize(sf::Vector2f(20.f,20.f));
    block.setFillColor(sf::Color::Blue);
    
    snake.push_back(block);
    generate(map_size, seed);

}

void Snake::generate(const size map_size, const int seed){
    srand(seed);
    position.x = (int)(map_size.start_x + snake[0].getOrigin().x) + (rand() % (int)(map_size.x - snake[0].getOrigin().x));
    position.y = (int)(map_size.start_y + snake[0].getOrigin().y) + (rand() % (int)(map_size.y - snake[0].getOrigin().y));

    snake[0].setPosition(position);
}

void Snake::grow(){
    sf::RectangleShape block;
    block.setSize(sf::Vector2f(20.f,20.f));
    block.setFillColor(sf::Color::Blue);
    
    sf::Vector2f prev_position;
    prev_position.x = snake[snake.size()-1].getPosition().x;
    prev_position.y = snake[snake.size()-1].getPosition().y;

    sf::Vector2f actual_position;
    switch (direction[direction.size()-1]){
        case 0:
            actual_position.x = prev_position.x - snake[0].getSize().x;
            actual_position.y = prev_position.y;
            break;
        case 1:
            actual_position.x = prev_position.x;
            actual_position.y = prev_position.y - snake[0].getSize().y;
            break;
        case 2:
            actual_position.x = prev_position.x + snake[0].getSize().x;
            actual_position.y = prev_position.y;
            break;
        case 3:
            actual_position.x = prev_position.x;
            actual_position.y = prev_position.y + snake[0].getSize().y;
            break;
        default:
            break;
    }
    block.setPosition(actual_position);

    int prev_direction = direction[direction.size()-1];
    direction.push_back(prev_direction);
    snake.push_back(block);
}

void Snake::die(){

}

void Snake::move(){

}