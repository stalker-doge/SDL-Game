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
    if (IsGameRunning())
    {
       
        inputManager->Update();

        if (inputManager->GetKeyDown(SDLK_ESCAPE))
        {
            StopGame();
            return;
        }
        else if (inputManager->GetKeyDown(SDLK_KP_ENTER))
        {
            RestartGame();
            return;
        }
        if (inputManager->GetKeyDown(SDLK_SPACE))
        {
            m_bulletPool->GetObject()->Shoot(m_player->GetLocation());
        }

        Uint64 startTimer = SDL_GetPerformanceCounter();
        m_player->Update();
        m_enemy->Update();
        m_bulletPool->Update();
        CheckCollisions();
        Render();
        Uint64 endTimer = SDL_GetPerformanceCounter();
        float elapsedMS = (endTimer - startTimer) / (float)SDL_GetPerformanceFrequency() * 1000;//capping the game at 60fps
        elapsedMS = SDL_max(elapsedMS, 0.01);
        SDL_Delay(floor(16.666f - elapsedMS));
    }
}

void Game::Render()
{
        SDL_RenderClear(gameRender);
		for (int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->Render();
		}
        SDL_RenderPresent(gameRender);
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
	m_enemy = new Enemy();
    m_bullet = new Bullet();
    m_bulletPool = new ObjectPool();
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
	m_enemy->Initialise();
    m_bullet->Initialise();
    m_entities.push_back(m_player);
	m_entities.push_back(m_block[0]);
	m_entities.push_back(m_block[1]);
	m_entities.push_back(m_block[2]);
	for (int i = 0; i < 5; i++)
	{
		m_entities.push_back(m_spikeBlocks[i]);
	}
    m_entities.push_back(m_star);
	m_entities.push_back(m_enemy);
    m_entities.push_back(m_bullet);
    m_bulletPool->Initialise(m_bullet);
}

void Game::Uninitialise()
{
    delete m_player;
    delete m_enemy;
	for (int i=0;i<3;i++)
	{
		delete m_block[i];
	}
    for (int i = 0; i < 5; i++)
	{
		delete m_spikeBlocks[i];
	}
    delete inputManager;
    delete m_visualisation;
    m_entities.clear();
    SDL_DestroyRenderer(gameRender);
    SDL_DestroyWindow(gameWindow);
    SDL_Quit();
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
