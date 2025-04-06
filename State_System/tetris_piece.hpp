//#include "game_state.hpp"
#include <vector>
#pragma once
using Grid = std::vector<std::vector<int>>;
class Tetris_Piece
{
    public:
        Tetris_Piece(Grid&l_grid):m_grid(l_grid){};
        ~Tetris_Piece() {};
        void MoveDown();
        void MoveLeft();
        void MoveRight();
        void ChangeOrientation();
        bool CheckCollision();
        void RenderPiece();
        void Solidify(); // I am doing this to check gameove condition
        void Clear();
    protected:
        Grid& m_grid;
        Grid m_tile;
        std::pair<int,int> m_position;
    
};

class Square : public Tetris_Piece
{
    public:
        Square(Grid& l_grid):Tetris_Piece(l_grid)
        {
            m_position = {0,0};
            m_tile = {{1,1,},{1,1}};
        }
};

class LShape : public Tetris_Piece
{
    public:
        LShape(Grid& l_grid):Tetris_Piece(l_grid)
        {
        m_tile = {{1,0,0},{1,1,1}};
        }
};

class IShape : public Tetris_Piece
{
    public:
        IShape(Grid& l_grid):Tetris_Piece(l_grid)
        {
            m_tile = {{1},{1},{1}};
        }
};  

class Triangle : public Tetris_Piece
{
    public:
        Triangle(Grid& l_grid):Tetris_Piece(l_grid)
        {
            m_tile = {{0,1,0},{1,1,1}};
        }
};

//////////////////////////////////////////////////////////////////////////////////////


