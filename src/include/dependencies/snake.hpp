class Snake{
    public:
        int prev_direction;
        sf::Vector2f position_change;
        std::vector<int> direction; 
        std::vector<sf::RectangleShape> snake;
        Snake(const size map_size, const int seed);
        void generate(const size map_size, const int seed);
        void grow();
        void die();
        void move();
    private:
        sf::Vector2f position;
        //0 right, 1 down, 2 left, 3 up
};