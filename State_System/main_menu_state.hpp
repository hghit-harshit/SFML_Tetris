#pragma once
#include "state_manager.hpp"

class State_MainMenu : public BaseState
{   
    public:
        State_MainMenu(StateManager* l_stateManager);
        void OnCreate() override;
        void OnDestroy() override;
        
        void Activate() override;
        void Deactivate() override{};

        void Update(const sf::Time& l_time) override;
        void Draw() override;

        void MouseClick(EventDetails* l_details);
    private:
        sf::Text m_text;
        sf::Font m_font;
        sf::Vector2f m_buttonSize;
        sf::Vector2f m_buttonPos;
        unsigned int m_buttonPadding;

        sf::RectangleShape m_rects[3];
        sf::Text m_lables[3];

};

/////////////////////////////////////////////////////////////////////////////////////////////

State_MainMenu::State_MainMenu(StateManager* l_stateManager):BaseState(l_stateManager){}

void State_MainMenu::OnCreate()
{
    m_font.loadFromFile("C:\\Users\\hghit\\source\\repos\\SFML_Tetris\\SFML_Tetris\\resources\\Minecraft.ttf");
    m_text.setFont(m_font);
    m_text.setString(sf::String("MAIN MENU"));
    m_text.setCharacterSize(40);

    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    sf::Vector2u windSize = m_stateManager->GetContext()->m_wind->GetWindowSize();
    m_text.setPosition(windSize.x/2.0f,200);

    m_buttonSize = sf::Vector2f(300.0f, 32.0f);
    m_buttonPos = sf::Vector2f(windSize.x/2.0f,300);
    m_buttonPadding = 4;

    std::string str[3];
    str[0] = "PLAY";
    str[1] = "REPLAY";
    str[2] = "EXIT";

    for(int i = 0; i < 3; ++i)
    {
        sf::Vector2f buttonPos(m_buttonPos.x,m_buttonPos.y + (i*(m_buttonSize.y + m_buttonPadding)));
        m_rects[i].setSize(m_buttonSize);
        m_rects[i].setFillColor(sf::Color::Blue);

        m_rects[i].setOrigin(m_buttonSize.x/2.0f, m_buttonSize.y / 2.0f);
        m_rects[i].setPosition(buttonPos);

        m_lables[i].setFont(m_font);
        m_lables[i].setString(sf::String(str[i]));
        m_lables[i].setCharacterSize(20);

        sf::FloatRect rect = m_lables[i].getLocalBounds();
        m_lables[i].setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);

        m_lables[i].setPosition(buttonPos);
    }
    m_stateManager->GetContext()->m_eventManager->
    AddCallback(StateType::MainMenu,"Mouse_Left",&State_MainMenu::MouseClick,this);
}

void State_MainMenu::OnDestroy()
{
    m_stateManager->GetContext()->m_eventManager->RemoveCallback(StateType::Intro,"Mouse_Left");
}
void State_MainMenu::Activate()
{
    if(m_stateManager->HasState(StateType::Game) && m_lables[0].getString() == "PLAY")
    {
        m_lables[0].setString(sf::String("RESUME"));
        sf::FloatRect textRect = m_lables[0].getLocalBounds();
        m_lables->setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    }
}

void State_MainMenu::MouseClick(EventDetails* l_details)
{
    sf::Vector2i mousePos = l_details->m_mouse;

    float halfx = m_buttonSize.x;
    float halfy = m_buttonSize.y;

    for(int i = 0; i < 3; ++i)
    {
        if(mousePos.x >= m_rects[i].getPosition().x - halfx &&
        mousePos.x <= m_rects[i].getPosition().x + halfx &&
        mousePos.y >= m_rects[i].getPosition().y - halfy &&
        mousePos.y <= m_rects[i].getPosition().y + halfy)
        {
            if(i == 0){m_stateManager->SwitchTo(StateType::Game);}
            else if(i ==1)
            {
                //m_stateManager->Remove(StateType::Game);
                m_stateManager->SwitchTo(StateType::Game);
            }
            else if(i == 2){m_stateManager->GetContext()->m_wind->Close();}
        }
    }
}

void State_MainMenu::Draw()
{
    sf::RenderWindow* window = m_stateManager->GetContext()->m_wind->GetRenderWindow();
    window->draw(m_text);
    for(int i = 0; i < 3; ++i)
    {
        window->draw(m_rects[i]);
        window->draw(m_lables[i]);
    }
}

void State_MainMenu::Update(const sf::Time& l_time)
{
   
}