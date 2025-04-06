#include "game_state.hpp"
//#include "tetris_piece.hpp"
#include <random>
State_Game::State_Game(StateManager* l_stateManager):BaseState(l_stateManager){}

void State_Game::OnCreate()
{
    sf::Vector2u l_windowSize = m_stateManager->GetContext()->m_wind->GetWindowSize();
    m_blockSize = l_windowSize.x/20;
    m_grid = std::vector<std::vector<int>>(20,std::vector<int>(10,0));

    m_scoreBoard = new Score_Board(400,800,sf::Vector2f(400,0));
    
    m_buffer.loadFromFile("C:\\Users\\hghit\\source\\repos\\SFML_Tetris\\SFML_Tetris\\resources\\collid.mp3");
    m_collid.setBuffer(m_buffer);
    m_backgroundTexture.loadFromFile("C:\\Users\\hghit\\source\\repos\\SFML_Tetris\\SFML_Tetris\\resources\\blue_texture.png");
    m_tileTexture.loadFromFile("C:\\Users\\hghit\\source\\repos\\SFML_Tetris\\SFML_Tetris\\resources\\pink_texture.png");
    //m_collid.setPlayingOffset(sf::seconds(0.75));
    m_tickrate = 0.5;
    //for(int i = 0; i < 10; ++i)m_grid[i][i] = 1;
    EventManager* evmgr = m_stateManager->GetContext()->m_eventManager;
    //evmgr->AddCallback(StateType::Game,"Key_Escape",&State_Game::MainMenu,this);
    //evmgr->AddCallback(StateType::Game,"Key_Pause",&State_Game::MainMenu,this);
    evmgr->AddCallback(StateType::Game,"Key_Left",&State_Game::MoveLeft,this);
    evmgr->AddCallback(StateType::Game,"Key_Right",&State_Game::MoveRight,this);
    evmgr->AddCallback(StateType::Game,"Key_Change",&State_Game::ChangeOrientation,this);
    evmgr->AddCallback(StateType::Game,"Key_Increase",&State_Game::IncreaseTick,this);
    evmgr->AddCallback(StateType::Game,"Key_Reset",&State_Game::ResetTick,this);
    evmgr->AddCallback(StateType::Game,"Key_Pause",&State_Game::Pause,this);

    SpawnPiece();

}

void State_Game::OnDestroy()
{
    EventManager* evmgr = m_stateManager->GetContext()->m_eventManager;
    evmgr->RemoveCallback(StateType::Game,"Key_Escape");
    evmgr->RemoveCallback(StateType::Game,"Key_Pause");
    evmgr->RemoveCallback(StateType::Game,"Key_Left");
    evmgr->RemoveCallback(StateType::Game,"Key_Right");
    evmgr->RemoveCallback(StateType::Game,"Key_Change");
    evmgr->RemoveCallback(StateType::Game,"Key_Increase");
    evmgr->RemoveCallback(StateType::Game,"Key_Reset");
}

// void State_Game::Activate(){m_music.play();}
//void State_Game::Deactivate(){m_music.stop();}

void State_Game::Update(const sf::Time& l_time)
{
    sf::Vector2u l_windowSize = m_stateManager->GetContext()->m_wind->GetWindowSize();
    
    if(!GameOver())
    {
        if(m_time.asSeconds() >= m_tickrate)
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
            sf::RectangleShape temp;
            sf::Vector2f size(m_blockSize,m_blockSize);
            temp.setSize(size);
            temp.setPosition(j*m_blockSize,i*m_blockSize);
            if(m_grid[i][j] == 0)
            {temp.setTexture(&m_backgroundTexture);}
            else 
            {temp.setTexture(&m_tileTexture); }
            l_renderwind->draw(temp);
        }
    }
    m_scoreBoard->Render(l_renderwind);
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

void State_Game::IncreaseTick(EventDetails* l_details){m_tickrate = 0.1;}
void State_Game::ResetTick(EventDetails* l_details){m_tickrate = 0.5;}


void State_Game::Tick()
{
    std::cout << "Moving\n";
    if(!m_piece->CheckCollision())
    {
        MoveDown();
        if(m_piece->CheckCollision())m_collid.play();
    }
    else 
    {
        for(int i = 2; i < m_grid.size(); ++i)
        {
            if(RowComplete(i))
            {
                RemoveRow(i);
                m_scoreBoard->IncreaseScore();
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
