struct block{
    sf::Sprite square;
    sf::Vector2f position;
    sf::Vector2f position_change;
    int direction;
};

class Snake{
    public:
        block head;
        std::vector<block> body;

        Snake(const size map_size, const int seed, const texture* snake_texture);
        void generate(const size map_size, const int seed);
        void grow(const texture* snake_texture);
        void move(const texture* snake_texture);
        bool die();
    private:
        sf::Vector2f position;
        sf::Vector2f map_start;
        sf::Vector2f map_end;
        //0 right, 1 down, 2 left, 3 up
};