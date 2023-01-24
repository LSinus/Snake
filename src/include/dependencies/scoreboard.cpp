#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "scoreboard.hpp"

Scoreboard::Scoreboard(sf::Font font){

    background.setFillColor(sf::Color::Black);
    background.setPosition(800, 30);
    background.setSize(sf::Vector2f(160, 530));


}