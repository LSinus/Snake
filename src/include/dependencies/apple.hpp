class Apple {
    public:
        sf::CircleShape apple;

        Apple(const size map_size, const int seed, const sf::Vector2f snake_pos);        
        void generate(const size map_size, const sf::Vector2f snake_pos);
        bool eat(sf::Vector2f snake_pos);
        void eaten();
    
    private:
        sf::Vector2f position;
        
};

