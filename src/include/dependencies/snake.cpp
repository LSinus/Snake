#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "size.hpp"


#include <vector>

#include "snake.hpp"


Snake::Snake(const size map_size, const int seed){
    sf::RectangleShape block;
    block.setSize(sf::Vector2f(20.f,20.f));
    block.setFillColor(sf::Color::Blue);
    
    snake.push_back(block);
    generate(map_size, seed);

}

void Snake::generate(const size map_size, const int seed){
    srand(seed);
    position.x = (map_size.start_x + snake[0].getOrigin().x) + (rand() % (int)(map_size.x - snake[0].getOrigin().x));
    position.y = (map_size.start_y + snake[0].getOrigin().y) + (rand() % (int)(map_size.y - snake[0].getOrigin().y));

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
    actual_position.x = prev_position.x + snake[0].getSize().x;
    actual_position.y = prev_position.y;
    block.setPosition(actual_position);


    snake.push_back(block);
}

void Snake::die(){

}

void Snake::move(){

}