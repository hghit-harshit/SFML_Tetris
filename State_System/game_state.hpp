#pragma once

#include "state_manager.hpp"
#include <SFML/Audio.hpp>
//#include "world.hpp"
#include "tetris_piece.hpp"
#include <vector>

class State_Game:public BaseState
{
    public:
        State_Game(StateManager* l_stateManager);
        void OnCreate() override;
        void OnDestroy() override;
        
        void Activate() override{};
        void Deactivate() override;

        void Update(const sf::Time& l_time) override;
        void Draw() override;

        void MainMenu(EventDetails* l_details);
        void Pause(EventDetails* l_details);
        void MoveLeft(EventDetails* l_details);
        void MoveRight(EventDetails* l_details);
        void ChangeOrientation(EventDetails* l_details);
        void IncreaseTick(EventDetails* l_details);
        void ResetTick(EventDetails* l_details);
        void Tick();
        void MoveDown();
        bool GameOver();
        void SpawnPiece();
        bool RowComplete(int l_row);
        void RemoveRow(int l_row);
    private:
        // sf::Texture m_texture;
        // sf::Sprite m_sprite;
        // sf::Vector2f m_increment;
        int height; // the height of the whoel tetris blocks
        Grid m_grid;
        int m_blockSize;
        Tetris_Piece* m_piece;
        // int m_score;
        // int m_level;
        sf::Clock m_clock;
        sf::Time m_time;
        sf::Music m_music;
        sf::SoundBuffer m_buffer;
        sf::Sound m_collid;
        float m_tickrate;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

