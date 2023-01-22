#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "dependencies/size.hpp"
#include "dependencies/snake.hpp"
#include "dependencies/utility.hpp"
#include "dependencies/apple.hpp"

#include "dependencies/rendering.hpp"

#include <iostream>
#include <functional>
#include <string>
#include <cmath>


int main(){
    /*
    sf::Texture texture;
    if (!texture.loadFromFile("files/image.png", sf::IntRect(10, 10, 32, 32))){
        std::cerr<<"Impossibile caricare la texture";
    }*/
    sf::Clock timer;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");

    window.setActive(false);
    window.setKeyRepeatEnabled(false);

    sf::Texture grass;
    if (!grass.loadFromFile("src/imgs/grass.jpg")){
        std::cerr<<"Impossibile caricare la texture";
    }
    grass.setSmooth(true);
    sf::RectangleShape map(sf::Vector2f(730.f, 530.f));
    map.setTexture(&grass);
    map.setPosition(30.f, 30.f);
    map.setFillColor(sf::Color::White);

    /*
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(10, 10, 32, 32));
    sprite.setPosition(sf::Vector2f(10.f, 50.f));*/

    std::string frames = "0";

    sf::Font font;
    font.loadFromFile("src/fonts/ARIAL.TTF");
    sf::Text fps;
    fps.setFont(font);
    fps.setString(frames);
    fps.setCharacterSize(24);
    fps.setFillColor(sf::Color::White);
    sf::Event event;

    sf::Vector2f velocity;
    velocity.x = 0;
    velocity.y = 0;

    int input = 3;
    

    sf::Time time;
    time = timer.restart();
    int seed = time.asMilliseconds();


    size map_size;
    map_size.start_x = map.getPosition().x;
    map_size.start_y = map.getPosition().y;
    map_size.x = map.getSize().x;
    map_size.y = map.getSize().y;
    map_size.end_x = (map.getSize().x + map.getPosition().x);
    map_size.end_y = (map.getSize().y + map.getPosition().y);

    //std::cout<<"map_size.start_x: "<<map_size.start_x<<" map_size.x: "<<map_size.x<<" map_size.end_x: "<<map_size.end_x<<'\n';

    Snake snake(map_size, seed);

    Apple apple(map_size, seed, snake.body[0].position);


    bool eat = false;


    sf::Thread thread(std::bind(&renderingThread, &window, &snake, &fps, &map, &velocity, &apple, &eat));
    thread.launch();

    sf::Clock update_timer;
    sf::Time update_clock;

    update_timer.restart();
    int change_direction_countdown = 0;

    double velocity_increment = 5;

    while (window.isOpen()){
        
            while (window.pollEvent(event)){   
                switch (event.type){
                
                    case sf::Event::KeyPressed:
                        //std::cout<<"Tasto premuto: "<<event.key.code<<'\n';
                        input = event.key.code;
                        if(event.key.code==36){
                            window.close();
                            thread.terminate();
                            }
                        break;

                    case sf::Event::Resized:
                        //std::cout<<"New size width:  "<<event.size.width<<'\n';
                        //std::cout<<"New size height: "<<event.size.height<<'\n';
                        break;

                    case sf::Event::Closed:
                        window.close();
                        thread.terminate();
                        break;

                    default:
                        break;
                }
            }

            if(window.hasFocus()){
                update_clock = update_timer.getElapsedTime();
                if(update_clock.asMilliseconds() >= velocity_increment){
                    //std::cout<<change_direction_countdown<<'\n';
                    update(&snake, &velocity, &map, &input, &change_direction_countdown);
                    update_timer.restart();
                }
                
                eat = apple.eat(snake.body[0].position);
                if(eat){
                    //std::cout<<"eat"<<'\n';
                    snake.grow();
                    apple.eaten();
                    apple.generate(map_size, snake.body[0].position);
                    seed++;
                    eat = false;
                    
                }
                if(snake.die()){
                    window.close();
                }
                
                //std::cout<<eat<<'\n';
                window.setFramerateLimit(144);
            }
            else{
                window.setFramerateLimit(30);
            }

            velocity_increment = velocity_increment - .00000001;
            //std::cout<<velocity_increment<<'\n';
    }
        

    return 0;
}

