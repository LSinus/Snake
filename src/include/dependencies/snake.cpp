#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "size.hpp"
#include <iostream>

#include <vector>

#include "snake.hpp"


Snake::Snake(const size map_size, const int seed, const texture* snake_texture){
    srand(seed);
    /*head.square.setSize(sf::Vector2f(20.f,20.f));
    head.square.setFillColor(sf::Color::Blue);*/
    generate(map_size, seed);
    
    head.direction = (int)rand()%4;
    if(head.direction == 0){
        head.square.setTexture(snake_texture->head[0], false);
    }
    else if(head.direction == 1){
        head.square.setTexture(snake_texture->head[1], false);
    }
    else if(head.direction == 2){
        head.square.setTexture(snake_texture->head[2], false);
    }
    else if(head.direction == 3){
        head.square.setTexture(snake_texture->head[3], false);
    }
    

    body.push_back(head);
    
    grow(snake_texture);

    map_start.x = map_size.start_x;
    map_start.y = map_size.start_y;

    map_end.x = map_size.end_x;
    map_end.y = map_size.end_y;


}

void Snake::generate(const size map_size, const int seed){
    srand(seed);
    head.position.x = (int)(map_size.start_x + head.square.getOrigin().x)*4 + (rand() % (int)((map_size.x - head.square.getOrigin().x)/2));
    head.position.y = (int)(map_size.start_y + head.square.getOrigin().y)*4 + (rand() % (int)((map_size.y - head.square.getOrigin().y)/2));

    head.square.setPosition(position);
}

void Snake::grow(const texture* snake_texture){
    block temp;
    int last = body.size()-1;
    temp.direction = body[last].direction;
    
    if(temp.direction == 0){
        temp.square.setTexture(snake_texture->tail[0], false);
    }
    else if(temp.direction == 1){
        temp.square.setTexture(snake_texture->tail[1], false);
    }
    else if(temp.direction == 2){
        temp.square.setTexture(snake_texture->tail[2], false);
    }
    else if(temp.direction == 3){
        temp.square.setTexture(snake_texture->tail[3], false);
    }

    sf::Vector2f prev_position;

    prev_position = body[last].position;

    //std::cout<<prev_position.x<<" "<<prev_position.y<<'\n';

    switch (body[last].direction){
        case 0:
            temp.position.x = prev_position.x - 24;//body[last].square.getSize().x;
            temp.position.y = prev_position.y;
            break;
        case 1:
            temp.position.x = prev_position.x;
            temp.position.y = prev_position.y - 24;//body[last].square.getSize().y;
            break;
        case 2:
            temp.position.x = prev_position.x + 24;//body[last].square.getSize().x;
            temp.position.y = prev_position.y;
            break;
        case 3:
            temp.position.x = prev_position.x;
            temp.position.y = prev_position.y + 24;//body[last].square.getSize().y;
            break;
        default:
            break;
    }
    temp.square.setPosition(temp.position);
    body.push_back(temp);

    if(body.size()>2){
        if(body[last].direction == 0){
            body[last].square.setTexture(snake_texture->body[0], false);
        }
        else if(body[last].direction == 1){
            body[last].square.setTexture(snake_texture->body[1], false);
        }
        else if(body[last].direction == 2){
            body[last].square.setTexture(snake_texture->body[2], false);
        }
        else if(body[last].direction == 3){
            body[last].square.setTexture(snake_texture->body[3], false);
        }
    }
}


void Snake::move(const texture* snake_texture){
    int size = body.size();
    if(size>1){
        for(int i=1; i<size; i++){
            //std::cout<<i<<": "<<body[i].direction<<" "<<i-1<<": "<<body[i-1].direction<<'\n';
            //std::cout<<"position change: "<<body[i-1].position_change.x<<" "<<body[i-1].position_change.y<<'\n';
            //std::cout<<"position: "<<body[i].position.x<<" "<<body[i].position.y<<'\n';
            switch (body[i].direction){
                case 0:
                    body[i].position.x += 1.f;
                    break;
                case 1:
                    body[i].position.y += 1.f;
                    break;
                case 2:
                    body[i].position.x -= 1.f;
                    break;
                case 3:
                    body[i].position.y -= 1.f;
                    break;
                default:
                    break;
            }
        
        
            if(body[i].direction != body[i-1].direction && body[i].position == body[i-1].position_change){
                body[i].direction = body[i-1].direction;
                if(i<size-1){
                    if(body[i].direction == 0){
                        body[i].square.setTexture(snake_texture->body[0], false);
                    }
                    else if(body[i].direction == 1){
                        body[i].square.setTexture(snake_texture->body[1], false);
                    }
                    else if(body[i].direction == 2){
                        body[i].square.setTexture(snake_texture->body[2], false);
                    }
                    else if(body[i].direction == 3){
                        body[i].square.setTexture(snake_texture->body[3], false);
                    }
                }
                else{
                    if(body[i].direction == 0){
                        body[i].square.setTexture(snake_texture->tail[0], false);
                    }
                    else if(body[i].direction == 1){
                        body[i].square.setTexture(snake_texture->tail[1], false);
                    }
                    else if(body[i].direction == 2){
                        body[i].square.setTexture(snake_texture->tail[2], false);
                    }
                    else if(body[i].direction == 3){
                        body[i].square.setTexture(snake_texture->tail[3], false);
                    }
                }
                body[i].position_change = body[i].position;
            }
        


            body[i].square.setPosition(body[i].position);
            //std::cout<<"\n";
        }
    }
}

bool Snake::die(){
    int size = body.size();
    if(size>1)
        for(int i=2; i<size; i++){
            if(abs(body[0].position - body[i].position)<20)
                return true;
        }

        if(body[0].position.x < map_start.x || body[0].position.x > map_end.x-20 || body[0].position.y < map_start.y || body[0].position.y > map_end.y-20)
            return true;
 
    return false;
}