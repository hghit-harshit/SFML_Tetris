#include "state_manager.hpp"

class State_GameOver : public BaseState
{
    public:
        State_GameOver(StateManager* l_stateManager);
        void OnCreate() override;
        void OnDestroy() override;
        
        void Activate() override{};
        void Deactivate() override{};

        void Update(const sf::Time& l_time) override{};
        void Draw() override;

        void MouseClick(EventDetails* l_details);
    private:   

    sf::Text m_text;
    sf::Font m_font;
    sf::Vector2f m_buttonSize;
    sf::Vector2f m_buttonPos;
    unsigned int m_buttonPadding;
    sf::RectangleShape m_rect;
    sf::RectangleShape m_rects[2];
    sf::Text m_lables[2];
};