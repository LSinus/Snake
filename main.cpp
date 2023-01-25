#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "dependencies/size.hpp"
#include "dependencies/snake.hpp"
#include "dependencies/utility.hpp"
#include "dependencies/apple.hpp"
#include "dependencies/scoreboard.hpp"

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
    sf::RenderWindow window(sf::VideoMode(1020, 600), "Snake", sf::Style::Titlebar | sf::Style::Close);

    window.setActive(false);
    window.setKeyRepeatEnabled(false);

    sf::Texture wall;
    if (!wall.loadFromFile("src/imgs/background3.jpg")){
        std::cerr<<"Impossibile caricare la texture";
    }

    sf::Texture grass;
    if (!grass.loadFromFile("src/imgs/grass.jpg")){
        std::cerr<<"Impossibile caricare la texture";
    }

    sf::Texture apple_texture;
    if (!apple_texture.loadFromFile("src/texture/mela.png")){
        std::cerr<<"Impossibile caricare la texture";
    }
    apple_texture.isSmooth();
        //apple_texture.setSmooth(true);

    grass.setSmooth(true);
    wall.setSmooth(true);
    sf::RectangleShape background(sf::Vector2f(1018,600));
    background.setPosition(0.f, 0.f);
    background.setTexture(&wall);
    sf::RectangleShape map(sf::Vector2f(942.f, 480.f));
    map.setTexture(&grass);
    map.setPosition(38.f, 38.f);
    map.setFillColor(sf::Color::White);

    /*
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(10, 10, 32, 32));
    sprite.setPosition(sf::Vector2f(10.f, 50.f));*/

    std::string frames = "0";

    sf::Font font;
    font.loadFromFile("src/fonts/unispace.ttf");
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

    Scoreboard scoreboard(font);

    scoreboard.score.setFont(font);
    scoreboard.score.setCharacterSize(20);
    scoreboard.score.setFillColor(sf::Color::Black);
    scoreboard.score.setString("0");
    scoreboard.score.setPosition(120,545); 

    scoreboard.bestScore.setFont(font);
    scoreboard.bestScore.setCharacterSize(20);
    scoreboard.bestScore.setFillColor(sf::Color::Black);
    std::string best_score = "BEST: " + scoreboard.pickUpData();
    scoreboard.bestScore.setString(best_score);
    if(stoi(scoreboard.pickUpData())/10 == 0){
        scoreboard.bestScore.setPosition(795,545);
    }
    else if(stoi(scoreboard.pickUpData())/10 <= 10){
        scoreboard.bestScore.setPosition(787,545);
    }
    else{
        scoreboard.bestScore.setPosition(780,545);
    }
    

    Snake snake(map_size, seed);

    Apple apple(map_size, seed, &apple_texture);
    


    bool eat = false;


    sf::Thread thread(std::bind(&renderingThread, &window,&background, &fps, &map, &scoreboard, &snake, &apple));
    thread.launch();

    sf::Clock update_timer;
    sf::Time update_clock;

    update_timer.restart();
    int change_direction_countdown = 0;

    double velocity_increment = 5;
    bool isAlmostDead = false;
    bool isDead = false;
    int apple_index;
    bool animation = false;

    while (window.isOpen()){

            while (window.pollEvent(event)){   
                switch (event.type){
                
                    case sf::Event::KeyPressed:
                        //std::cout<<"Tasto premuto: "<<event.key.code<<'\n';
                        input = event.key.code;
                        if(event.key.code==36){
                            scoreboard.saveData();
                            window.close();
                            thread.terminate();
                            }
                        break;

                    case sf::Event::Resized:
                        //std::cout<<"New size width:  "<<event.size.width<<'\n';
                        //std::cout<<"New size height: "<<event.size.height<<'\n';
                        break;

                    case sf::Event::Closed:
                        scoreboard.saveData();
                        window.close();
                        thread.terminate();
                        break;

                    default:
                        break;
                }
            }

            if(window.hasFocus()){
                
                //spostamento scritta score
                if((snake.body.size()-2)/10 > 0){
                    scoreboard.score.setPosition(112,545);
                }
                if(snake.body.size()/10 > 10){
                    scoreboard.score.setPosition(107,545);
                }



                update_clock = update_timer.getElapsedTime();
                if(update_clock.asMilliseconds() >= velocity_increment){
                    //std::cout<<change_direction_countdown<<'\n';
                    isDead = update(&snake, &velocity, &map, &input, &change_direction_countdown);
                    update_timer.restart();
                }

                eat = apple.eat(snake.body[0].position, &apple_index);
                
                if(eat){
                    apple.eaten(apple_index);
                    apple.generate(map_size, snake, apple_index);
                    snake.grow();
                    eat = false;    
                }
                if(isDead){
                    scoreboard.saveData();
                    window.close();
                    thread.terminate();
                }
                
                //std::cout<<eat<<'\n';
                window.setFramerateLimit(144);
                velocity_increment = velocity_increment - .00000003;
                
                if(velocity_increment<3.5 && apple.apple.size() == 1){
                    apple.addApple(map_size, seed, &apple_texture);
                }

                if(velocity_increment<2.5 && apple.apple.size() == 2){
                    apple.addApple(map_size, seed, &apple_texture);
                }
            }
            else{
                window.setFramerateLimit(30);
            }


            //std::cout<<velocity_increment<<'\n';
    }
        

    return 0;
}

