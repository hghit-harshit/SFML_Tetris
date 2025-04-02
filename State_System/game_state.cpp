#include "game_state.hpp"
//#include "tetris_piece.hpp"
#include <random>
State_Game::State_Game(StateManager* l_stateManager):BaseState(l_stateManager){}

void State_Game::OnCreate()
{
    // m_texture.loadFromFile("resources/logo.png");
    // m_sprite.setTexture(m_texture);
    // m_sprite.setPosition(0,0);s
    // m_increment= sf::Vector2f(200.0f,200.0f);
    sf::Vector2u l_windowSize = m_stateManager->GetContext()->m_wind->GetWindowSize();
    m_blockSize = l_windowSize.x/10;
    m_grid = std::vector<std::vector<int>>(20,std::vector<int>(10,0));
    m_music.openFromFile("C:\\Users\\hghit\\source\\repos\\SFML_Tetris\\SFML_Tetris\\resources\\tetris_theme.mp3");
    //m_music.play();
    m_music.setLoop(true);
    m_music.setVolume(25.0f);
    //for(int i = 0; i < 10; ++i)m_grid[i][i] = 1;
    EventManager* evmgr = m_stateManager->GetContext()->m_eventManager;
    evmgr->AddCallback(StateType::Game,"Key_Escape",&State_Game::MainMenu,this);
    evmgr->AddCallback(StateType::Game,"Key_Pause",&State_Game::MainMenu,this);
    evmgr->AddCallback(StateType::Game,"Key_Left",&State_Game::MoveLeft,this);
    evmgr->AddCallback(StateType::Game,"Key_Right",&State_Game::MoveRight,this);
    evmgr->AddCallback(StateType::Game,"Key_Change",&State_Game::ChangeOrientation,this);
    SpawnPiece();

}

void State_Game::OnDestroy()
{
    EventManager* evmgr = m_stateManager->GetContext()->m_eventManager;
    evmgr->RemoveCallback(StateType::Game,"Key_Escape");
    evmgr->RemoveCallback(StateType::Game,"Key_Pause");
    evmgr->RemoveCallback(StateType::Game,"Key_Left");
    evmgr->RemoveCallback(StateType::Game,"Key_Right");
}

void State_Game::Activate(){m_music.play();}
void State_Game::Deactivate(){m_music.stop();}

void State_Game::Update(const sf::Time& l_time)
{
    sf::Vector2u l_windowSize = m_stateManager->GetContext()->m_wind->GetWindowSize();
    // sf::Vector2u l_textureSize = m_texture.getSize();

    // if((m_sprite.getPosition().x > l_windowSize.x - l_textureSize.x && m_increment.x > 0) ||
    // (m_sprite.getPosition().x < 0 && m_increment.x < 0))
    // {
    //     m_increment.x = -m_increment.x;
    // }
    // if((m_sprite.getPosition().y > l_windowSize.y - l_textureSize.y && m_increment.y > 0) ||
    // (m_sprite.getPosition().y < 0 && m_increment.y < 0))
    // {
    //     m_increment.y = -m_increment.y;
    // }
    // m_sprite.setPosition(m_sprite.getPosition().x + (m_increment.x * l_time.asSeconds()), 
    // m_sprite.getPosition().y + (m_increment.y * l_time.asSeconds()));

    if(!GameOver())
    {
        if(m_time.asSeconds() >= 0.5)
        {
            Tick();
            m_time = m_clock.restart();
        }
        else{ m_time = m_clock.getElapsedTime();}
    }

}

void State_Game::Draw()
{
    // for(auto row : m_grid)
    // {
    //     for(auto col : row)
    //     {
    //         std::cout << col << ' ';
    //     }
    //     puts("");
    // }
    m_piece->RenderPiece();
    sf::RenderWindow* l_renderwind = m_stateManager->GetContext()->m_wind->GetRenderWindow();
    for(int i = 0; i < m_grid.size(); ++i)
    {
        for(int j = 0; j < m_grid[0].size(); ++j)
        {
            if(m_grid[i][j] == 0)
            {
                sf::RectangleShape temp;
                sf::Vector2f size(m_blockSize-1,m_blockSize-1);
                temp.setSize(size);
                temp.setFillColor(sf::Color::Red);
                temp.setPosition(j*m_blockSize,i*m_blockSize);
                l_renderwind->draw(temp);
            }
            else 
            {
                sf::RectangleShape temp;
                sf::Vector2f size(m_blockSize,m_blockSize);
                temp.setSize(size);
                temp.setFillColor(sf::Color::Yellow);
                temp.setPosition(j*m_blockSize,i*m_blockSize);
                l_renderwind->draw(temp);
            }
        }
    }
}

void State_Game::MainMenu(EventDetails* l_details)
{m_stateManager->SwitchTo(StateType::MainMenu);}

void State_Game::Pause(EventDetails* l_details)
{m_stateManager->SwitchTo(StateType::Paused);}  

inline int rando()
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<>dist(0,INT_MAX);
    
    return dist(gen);
}

void State_Game::SpawnPiece()
{
    //srand(time(NULL));
    int r = rando()%4;
    switch(r)
    {
        case 0:
            m_piece = new Square(m_grid);
            break;
        case 1:
            m_piece = new Triangle(m_grid);
            break;
        case 2:
            m_piece = new LShape(m_grid);
            break;
        case 3:
            m_piece = new IShape(m_grid);
            break;

    }
    
}

void State_Game::MoveDown(){ m_piece->MoveDown();}
void State_Game::MoveRight(EventDetails* l_details){m_piece->MoveRight();}
void State_Game::MoveLeft(EventDetails* l_details){m_piece->MoveLeft();}
void State_Game::ChangeOrientation(EventDetails* l_details){m_piece->ChangeOrientation();}

void State_Game::Tick()
{
    std::cout << "Moving\n";
    if(!m_piece->CheckCollision())MoveDown();
    else 
    {
        for(int i = 2; i < m_grid.size(); ++i)
        {
            if(RowComplete(i))
            {
                //std::cout << "loop\n";
                //std::cout << '\a';
                RemoveRow(i);
                i--;
            }
        }
        delete m_piece;
        SpawnPiece();
    }

}

bool State_Game::RowComplete(int l_row)
{
    for(auto a : m_grid[l_row])
    {
        if(a == 0)return false;
    }
    return true;
}
void State_Game::RemoveRow(int l_row)
{
    for(int i = l_row; i > 0; --i)
    {
        for(int j = 0; j < m_grid[0].size();++j)
        {
            m_grid[i][j] = m_grid[i-1][j];
        }
    }
    for(auto a : m_grid[0])a = 0;
}
bool State_Game::GameOver()
{
    
    return false;
}
