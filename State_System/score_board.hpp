#pragma once
#include <SFML/Graphics.hpp>

class Score_Board
{
    public:
        Score_Board(){};
        Score_Board(float l_length, float l_width, sf::Vector2f l_postion);
        void Update();
        void Render(sf::RenderWindow*& l_window);
        void IncreaseScore();
        //void Draw();

    private:
        sf::Font m_font;
        int m_score;
        //sf::Font m_font;
        sf::Text m_scoreString;
        sf::Text m_scoreText; // wtf i am soooo bad at naming :(
        int m_lines; // lines destroye=
        sf::RectangleShape m_background;
        sf::Texture m_scoreboardTexture;

};
