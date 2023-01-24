#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "size.hpp"
#include <iostream>

#include "apple.hpp"

Apple::Apple(const size map_size, const int seed){
    apple_container temp;
    srand(seed+12938);


    temp.circle.setRadius(15.f);
    temp.circle.setFillColor(sf::Color::Red);

    temp.position.x = (map_size.start_x + 50) + (rand() % (int)(map_size.x - 100));  //DA RIVEDERE A VOLTE LA MELA SPAWNA SUL BORDO
    temp.position.y = (map_size.start_y + 50) + (rand() % (int)(map_size.y - 100));
    
    

    temp.circle.setPosition(temp.position);
    apple.push_back(temp);
    
}

void Apple::generate(const size map_size, const sf::Vector2f snake_pos, int index){
    //for(int i=0;i<apple.size();i++){
        position.x = (map_size.start_x + 50) + (rand() % (int)(map_size.x - 100));  //DA RIVEDERE A VOLTE LA MELA SPAWNA SUL BORDO
        position.y = (map_size.start_y + 50) + (rand() % (int)(map_size.y - 100));

        if(abs(position - snake_pos)<100) //DA RIVEDERE (IMPLEMENTAZIONE ERRATA) AGGIUNGERE CONTROLLO SU OGNI PEZZO DEL SERPENTE
            position.x += 40;
            position.y += 40;

        apple[index].circle.setPosition(position);
    //}



    //std::cout<<"x: "<<position.x<<" y: "<<position.y<<'\n';
}

void Apple::eaten(int index){
    
    position.x = -100;
    position.y = -100;
    apple[index].circle.setPosition(position);

    //std::cout<<"x: "<<position.x<<" y: "<<position.y<<'\n';
}

bool Apple::eat(sf::Vector2f snake_pos, int* index){
    for(int i=0;i<apple.size();i++){
        if(abs(snake_pos - apple[i].circle.getPosition())<20){
            *index = i;
            return true;
        }
        
    }

    return false;
}

void Apple::addApple(const size map_size, const int seed){
    apple_container temp;
    srand(seed+12938);


    temp.circle.setRadius(15.f);
    temp.circle.setFillColor(sf::Color::Red);

    temp.position.x = (map_size.start_x + 50) + (rand() % (int)(map_size.x - 100));  //DA RIVEDERE A VOLTE LA MELA SPAWNA SUL BORDO
    temp.position.y = (map_size.start_y + 50) + (rand() % (int)(map_size.y - 100));
    
    

    temp.circle.setPosition(temp.position);
    apple.push_back(temp);
}