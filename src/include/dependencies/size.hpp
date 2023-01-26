struct size{
    float start_x;
    float start_y;
    int end_x;
    int end_y;
    int x;
    int y;
};

struct texture{
    sf::Texture head[4];
    sf::Texture body[4];
    sf::Texture tail[4];
};


float abs(sf::Vector2f);