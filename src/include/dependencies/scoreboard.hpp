class Scoreboard{
    public:
        Scoreboard(sf::Font font);
        void pickUpData();
        void saveData();

        sf::RectangleShape background;
        sf::Text score;
        sf::Text bestScore;
};