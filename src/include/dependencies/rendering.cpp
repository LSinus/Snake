#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "utility.hpp"
#include "apple.hpp"

#include <iostream>
#include <cmath>

#include "rendering.hpp"

void renderingThread(sf::RenderWindow* window,const sf::RectangleShape* sprite, sf::Text* text,const float* x,const float*y, sf::RectangleShape* rectangle, sf::Vector2f* velocity, Apple* apple, bool* eat){
    
    window->setActive(true);
    sf::Clock clock;
    sf::Time time1;
    clock.restart();   

    while (window->isOpen()){

        clock.restart();

        window->clear(sf::Color(22, 102, 44, 255));
        window->draw(*text);
        window->draw(*rectangle);
        window->draw(apple->apple);
        window->draw(*sprite);
        window->display();

        time1 = clock.getElapsedTime();
        float frametime = time1.asMicroseconds();
        int framerate = roundf(pow(10,6)/frametime);
        std::string fps = std::to_string(framerate) + "FPS";
        text->setString(fps);
        std::cout<<*eat<<'\n';
        //std::cout<<"x: "<<*x<<" y: "<<*y<<"\tVelocity: "<<velocity->x<<" "<<velocity->y<<'\n';
    }

    //window->setActive(false);

}