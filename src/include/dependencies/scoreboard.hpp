class Scoreboard{
    public:
        Scoreboard(sf::Font font);
        std::string pickUpData();
        void saveData();
        void resetData();
        void showData();

        sf::RectangleShape background;
        sf::Text score;
        sf::Text bestScore;
};