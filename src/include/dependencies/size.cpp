#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <cmath>

float abs(sf::Vector2f vector){
    if(vector.x < 0.f){
        vector.x = -vector.x;
    }

    if(vector.y < 0.f){
        vector.y = -vector.y;
    }

    float res = sqrt(pow(vector.x,2)+pow(vector.y,2));

    return res; 
}