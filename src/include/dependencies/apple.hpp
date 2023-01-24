struct apple_container{
    sf::CircleShape circle;
    sf::Vector2f position;
};

class Apple {
    public:
        std::vector<apple_container> apple;

        Apple(const size map_size, const int seed);        
        void generate(const size map_size, const Snake snake_body, int index);
        bool eat(sf::Vector2f snake_pos,int* index);
        void eaten(int index);
        void addApple(const size map_size, const int seed);
    
    private:
        sf::Vector2f position;
        
};

