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

struct menu_textures{
    sf::Texture frame;
    sf::Texture menu_selected;
    sf::Texture exit_selected;
    sf::Texture reset_selected;
    sf::Texture pause_menu;
    sf::Texture play_again_selected;
    sf::Texture resume_selected;
    sf::Texture welcome_menu;
    sf::Texture play_selected;
    sf::Texture apple_texture;
    sf::Texture lose_menu;
    sf::Texture play_again_lose_selected;
};

struct backgrounds_shapes{
    sf::RectangleShape background;
    sf::RectangleShape menu_welcome_background;
    sf::RectangleShape menu_pause_background;
    sf::RectangleShape menu_lose_background;

};

struct button_shapes{
    sf::RectangleShape playbutton;
    sf::RectangleShape menubutton;
    sf::RectangleShape resumebutton;
    sf::RectangleShape playagainbutton;
    sf::RectangleShape playagainlosebutton;
    sf::RectangleShape exitbutton;
    sf::RectangleShape resetbutton;
    sf::RectangleShape resetlosebutton;
};


struct flags{
    bool isWelcomeMenu = true;
    bool isPlaySelected = false;
    bool isResetSelected = false;
    bool isPlayAgainSelected = false;
    bool isExitSelected = false;
    bool eat = false;
    bool isMenuSelected = false;
    bool isMenuClicked = false;
    bool isResumeSelected = false;
    bool isDead = false;
    bool isLoseMenu = false;
};

float abs(sf::Vector2f);