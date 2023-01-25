struct apple_container{
    sf::Sprite circle;
    sf::Vector2f position;
};

class Apple {
    public:
        std::vector<apple_container> apple;

        Apple(const size map_size, const int seed, const sf::Texture* texture);        
        void generate(const size map_size, const Snake snake_body, int index);
        bool eat(sf::Vector2f snake_pos,int* index);
        void eatAnimation(int index);
        void eaten(int index);
        void addApple(const size map_size, const int seed, const sf::Texture* texture);
    
    private:
        sf::Vector2f position;
        
};

