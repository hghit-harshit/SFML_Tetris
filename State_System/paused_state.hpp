#pragma once
#include "state_manager.hpp"

class State_Paused : public BaseState
{   
    public:
        State_Paused(StateManager* l_stateManager);
        void OnCreate() override;
        void OnDestroy() override;
        
        void Activate() override {};
        void Deactivate() override{};

        void Update(const sf::Time& l_time) override {};
        void Draw() override;

        void Unpuase(EventDetails* l_details);
        void MouseClick(EventDetails* l_details);
    private:
        sf::Font m_font;
        sf::Text m_text;
        sf::RectangleShape m_rect;

        sf::Vector2f m_buttonSize;
        sf::Vector2f m_buttonPos;
        unsigned int m_buttonPadding;

        sf::RectangleShape m_rects[3];
        sf::Text m_lables[3];


};

////////////////////////////////////////////////////////////////////////////////////////

