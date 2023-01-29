#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


#include "dependencies/size.hpp"
#include "dependencies/scoreboard.hpp"
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
    sf::RenderWindow window(sf::VideoMode(1020, 600), "Snake", sf::Style::Titlebar | sf::Style::Close);

    window.setActive(false);
    window.setKeyRepeatEnabled(false);

    menu_textures menu_texture;
    sf::Texture apple_texture;
    texture snake_texture;
    backgrounds_shapes background_shape;
    button_shapes button_shape;

    loadTextures(&menu_texture, &apple_texture, &snake_texture, &background_shape, &button_shape);

    sf::RectangleShape map(sf::Vector2f(942.f, 480.f));
    map.setPosition(38.f, 38.f);
    map.setFillColor(sf::Color::White);

    sf::Font font;
    font.loadFromFile("src/fonts/unispace.ttf");

    sf::Event event;

    sf::Vector2f velocity;
    velocity.x = 0;
    velocity.y = 0;

    sf::Time time;
    time = timer.restart();
    int seed = time.asMilliseconds();

    int input = -1;

    size map_size;
    map_size.start_x = map.getPosition().x;
    map_size.start_y = map.getPosition().y;
    map_size.x = map.getSize().x;
    map_size.y = map.getSize().y;
    map_size.end_x = (map.getSize().x + map.getPosition().x);
    map_size.end_y = (map.getSize().y + map.getPosition().y);

    Scoreboard scoreboard(font);

    setScoreboard(&scoreboard, &font);
    
    flags flag;


    Snake snake(map_size, seed, &snake_texture);

    Apple apple(map_size, seed, &apple_texture);
    

    sf::Thread thread(std::bind(&renderingThread, &window, &background_shape, &menu_texture, &button_shape, &map, &scoreboard, &snake, &apple, &flag));
    thread.launch();

    sf::Clock update_timer;
    sf::Time update_clock;

    update_timer.restart();
    int change_direction_countdown = 0;

    double velocity_increment = 5;

    int apple_index;

    while (window.isOpen()){

            while (window.pollEvent(event)){   
                switch (event.type){
                
                    case sf::Event::KeyPressed:
                        //std::cout<<"Tasto premuto: "<<event.key.code<<'\n';
                        input = event.key.code;
                        if(event.key.code==36){
                                flag.isMenuClicked = true;
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
                
                //SCORE POSITION SHIFTING
                if((snake.body.size()-2)/10 > 0){
                    scoreboard.score.setPosition(112,545);
                }
                if(snake.body.size()/10 > 10){
                    scoreboard.score.setPosition(107,545);
                }

                sf::Vector2i mouseposition = sf::Mouse::getPosition(window);
                flag.isMenuSelected = selectMenu(mouseposition);

                //PLAY BUTTON CLICK
                if(flag.isWelcomeMenu){
                    flag.isPlaySelected = selectPlay(mouseposition);
                    flag.isResetSelected = selectReset(mouseposition);
                    flag.isExitSelected = selectExit(mouseposition);
                    if(flag.isPlaySelected && click()){
                        flag.isWelcomeMenu = false;
                    }
                    else if(flag.isResetSelected && click()){
                        scoreboard.resetData();
                        scoreboard.pickUpData();
                    }
                    else if(flag.isExitSelected && click()){
                        scoreboard.saveData();
                        window.close();
                        thread.terminate();
                    }
                }

                if(flag.isMenuSelected && click()){
                    flag.isMenuClicked = true;
                }

                if(flag.isMenuClicked){
                    flag.isResumeSelected = resume(mouseposition);
                    flag.isResetSelected = selectReset(mouseposition);
                    flag.isExitSelected = selectExit(mouseposition);
                    flag.isPlayAgainSelected = selectPlayAgain(mouseposition);
                    if(flag.isResumeSelected && click())
                        flag.isMenuClicked = false;
                    if(flag.isResetSelected && click()){
                        scoreboard.resetData();
                        flag.isResetSelected = false;
                        flag.isMenuClicked = false;
                    }
                    if(flag.isExitSelected && click()){
                        scoreboard.saveData();
                        window.close();
                        thread.terminate();
                    }
                    if(flag.isPlayAgainSelected && click()){
                        scoreboard.saveData();
                        input = -1;
                        Snake snakeTemp(map_size, (seed+rand()), &snake_texture);
                        Apple appleTemp(map_size, (seed+rand()), &apple_texture);
                        snake = snakeTemp;
                        apple = appleTemp;
                        velocity_increment = 5;
                        setScoreboard(&scoreboard, &font);
                        flag.isMenuClicked = false;
                        flag.isPlayAgainSelected = false;
                    }
                }

                if(flag.isLoseMenu){
                    
                    flag.isResetSelected = selectResetLose(mouseposition);
                    flag.isExitSelected = selectExit(mouseposition);
                    flag.isPlayAgainSelected = selectPlayAgainLose(mouseposition);

                    if(flag.isResetSelected && click()){
                        scoreboard.resetData();
                        flag.isResetSelected = false;
                    }
                    if(flag.isExitSelected && click()){
                        scoreboard.saveData();
                        window.close();
                        thread.terminate();
                    }
                    if(flag.isPlayAgainSelected && click()){
                        //scoreboard.saveData();
                        input = -1;
                        Snake snakeTemp(map_size, (seed+rand()), &snake_texture);
                        Apple appleTemp(map_size, (seed+rand()), &apple_texture);
                        snake = snakeTemp;
                        apple = appleTemp;
                        velocity_increment = 5;
                        setScoreboard(&scoreboard, &font);
                        flag.isLoseMenu = false;
                        flag.isPlayAgainSelected = false;
                    }
                }


                update_clock = update_timer.getElapsedTime();
                if(update_clock.asMilliseconds() >= velocity_increment && flag.isMenuClicked == false && flag.isWelcomeMenu == false){
                    //std::cout<<change_direction_countdown<<'\n';
                    flag.isDead = update(&snake, &velocity, &map, &input, &change_direction_countdown, &snake_texture);
                    update_timer.restart();
                }

                flag.eat = apple.eat(snake.body[0].position, &apple_index);
                
                if(flag.eat){
                    apple.eaten(apple_index);
                    apple.generate(map_size, snake, apple_index);
                    snake.grow(&snake_texture);
                    flag.eat = false;    
                }
                if(flag.isDead){
                    scoreboard.saveData();
                    scoreboard.showData();

                    flag.isLoseMenu = true;
                    flag.isDead = false;

                    
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
                flag.isMenuClicked = true;
                window.setFramerateLimit(30);
            }


            //std::cout<<velocity_increment<<'\n';
    }
        

    return 0;
}

