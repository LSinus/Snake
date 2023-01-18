struct size{
    float start_x;
    float start_y;
    int x;
    int y;
};

void update(sf::RectangleShape* sprite, sf::Vector2f* velocity, float* x, float* y, sf::RectangleShape* map, int* input);
