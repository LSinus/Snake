#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "scoreboard.hpp"
#include <iostream>
#include <string>
#include <cmath>

#include "size.hpp"
#include "snake.hpp"

#include "utility.hpp"

bool update(Snake* snake, sf::Vector2f* velocity, sf::RectangleShape* map, int* input, int* change_direction_countdown, texture* snake_texture){

    int prev_direction = snake->body[0].direction;
    if((*change_direction_countdown)<=0){
        if ((*input == 73 || *input == 22) && prev_direction != 1){
            snake->body[0].direction = 3;
            snake->body[0].square.setTexture(snake_texture->head[3], false);
        }

        else if ((*input == 71 || *input == 0) && prev_direction != 0){
            snake->body[0].direction = 2;
            snake->body[0].square.setTexture(snake_texture->head[2], false);
        }
        
        else if ((*input == 74 || *input == 18) && prev_direction != 3){
            snake->body[0].direction = 1;
            snake->body[0].square.setTexture(snake_texture->head[1], false);
        }
        
        else if ((*input == 72 || *input == 3) && prev_direction != 2){
            //snake->body[0].square.setTexture()
            snake->body[0].direction = 0;
            snake->body[0].square.setTexture(snake_texture->head[0], false);
        }/**/

    }

    
    if(snake->body[0].direction != prev_direction){
        snake->body[0].position_change = snake->body[0].square.getPosition();
        *change_direction_countdown = 40;
    }
    
      
    //std::cout<<"direction: "<<snake->body[0].direction<<'\n';

    switch (snake->body[0].direction){
        case 0:
            velocity->y = 0;
            velocity->x = 1.f;
            break;
        case 1:
            velocity->x = 0;
            velocity->y = 1.f;
            break;
        case 2:
            velocity->y = 0;
            velocity->x = -1.f;
            break;
        case 3:
            velocity->x = 0;
            velocity->y = -1.f;
            break;
        default:
            break;
        }

    snake->body[0].position.x += velocity->x;
    snake->body[0].position.y += velocity->y;

    snake->body[0].square.setPosition(snake->body[0].position);

    snake->move(snake_texture);

    (*change_direction_countdown)--;

    return snake->die();
}


bool resume(sf::Vector2i mouseposition){
    if(mouseposition.x >= 360 && mouseposition.y >= 128 && mouseposition.x <= 660 && mouseposition.y <= 176)
        return true;

    return false;
}


bool selectMenu(sf::Vector2i mouseposition){
    if(mouseposition.x >= 477 && mouseposition.y >= 523 && mouseposition.x <= 543 && mouseposition.y <= 559)
        return true;

    return false;
}

bool selectPlay(sf::Vector2i mouseposition){
    if(mouseposition.x >= 360 && mouseposition.y >= 124 && mouseposition.x <= 660 && mouseposition.y <= 240)
        return true;

    return false;
}

bool selectReset(sf::Vector2i mouseposition){
    if(mouseposition.x >= 360 && mouseposition.y >= 258 && mouseposition.x <= 660 && mouseposition.y <= 307)
        return true;

    return false;
}

bool selectExit(sf::Vector2i mouseposition){
    if(mouseposition.x >= 360 && mouseposition.y >= 429 && mouseposition.x <= 660 && mouseposition.y <= 478)
        return true;

    return false;
}

bool selectPlayAgain(sf::Vector2i mouseposition){
    if(mouseposition.x >= 360 && mouseposition.y >= 191 && mouseposition.x <= 660 && mouseposition.y <= 240)
        return true;

    return false;
}

bool selectPlayAgainLose(sf::Vector2i mouseposition){
    if(mouseposition.x >= 360 && mouseposition.y >= 237 && mouseposition.x <= 660 && mouseposition.y <= 352)
        return true;

    return false;
}

bool selectResetLose(sf::Vector2i mouseposition){
    if(mouseposition.x >= 360 && mouseposition.y >= 369 && mouseposition.x <= 660 && mouseposition.y <= 418)
        return true;

    return false;
}

bool click(){
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        return true;
    

    return false;
}


