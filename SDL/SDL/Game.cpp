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
        std::cout << "Beep\n";
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
        if (inputManager->GetKeyHeld(SDLK_SPACE))//shooting function
        {
            m_bulletPool->Shoot(m_player->GetLocation());
        }
        if (inputManager->GetKeyDown(SDLK_q))
        {
            m_bulletPool->Wipe();
        }
        Uint64 startTimer = SDL_GetPerformanceCounter();
        m_player->Update();
        m_enemy->Update();
        m_bulletPool->Update();
		m_enemySpawner->Update();
        if ((SDL_GetTicks64() - shootTimer) / 1000 > 3)
        {
            //makes all enemies shoot a bullet
            for (int i = 0; i < m_enemySpawner->GetEnemyVector().size(); i++)
            {
                if (m_enemySpawner->GetEnemyVector()[i]->GetStatus())
                {
                    m_bulletPool->EnemyShoot(m_enemySpawner->GetEnemyVector()[i]->GetLocation());
                }
            }
            shootTimer = SDL_GetTicks64();
        }
        if (m_boss->bossDeath1)
        {
            m_enemySpawner->Upgrade(true);
        }
        m_boss->Update();
        m_starScape->Update();
        m_userInterface->SetHealth(m_player->GetHP());
        m_userInterface->SetScore(score);
        m_userInterface->Update();
        CheckCollisions();
        Render();
        if (!m_boss->GetStatus())
        {
            if ((SDL_GetTicks64() - timer)/1000 > 10)
            {
                m_boss->SetStatus(true);
                timer = SDL_GetTicks64();
            }
        }
        Uint64 endTimer = SDL_GetPerformanceCounter();
        float elapsedMS = (endTimer - startTimer) / (float)SDL_GetPerformanceFrequency() * 1000;//capping the game at 60fps
        elapsedMS = SDL_max(elapsedMS, 0.01);
        SDL_Delay(floor(16.666f - elapsedMS));
        std::cout << "Boop\n";
    }
}

void Game::Render()
{
        SDL_RenderClear(gameRender);
        m_starScape->Render(gameRender);
		for (int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->Render();
		}
        m_bulletPool->Render();
        m_enemySpawner->Render();
        m_boss->Render();
        m_userInterface->Render();
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
    m_enemySpawner = new EnemySpawner();
    m_boss = new Boss();
    timer = SDL_GetTicks64();
    shootTimer = SDL_GetTicks64();
    m_player = new Player();
	m_enemy = new Enemy();
    m_bullet = new Bullet();
    m_bulletPool = new ObjectPool();
    m_starScape = new StarScape();
    m_userInterface = new UserInterface();
    rgb[0] = 0;
    rgb[1] = 0;
    rgb[2] = 0;
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    gameWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    gameRender = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
    m_visualisation = Visualisation::Initialise(gameRender);
    SDL_SetRenderDrawColor(gameRender, rgb[0], rgb[1], rgb[2], 255);
    m_player->Initialise();
	m_enemy->Initialise();
    m_bullet->Initialise();
    m_entities.push_back(m_player);
	m_entities.push_back(m_enemy);
    m_entities.push_back(m_bullet);
    m_bulletPool->Initialise(100);
    m_enemySpawner->Initialise();
    m_starScape->Initialise(gameRender);
    m_boss->Initialise();
    m_entities.push_back(m_boss);
    m_userInterface->Initialise();
    score = 0;
}

void Game::Uninitialise()
{
    delete m_player;
    delete m_enemy;
    delete inputManager;
    delete m_visualisation;
    delete m_bulletPool;
    delete m_enemySpawner;
    delete m_starScape;
    delete m_boss;
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
                if (m_entities[i]->GetStatus())
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
		}
		std::vector<Bullet*> temp = m_bulletPool->GetUsedVector();
        for (int i = 0; i < m_entities.size(); i++)
        {
            if (m_entities[i]->GetStatus())
            {
                if (m_entities[i]->GetName() != "player")
                {
                    for (int j = 0; j < temp.size(); j++)
                    {
                        if (TestCollision(m_entities[i], temp[j]))
                        {
                            m_entities[i]->OnCollision(temp[j]);
                            temp[j]->OnCollision(m_entities[i]);
                        }
                    }
                }
            }
        }

		
        std::vector<Enemy*> temp2 = m_enemySpawner->GetEnemyVector();
        for (int i = 0; i < m_entities.size(); i++)
        {
            if (m_entities[i]->GetStatus())
            {
                    for (int j = 0; j < temp2.size(); j++)
                    {
                        if (temp2[j]->GetStatus())
                        {
                            if (TestCollision(m_entities[i], temp2[j]))
                            {
                                score +=m_entities[i]->OnCollision(temp2[j]);
                                temp2[j]->OnCollision(m_entities[i]);
                            }
                        }
                    }
            }
        }
        for (int i = 0; i < temp.size(); i++)
        {
			if (temp[i]->GetStatus())
			{
				for (int j = 0; j < temp2.size(); j++)
				{
					if (temp2[j]->GetStatus())
					{
						if (TestCollision(temp[i], temp2[j]))
						{
                            temp[i]->OnCollision(temp2[j]);
							score+=temp2[j]->OnCollision(temp[i]);
						}
					}
				}
			}
        }
		
        temp.clear();
        temp2.clear();
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

SDL_Renderer* Game::GetRenderer()
{
    return gameRender;
}

Game* Game::s_instance = nullptr;
