#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "utility.hpp"

#include "apple.hpp"


void Apple::generate(const size map_size, const int seed){
    srand(seed);
    position.x = (map_size.start_x + apple.getOrigin().x) + (rand() % (int)(map_size.x - apple.getOrigin().x));
    position.y = (map_size.start_y + apple.getOrigin().y) + (rand() % (int)(map_size.y - apple.getOrigin().y));

    flag = false;
    apple.setPosition(position);


    //std::cout<<"x: "<<position.x<<" y: "<<position.y<<'\n';
}

void Apple::eaten(){
    
    position.x = -100;
    position.y = -100;
    apple.setPosition(position);

    //std::cout<<"x: "<<position.x<<" y: "<<position.y<<'\n';
}

bool Apple::eat(sf::Vector2f snake_pos){
    if(snake_pos.x >= (position.x-25.f) && snake_pos.x <= (position.x+25.f) && snake_pos.y >= (position.y-25.f) && snake_pos.y <= (position.y+25.f) ) 
       flag = true;

    return flag;
}

Apple::Apple(const size map_size, const int seed){
    generate(map_size, seed);
    apple.setOrigin(15.f, 15.f);
    apple.setRadius(15.f);
    apple.setFillColor(sf::Color::Red);

    flag = false;
}