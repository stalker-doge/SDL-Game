#include "Game.h"

Game::Game()
{
    Initialise();
}

Game* Game::Instance()
{
    if (s_instance == nullptr)
    {
        s_instance = new Game();
        return s_instance;
    }
    return s_instance;
}

Game::~Game()
{
}

void Game::Update()
{
    inputManager->Update();

    if (inputManager->GetKeyDown(SDLK_ESCAPE))
    {
        StopGame();
    }
    else if (inputManager->GetKeyDown(SDLK_KP_ENTER))
    {
        RestartGame();
    }
    m_player->Update();
    CheckCollisions();
}

void Game::Render()
{
    if (IsGameRunning())
    {
        SDL_RenderClear(gameRender);
        m_block[0]->Render();
        m_block[1]->Render();
        m_block[2]->Render();
        for (int i = 0; i < 5; i++)
        {
           m_spikeBlocks[i]->Render();
        }
        m_player->Render();
        m_star->Render();
        SDL_RenderPresent(gameRender);
        SDL_Delay(1000 / 60);
    }
}

bool Game::IsGameRunning()
{
    return running;
}

void Game::Initialise()
{
    inputManager = InputManager::Instance();
    running = true;
    m_block[0] = new Entity();
    m_block[1] = new Entity();
    m_block[2] = new Entity();
    for (int i = 0; i < 5; i++)
    {
        m_spikeBlocks[i] = new Entity();
    }
    m_player = new Player();
    m_star = new Entity();
    rgb[0] = 76;
    rgb[1] = 183;
    rgb[2] = 245;
    SDL_Init(SDL_INIT_EVERYTHING);
    gameWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    gameRender = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
    m_visualisation = Visualisation::Initialise(gameRender);
    SDL_SetRenderDrawColor(gameRender, rgb[0], rgb[1], rgb[2], 255);
    m_player->Initialise();
    m_block[0]->Initialise("block","block.bmp");
    m_block[1]->Initialise("block", "block.bmp");
    m_block[2]->Initialise("block", "block.bmp");
    for (int i = 0; i < 5; i++)
    {
        m_spikeBlocks[i]->Initialise("spike", "spike.bmp");
    }
    m_star->Initialise("star", "star.bmp");
    m_entities.push_back(m_player);
	m_entities.push_back(m_block[0]);
	m_entities.push_back(m_block[1]);
	m_entities.push_back(m_block[2]);
	for (int i = 0; i < 5; i++)
	{
		m_entities.push_back(m_spikeBlocks[i]);
	}
    m_entities.push_back(m_star);
	
}

void Game::Uninitialise()
{
    SDL_Quit();
    SDL_DestroyRenderer(gameRender);
    SDL_DestroyWindow(gameWindow);
    inputManager->~InputManager();
    m_visualisation->~Visualisation();
}
void Game::StopGame()
{
    running = false;
    Uninitialise();
}
void Game::RestartGame()
{
    Uninitialise();
    Initialise();
}
Entity* Game::CheckCollisions()
{
    while (IsGameRunning())
    {
		for (int i = 0; i < m_entities.size(); i++)
		{
            if (m_entities[i]->GetDyanmic())
            {

                for (int j = 0; j < m_entities.size(); j++)
                {
                    if (i != j)
                    {
                        if (TestCollision(m_entities[i], m_entities[j]))
                        {
                            m_entities[i]->OnCollision(m_entities[j]);
                            m_entities[j]->OnCollision(m_entities[i]);
							return m_entities[j];
                        }
                    }
                }
            }
		}
        return nullptr;
	}
}
bool Game::TestCollision(Entity* player,Entity* block)
{
    if (!block->GetStatus())
    {
        return false;
    }
    int playerMinX, playerMinY, playerMaxX,playerMaxY, blockMinX, blockMinY, blockMaxX, blockMaxY;
    SDL_Rect* playerRect;
    SDL_Rect* blockRect;
    playerRect = player->GetLocation();
    blockRect = block->GetLocation();
    playerMinX = playerRect->x;
    playerMinY = playerRect->y;
    playerMaxX = playerRect->x + playerRect->w;
    playerMaxY = playerRect->y + playerRect->h;
    blockMinX = blockRect->x;
    blockMinY = blockRect->y;
    blockMaxX = blockRect->x + blockRect->w;
    blockMaxY = blockRect->y + blockRect->h;
    if (playerMinY > blockMaxY)
    {
        return false;
    }
    else if (playerMaxY < blockMinY)
    {
        return false;
    }else if (playerMinX > blockMaxX)
    {
        return false;
    }
    else if (playerMaxX < blockMinX)
    {
        return false;
    }
    return true;
}
Game* Game::s_instance = nullptr;