void setScoreboard(Scoreboard* scoreboard, sf::Font* font){
    scoreboard->score.setFont(*font);
    scoreboard->score.setCharacterSize(20);
    scoreboard->score.setFillColor(sf::Color::Black);
    scoreboard->score.setString("0");
    scoreboard->score.setPosition(120,545); 

    scoreboard->bestScore.setFont(*font);
    scoreboard->bestScore.setCharacterSize(20);
    scoreboard->bestScore.setFillColor(sf::Color::Black);
    std::string best_score = "BEST: " + scoreboard->pickUpData();
    scoreboard->bestScore.setString(best_score);
    
    if(stoi(scoreboard->pickUpData())/10 == 0){
        scoreboard->bestScore.setPosition(815,545);
    }
    else if(stoi(scoreboard->pickUpData())/10 <= 10){
        scoreboard->bestScore.setPosition(807,545);
    }
    else{
        scoreboard->bestScore.setPosition(800,545);
    }

}

void loadTextures(menu_textures* menu_texture, sf::Texture* apple_texture, texture* snake_texture, backgrounds_shapes* background_shape, 
button_shapes* button_shape){
    
    if (!menu_texture->frame.loadFromFile("src/imgs/background4.jpg")){
        std::cerr<<"Impossibile caricare la texture";
    }
    if (!menu_texture->menu_selected.loadFromFile("src/imgs/menu_selected.png")){
        std::cerr<<"Impossibile caricare la texture";
    }

    //GENERAL MENU TEXTURES
    if (!menu_texture->exit_selected.loadFromFile("src/imgs/exit_selected.png")){
        std::cerr<<"Impossibile caricare la texture";
    }
    if (!menu_texture->reset_selected.loadFromFile("src/imgs/reset_selected.png")){
        std::cerr<<"Impossibile caricare la texture";
    }

    //PAUSE MENU TEXTURES
    if (!menu_texture->pause_menu.loadFromFile("src/imgs/menu_pause_background.png")){
        std::cerr<<"Impossibile caricare la texture";
    }
    if (!menu_texture->play_again_selected.loadFromFile("src/imgs/play_again_selected.png")){
        std::cerr<<"Impossibile caricare la texture";
    }
    if (!menu_texture->resume_selected.loadFromFile("src/imgs/resume_selected.png")){
        std::cerr<<"Impossibile caricare la texture";
    }

    //WELCOME MENU TEXTURES
    if (!menu_texture->welcome_menu.loadFromFile("src/imgs/welcome_menu.png")){
        std::cerr<<"Impossibile caricare la texture";
    }
    if (!menu_texture->play_selected.loadFromFile("src/imgs/play_selected.png")){
        std::cerr<<"Impossibile caricare la texture";
    }

    //LOSE MENU TEXTURES
    if (!menu_texture->lose_menu.loadFromFile("src/imgs/lose_menu.png")){
        std::cerr<<"Impossibile caricare la texture";
    }
    if (!menu_texture->play_again_lose_selected.loadFromFile("src/imgs/play_again_lose_selected.png")){
        std::cerr<<"Impossibile caricare la texture";
    }

    //APPLE TEXTURE
    if (!apple_texture->loadFromFile("src/texture/mela.png")){
        std::cerr<<"Impossibile caricare la texture";
    }

    //SNAKE TEXTURES

     //body texture
    if (!snake_texture->body[0].loadFromFile("src/texture/body_0.png")){
        std::cerr<<"Impossibile caricare la texture";
    }
    if (!snake_texture->body[1].loadFromFile("src/texture/body_1.png")){
        std::cerr<<"Impossibile caricare la texture";
    }
    if (!snake_texture->body[2].loadFromFile("src/texture/body_2.png")){
        std::cerr<<"Impossibile caricare la texture";
    }
    if (!snake_texture->body[3].loadFromFile("src/texture/body_3.png")){
        std::cerr<<"Impossibile caricare la texture";
    }

    //head texture
    if (!snake_texture->head[0].loadFromFile("src/texture/head_0.png")){
        std::cerr<<"Impossibile caricare la texture";
    }
    if (!snake_texture->head[1].loadFromFile("src/texture/head_1.png")){
        std::cerr<<"Impossibile caricare la texture";
    }
    if (!snake_texture->head[2].loadFromFile("src/texture/head_2.png")){
        std::cerr<<"Impossibile caricare la texture";
    }
    if (!snake_texture->head[3].loadFromFile("src/texture/head_3.png")){
        std::cerr<<"Impossibile caricare la texture";
    }

    //tail texture
    if (!snake_texture->tail[0].loadFromFile("src/texture/tail_0.png")){
        std::cerr<<"Impossibile caricare la texture";
    }
    if (!snake_texture->tail[1].loadFromFile("src/texture/tail_1.png")){
        std::cerr<<"Impossibile caricare la texture";
    }
    if (!snake_texture->tail[2].loadFromFile("src/texture/tail_2.png")){
        std::cerr<<"Impossibile caricare la texture";
    }
    if (!snake_texture->tail[3].loadFromFile("src/texture/tail_3.png")){
        std::cerr<<"Impossibile caricare la texture";
    }

    //GAME BACKGROUND
    background_shape->background.setSize(sf::Vector2f(1020,600));
    background_shape->background.setPosition(0.f, 0.f);
    background_shape->background.setTexture(&(menu_texture->frame));

    //WELCOME MENU BACKGROUND
    background_shape->menu_welcome_background.setSize(sf::Vector2f(1020,600));
    background_shape->menu_welcome_background.setPosition(0.f, 0.f);
    background_shape->menu_welcome_background.setTexture(&(menu_texture->welcome_menu));

    //PAUSE MENU BACKGROUND
    background_shape->menu_pause_background.setSize(sf::Vector2f(1020,600));
    background_shape->menu_pause_background.setPosition(0.f, 0.f);
    background_shape->menu_pause_background.setTexture(&(menu_texture->pause_menu));

    //LOSE MENU BACKGROUND
    background_shape->menu_lose_background.setSize(sf::Vector2f(1020,600));
    background_shape->menu_lose_background.setPosition(0.f, 0.f);
    background_shape->menu_lose_background.setTexture(&(menu_texture->lose_menu));
    
    //MENU BUTTON
    button_shape->menubutton.setSize(sf::Vector2f(70.f,41.f));
    button_shape->menubutton.setTexture(&menu_texture->menu_selected);
    button_shape->menubutton.setPosition(475,521);

    //PLAY BUTTON
    button_shape->playbutton.setSize(sf::Vector2f(304.f,120.f));
    button_shape->playbutton.setTexture(&menu_texture->play_selected);
    button_shape->playbutton.setPosition(358, 124);


    //RESET SCORE BUTTON
    button_shape->resetbutton.setSize(sf::Vector2f(304.f,54.f));
    button_shape->resetbutton.setTexture(&menu_texture->reset_selected);
    button_shape->resetbutton.setPosition(358, 256);

    //EXIT BUTTON
    button_shape->exitbutton.setSize(sf::Vector2f(304.f,54.f));
    button_shape->exitbutton.setTexture(&menu_texture->exit_selected);
    button_shape->exitbutton.setPosition(358, 421);

    //RESUME BUTTON
    button_shape->resumebutton.setSize(sf::Vector2f(304.f,54.f));
    button_shape->resumebutton.setTexture(&menu_texture->resume_selected);
    button_shape->resumebutton.setPosition(358, 126);

    //PLAY AGAIN BUTTON
    button_shape->playagainbutton.setSize(sf::Vector2f(304.f,54.f));
    button_shape->playagainbutton.setTexture(&menu_texture->play_again_selected);
    button_shape->playagainbutton.setPosition(358, 190);

    //PLAY AGAIN (LOSE) BUTTON
    button_shape->playagainlosebutton.setSize(sf::Vector2f(304.f,120.f));
    button_shape->playagainlosebutton.setTexture(&menu_texture->play_again_lose_selected);
    button_shape->playagainlosebutton.setPosition(358, 234);

    //RESET SCORE (LOSE) BUTTON
    button_shape->resetlosebutton.setSize(sf::Vector2f(304.f,54.f));
    button_shape->resetlosebutton.setTexture(&menu_texture->reset_selected);
    button_shape->resetlosebutton.setPosition(358, 363);

}