#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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

    sf::RectangleShape snake(sf::Vector2f(30.f, 30.f));
    snake.setOrigin(15.f, 15.f);
    snake.setPosition(200.f, 200.f);
    snake.setFillColor(sf::Color(99,31,19,255));

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

    float x, y;
    x=50.f;
    y=50.f;

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
    map_size.x = map.getSize().x+map.getPosition().x;
    map_size.y = map.getSize().y+map.getPosition().y;
    Apple apple(map_size, seed);
    

    bool eat = false;


    sf::Thread thread(std::bind(&renderingThread, &window, &snake, &fps, &x, &y, &map, &velocity, &apple, &eat));
    thread.launch();

    
    while (window.isOpen())
    {
        
            while (window.pollEvent(event))
            {   
                switch (event.type){
                
                    case sf::Event::KeyPressed:
                        std::cout<<"Tasto premuto: "<<event.key.code<<'\n';
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
                update(&snake, &velocity, &x, &y, &map, &input);
                eat = apple.eat(snake.getPosition());
                if(eat){
                    //std::cout<<"eat"<<'\n';
                    snake.setSize(sf::Vector2f(snake.getSize().x*2,snake.getSize().y));
                    apple.eaten();
                    apple.generate(map_size, seed);
                    seed++;
                    eat = false;
                    
                }
                
                //std::cout<<eat<<'\n';
                window.setFramerateLimit(144);
            }
            else{
                window.setFramerateLimit(30);
            }
    }
        

    return 0;
}

