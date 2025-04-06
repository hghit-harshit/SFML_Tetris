#include "paused_state.hpp"

State_Paused::State_Paused(StateManager* l_stateManager) : BaseState(l_stateManager) {}

void State_Paused::OnCreate()
{
    SetTransparent(true);
    m_font.loadFromFile("C:\\Users\\hghit\\source\\repos\\SFML_Tetris\\SFML_Tetris\\resources\\Minecraft.ttf");
    m_text.setFont(m_font);
    m_text.setString(sf::String("Paused"));
    m_text.setCharacterSize(40);
    m_text.setStyle(sf::Text::Bold);

    sf::Vector2u windSize = m_stateManager->GetContext()->m_wind->GetWindowSize();
    
    m_rect.setSize(sf::Vector2f(windSize));
    m_rect.setPosition(0,0);
    m_rect.setFillColor(sf::Color(0,0,0,150));

    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    m_text.setPosition(windSize.x/2.0f,200);

    m_buttonSize = sf::Vector2f(300.0f, 32.0f);
    m_buttonPos = sf::Vector2f(windSize.x/2.0f,300);
    m_buttonPadding = 4;

    std::string str[3];
    str[0] = "RESUME";
    str[1] = "RESTART";
    str[2] = "MAIN MENU";

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

    EventManager* evmgr = m_stateManager->GetContext()->m_eventManager;
    
    evmgr->AddCallback(StateType::Paused,"Key_Pause",&State_Paused::Unpuase,this);
    evmgr->AddCallback(StateType::Paused,"Mouse_Left",&State_Paused::MouseClick,this);
}

void State_Paused::Unpuase(EventDetails* l_details)
{
    m_stateManager->SwitchTo(StateType::Game);
}

void State_Paused::MouseClick(EventDetails* l_details)
{
    sf::Vector2i mousePos = l_details->m_mouse;

    float halfx = m_buttonSize.x/2.0f;
    float halfy = m_buttonSize.y/2.0f;

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
                m_stateManager->RestartState(StateType::Game);
            }
            else if(i == 2){m_stateManager->SwitchTo(StateType::MainMenu);}
        }
    }
}

void State_Paused::OnDestroy()
{
    m_stateManager->GetContext()->m_eventManager->RemoveCallback(StateType::Paused,"Key_Pause");
}

void State_Paused::Draw()
{
    sf::RenderWindow* wind = m_stateManager->GetContext()->m_wind->GetRenderWindow();
    wind->draw(m_rect);
    wind->draw(m_text);
    for(int i = 0; i < 3; ++i)
    {
        wind->draw(m_rects[i]);
        wind->draw(m_lables[i]);
    }
}