#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <fstream>

#include "scoreboard.hpp"

Scoreboard::Scoreboard(sf::Font font){

    background.setFillColor(sf::Color::Black);
    background.setPosition(800, 30);
    background.setSize(sf::Vector2f(200, 530));


}

std::string Scoreboard::pickUpData(){
    std::ifstream input("bin/data/score.dat", std::ios::binary);
    std::string file_score;

    if(input){
        input.seekg (0, input.end);
        int length = input.tellg();
        input.seekg (0, input.beg);
        //std::cout<<length<<'\n';
        if(length>0){
            char* buffer = new char [length+1];
            input.read(buffer, length);
            buffer[length] = '\0';
            file_score = buffer;
            delete[] buffer;
        }
        else
            file_score = "0";

        input.close();

        return file_score;
    }
    else{
        std::cerr<<"pickUpData()::Impossibile aprire il file score.dat"<<'\n';
        return "NaN";
    }
}

void Scoreboard::saveData(){
    std::ifstream input("bin/data/score.dat", std::ios::binary);
    std::string file_score;

    if(input){
        input.seekg (0, input.end);
        int length = input.tellg();
        input.seekg (0, input.beg);
        //std::cout<<length<<'\n';
        if(length>0){
            char* buffer = new char [length+1];
            input.read(buffer, length);
            buffer[length] = '\0';
            file_score = buffer;
            delete[] buffer;
        }
        else
            file_score = "0";

        input.close();
    }
    else{
        std::cerr<<"saveData()::Impossibile aprire il file score.dat in lettura"<<'\n';
    }

    int file_score_i = std::stoi(file_score);
        std::string current_score_s = score.getString();
        current_score_s.erase(0,7);
        //std::cout<<current_score_s<<'\n';
        int current_score_i = std::stoi(current_score_s);

    if(file_score_i < current_score_i){
        std::ofstream output("bin/data/score.dat", std::ios::out | std::ios::binary);
        //std::cout<<file_score<<'\n';
        if(output){
            output<<current_score_s;
            output.close();
        }
        else{
            std::cerr<<"saveData()::Impossibile aprire il file score.dat in scrittura"<<'\n';
        } 
    }

}