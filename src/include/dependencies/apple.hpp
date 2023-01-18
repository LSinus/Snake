class Apple {
    public:
        sf::CircleShape apple;

        Apple(const size map_size, const int seed);        
        void generate(const size map_size, const int seed);
        bool eat(sf::Vector2f snake_pos);
        void eaten();
    
    private:
        sf::Vector2f position;
        bool flag;
        
};

