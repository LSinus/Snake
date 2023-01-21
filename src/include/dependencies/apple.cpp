#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "size.hpp"

#include "apple.hpp"


void Apple::generate(const size map_size, const int seed){
    srand(seed+12938);
    position.x = (map_size.start_x + apple.getOrigin().x) + (rand() % (int)(map_size.x - apple.getOrigin().x));
    position.y = (map_size.start_y + apple.getOrigin().y) + (rand() % (int)(map_size.y - apple.getOrigin().y));

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
    if(abs(snake_pos - apple.getPosition())<20)
        return true;

    return false;
}

Apple::Apple(const size map_size, const int seed){
    generate(map_size, seed);
    apple.setOrigin(15.f, 15.f);
    apple.setRadius(15.f);
    apple.setFillColor(sf::Color::Red);
}