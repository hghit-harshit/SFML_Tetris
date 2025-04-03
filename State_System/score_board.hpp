#include <SFML/Graphics.hpp>

#pragma once

class Score_Board
{
    public:
        Score_Board(int l_length, int l_width, sf::Vector2f l_postion);
        void Update();
        void Render();
        void Draw();

    private:
        sf::Font m_font;
        int m_score;
        int m_lines; // lines destroyed
        sf::RectangleShape m_background;



};
