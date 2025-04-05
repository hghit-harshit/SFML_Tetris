#include "score_board.hpp"
#include <string>

Score_Board::Score_Board(float l_width, float l_height,sf::Vector2f l_position)
{
    m_scoreboardTexture.loadFromFile("C:\\Users\\hghit\\source\\repos\\SFML_Tetris\\SFML_Tetris\\resources\\scoreboard_texture.png");
    m_font.loadFromFile("C:\\Users\\hghit\\source\\repos\\SFML_Tetris\\SFML_Tetris\\resources\\Minecraft.ttf");
    
    m_background.setSize(sf::Vector2f(l_width,l_height));
    m_background.setPosition(l_position);
    m_background.setTexture(&m_scoreboardTexture);
    
    m_scoreString.setFont(m_font);
    m_scoreString.setCharacterSize(40);
    m_scoreString.setFillColor(sf::Color::Black);
    m_scoreString.setString("SCORE\n");
    sf::FloatRect rect = m_scoreString.getLocalBounds();
    m_scoreString.setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
    m_scoreString.setPosition(l_position.x + l_width/2.0f, 100);

    m_score = 0;
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(40);
    m_scoreText.setString(std::to_string(m_score));
    rect = m_scoreText.getLocalBounds();
    m_scoreText.setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
    m_scoreText.setPosition(l_position.x + l_width/2.0f, 150);
    
}

void Score_Board::IncreaseScore()
{
    m_score += 100;
    m_scoreText.setString(std::to_string(m_score));
    sf::FloatRect rect = m_scoreText.getLocalBounds();
    m_scoreText.setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
}

void Score_Board::Render(sf::RenderWindow*& l_window)
{
    l_window->draw(m_background);
    l_window->draw(m_scoreString);
    l_window->draw(m_scoreText);
}