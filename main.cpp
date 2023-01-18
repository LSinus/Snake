#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <string>
#include <cmath>

struct size{
    float start_x;
    float start_y;
    int x;
    int y;
};

class Apple {
    public:
        sf::CircleShape apple;

        Apple(const size map_size, const int seed){
            generate(map_size, seed);
            apple.setOrigin(15.f, 15.f);
            apple.setRadius(15.f);
            apple.setFillColor(sf::Color::Red);

            flag = false;
        };
        
        void generate(const size map_size, const int seed);
        bool eat(sf::Vector2f snake_pos);
        void eaten();
    
    private:
        sf::Vector2f position;
        bool flag;

        
};

void Apple::generate(const size map_size, const int seed){
    srand(seed);
    position.x = (map_size.start_x + apple.getOrigin().x) + (rand() % (int)(map_size.x - apple.getOrigin().x));
    position.y = (map_size.start_y + apple.getOrigin().y) + (rand() % (int)(map_size.y - apple.getOrigin().y));

    flag = false;
    apple.setPosition(position);


    //std::cout<<"x: "<<position.x<<" y: "<<position.y<<'\n';
}

void Apple::eaten(){
    
    position.x = -100;
    position.y = -100;
    apple.setPosition(position);

    //std::cout<<"x: "<<position.x<<" y: "<<position.y<<'\n';
}

bool Apple::eat(sf::Vector2f snake_pos){
    if(snake_pos.x >= (position.x-25.f) && snake_pos.x <= (position.x+25.f) && snake_pos.y >= (position.y-25.f) && snake_pos.y <= (position.y+25.f) ) 
       flag = true;

    return flag;
}

 
void update(sf::RectangleShape* sprite, sf::Vector2f* velocity, float* x, float* y, sf::RectangleShape* map, int* input){

    if (*input == 22){
        velocity->x = 0;
        velocity->y = -.0008f;
    }

    else if (*input == 0){
        velocity->y = 0;
        velocity->x = -.0008f;
    }
      
    else if (*input == 18){
        velocity->x = 0;
        velocity->y = .0008f;
    }
      
    else if (*input == 3){
        velocity->y = 0;
        velocity->x = .0008f;
    }
      
    
    (*x) += velocity->x;
    (*y) += velocity->y;


    size map_size;
    map_size.x = map->getSize().x+map->getPosition().x;
    map_size.y = map->getSize().y+map->getPosition().y;

    //std::cout<<map_size.x<< " "<<map_size.y<<'\n';

    if(*x<map->getPosition().x+sprite->getOrigin().x)
        *x = map->getPosition().x + sprite->getOrigin().x;
        

    else if(*x>map_size.x - sprite->getOrigin().x)
        *x = map_size.x - sprite->getOrigin().x;
        

    else if(*y<map->getPosition().y + sprite->getOrigin().y)
        *y = map->getPosition().y + sprite->getOrigin().y;
        
    else if(*y>map_size.y - sprite->getOrigin().y)
        *y = map_size.y - sprite->getOrigin().y;
        
    else
        sprite->setPosition(*x, *y);
}


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
    if (!grass.loadFromFile("files/grass.jpg")){
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
    font.loadFromFile("files/ARIAL.TTF");
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

