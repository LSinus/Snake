#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "size.hpp"
#include <iostream>

#include "apple.hpp"

Apple::Apple(const size map_size, const int seed, const sf::Vector2f snake_pos){
    srand(seed+12938);
    generate(map_size, snake_pos);
    apple.setRadius(15.f);
    apple.setFillColor(sf::Color::Red);
}

void Apple::generate(const size map_size, const sf::Vector2f snake_pos){
    
    position.x = (map_size.start_x + 50) + (rand() % (int)(map_size.x - 100));  //DA RIVEDERE A VOLTE LA MELA SPAWNA SUL BORDO
    position.y = (map_size.start_y + 50) + (rand() % (int)(map_size.y - 100));

    if(abs(position - snake_pos)<100) //DA RIVEDERE (IMPLEMENTAZIONE ERRATA) AGGIUNGERE CONTROLLO SU OGNI PEZZO DEL SERPENTE
        position.x += 40;
        position.y += 40;

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

