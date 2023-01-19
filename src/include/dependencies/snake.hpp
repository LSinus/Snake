class Snake{
    public:
        std::vector<sf::RectangleShape> snake;
        Snake(const size map_size, const int seed);
        void generate(const size map_size, const int seed);
        void grow();
        void die();
        void move();
        int level(); 
    private:
        sf::Vector2f position;
};