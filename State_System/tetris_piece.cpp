#include "tetris_piece.hpp"
#include <iostream>
/*TODO
* the check collision is working wierdly so check that
*/
bool Tetris_Piece::CheckCollision()
{
    int row_below = m_position.second + m_tile.size();
    std::cout << row_below << std::endl;
    if(row_below >= m_grid.size())return true;
    for(int i = 0; i < m_tile[0].size(); ++i)
    {
        // int last_one = m_tile.size()-1;
        // j >=0 works because we'll definitely find a 1 before that
        for(int j = m_tile.size()-1; j >= 0; j--)
        {
            if(m_tile[j][i] == 1 && m_grid[m_position.second + j][m_position.first+i] == 1)
            {
                row_below = m_position.second+j+1;
                break;
            }
        }
        
        if(m_grid[row_below][m_position.first+i] != 0)return true;
    }
    return false;
}       

void Tetris_Piece::Clear()
{
    for(int i = 0; i < m_tile.size();++i)
    {
        for(int j = 0; j < m_tile[0].size(); ++j)
        {
            if(m_tile[i][j] == 1)
                m_grid[m_position.second+i][m_position.first+j] = 0;
            //std::cout << "Printing\n";
        }
    }
}

void Tetris_Piece::MoveDown()
{
    Clear();
    m_position.second++;
}
void Tetris_Piece::MoveRight()
{ 
    if(m_position.first + m_tile[0].size() >= m_grid[0].size())return;

    for(int i = 0; i < m_tile.size(); ++i)
    {
        int col_right;
        for(int j = m_position.first + m_tile[0].size()-1; j >= 0;--j)
        {
            if(m_grid[m_position.second+i][j] == 1)
            {
                col_right = j + 1;
                break;
            }
        }
        if(m_grid[m_position.second + i][col_right] != 0 )
        {return;}
    }
    Clear();
    m_position.first++;

}
void Tetris_Piece::MoveLeft()
{
    if(m_position.first == 0)return;
    for(int i = 0; i < m_tile.size(); ++i)
    {
        if(m_grid[m_position.second + i][m_position.first-1] != 0 )
        {return;}
    }
    Clear();
    m_position.first--;
    
}

void Tetris_Piece::RenderPiece()
{
    for(int i = m_position.second; i < m_position.second + m_tile.size() ;++i)
    {
        for(int j = m_position.first; j < m_position.first + m_tile[0].size(); ++j)
        {
            if(m_grid[i][j] == 0)
                m_grid[i][j] = m_tile[i-m_position.second][j-m_position.first];
            //std::cout << "Printing\n";
        }
    }
}

void Tetris_Piece::ChangeOrientation()
{
    int row = m_tile.size();
    int col = m_tile[0].size();
    Grid l_rotated(m_tile[0].size(),std::vector<int>(m_tile.size()));
    for(int i = 0; i < l_rotated.size(); ++i)
    {
        for(int j = 0; j < l_rotated[0].size(); ++j)
        {
            l_rotated[i][j] = m_tile[row - 1 -j][i];
        }
    }
    Clear();
    m_tile = l_rotated;
}