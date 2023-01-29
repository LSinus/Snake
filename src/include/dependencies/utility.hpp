bool update(Snake* snake, sf::Vector2f* velocity, sf::RectangleShape* map, int* input, int* flag, texture* snake_texture);

bool click();
bool selectMenu(sf::Vector2i);
bool resume(sf::Vector2i);
bool selectPlay(sf::Vector2i);
bool selectReset(sf::Vector2i);
bool selectExit(sf::Vector2i);
bool selectPlayAgain(sf::Vector2i);
bool selectPlayAgainLose(sf::Vector2i);
bool selectResetLose(sf::Vector2i);

void setScoreboard(Scoreboard* scoreboard, sf::Font* font);
void loadTextures(menu_textures* menu_textures, sf::Texture* apple_texture, texture* snake_texture, backgrounds_shapes* backgrounds_shape, button_shapes* button_shape);