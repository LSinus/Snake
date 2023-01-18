#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <cmath>

#include "utility.hpp"

void update(sf::RectangleShape* sprite, sf::Vector2f* velocity, float* x, float* y, sf::RectangleShape* map, int* input){

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
      
    
    (*x) += velocity->x;
    (*y) += velocity->y;


    size map_size;
    map_size.x = map->getSize().x+map->getPosition().x;
    map_size.y = map->getSize().y+map->getPosition().y;

    //std::cout<<map_size.x<< " "<<map_size.y<<'\n';

    if(*x<map->getPosition().x+sprite->getOrigin().x)
        *x = map->getPosition().x + sprite->getOrigin().x;
        

    else if(*x>map_size.x - sprite->getOrigin().x)
        *x = map_size.x - sprite->getOrigin().x;
        

    else if(*y<map->getPosition().y + sprite->getOrigin().y)
        *y = map->getPosition().y + sprite->getOrigin().y;
        
    else if(*y>map_size.y - sprite->getOrigin().y)
        *y = map_size.y - sprite->getOrigin().y;
        
    else
        sprite->setPosition(*x, *y);
}

