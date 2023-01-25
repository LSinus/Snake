#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "size.hpp"
#include "snake.hpp"
#include <fstream>
#include <iostream>

#include "apple.hpp"

Apple::Apple(const size map_size, const int seed, const sf::Texture* texture){
    apple_container temp;
    srand(seed+12938);



    //temp.circle.setRadius(15.f);
    //temp.circle.setFillColor(sf::Color::Red);
    temp.circle.setTexture(*texture, false);


    //for(int i=0;i<1000;i++){
    temp.position.x = (map_size.start_x + 70) + (rand() % (int)(map_size.x - 120));  //DA RIVEDERE A VOLTE LA MELA SPAWNA SUL BORDO
    temp.position.y = (map_size.start_y + 70) + (rand() % (int)(map_size.y - 120));

    //}

    
    

    temp.circle.setPosition(temp.position);
    apple.push_back(temp);
    
}

void Apple::generate(const size map_size, const Snake snake, int index){
    apple[index].circle.setScale(1,1);

    bool over_forbidden_position = false;
    do{ 
        over_forbidden_position = false;
        position.x = (map_size.start_x + 70) + (rand() % (int)(map_size.x - 120));  //DA RIVEDERE A VOLTE LA MELA SPAWNA SUL BORDO
        position.y = (map_size.start_y + 70) + (rand() % (int)(map_size.y - 120));

        for(int i=0;i<snake.body.size();i++){
            if(abs(position - snake.body[i].position)<50)
                over_forbidden_position = true;
        }
        if(apple.size()>1){
            for(int i=0; i<apple.size();i++){
                if(i!=index && abs(position - apple[i].position)<100)
                    over_forbidden_position = true;
            }
        }
    
    }while(over_forbidden_position);
        

        /*if(abs(position - snake_pos)<100) //DA RIVEDERE (IMPLEMENTAZIONE ERRATA) AGGIUNGERE CONTROLLO SU OGNI PEZZO DEL SERPENTE
            position.x += 40;
            position.y += 40;*/

    apple[index].circle.setPosition(position);
    //}



    //std::cout<<"x: "<<position.x<<" y: "<<position.y<<'\n';
}

void Apple::eatAnimation(int index){
    apple[index].circle.setScale(3,3);
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

void Apple::addApple(const size map_size, const int seed, const sf::Texture* texture){
    apple_container temp;
    srand(seed+12938);


    //temp.circle.setRadius(15.f);
    //temp.circle.setFillColor(sf::Color::Red);
    temp.circle.setTexture(*texture, false);

    temp.position.x = (map_size.start_x + 50) + (rand() % (int)(map_size.x - 100));  //DA RIVEDERE A VOLTE LA MELA SPAWNA SUL BORDO
    temp.position.y = (map_size.start_y + 50) + (rand() % (int)(map_size.y - 100));
    
    

    temp.circle.setPosition(temp.position);
    apple.push_back(temp);
}