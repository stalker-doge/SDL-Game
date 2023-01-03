#include "MainMenu.h"

MainMenu::MainMenu() 
{
    Initialise();
}

MainMenu* MainMenu::Instance()
{
    if (s_instance == nullptr)
    {
        s_instance = new MainMenu();
        return s_instance;
    }
    return s_instance;
}

MainMenu::~MainMenu()
{
}

void MainMenu::Update()
{
    inputManager->Update();

    int x, y;
    SDL_GetMouseState(&x, &y);
    //m = new SDL_Rect(SDL_GetMouseState(&x), SDL_GetMouseState(&y), 1, 1);

    mouseY = y;
    mouseX = x;

    //m_mousepos = new SDL_Rect{ x, y, 1, 1 };

    if (inputManager->GetKeyDown(SDLK_ESCAPE))
    {
        Uninitialise();
    }

    if (inputManager->GetKeyDown(SDLK_e)) 
    {
        RunGame = false;
    }
}

void MainMenu::Render()
{
    if (IsGameRunning())
    {
        SDL_RenderClear(gameRender);

        m_button->Render();
        m_mousepos->Render();

        SDL_RenderPresent(gameRender);
        SDL_Delay(1000 / 60);
    }
}

bool MainMenu::IsGameRunning()
{
    return RunGame;
}

void MainMenu::Initialise()
{
    inputManager = InputManager::Instance();

    m_button = new Entity();
    m_mousepos = new Entity();

    rgb[0] = 76;
    rgb[1] = 183;
    rgb[2] = 245;
    SDL_Init(SDL_INIT_EVERYTHING);
    gameWindow = SDL_CreateWindow("Main Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    gameRender = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
    m_visualisation = Visualisation::Initialise(gameRender);
    SDL_SetRenderDrawColor(gameRender, rgb[0], rgb[1], rgb[2], 255);

    m_button->Initialise("block", "block.bmp");
    m_mousepos->Initialise("player", "block.bmp");
    m_entities.push_back(m_button);
    m_entities.push_back(m_mousepos);
}

void MainMenu::Uninitialise()
{
    RunGame = false;
    delete inputManager;
    delete m_visualisation;
    SDL_DestroyRenderer(gameRender);
    SDL_DestroyWindow(gameWindow);
    SDL_Quit();
}

Entity* MainMenu::CheckCollisions()
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
bool MainMenu::TestCollision(Entity* player, Entity* button)
{
    if (!button->GetStatus())
    {
        return false;
    }
    int playerMinX, playerMinY, playerMaxX, playerMaxY, blockMinX, blockMinY, blockMaxX, blockMaxY;
    SDL_Rect* playerRect;
    SDL_Rect* blockRect;
    playerRect = player->GetLocation();
    blockRect = button->GetLocation();
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
    }
    else if (playerMinX > blockMaxX)
    {
        return false;
    }
    else if (playerMaxX < blockMinX)
    {
        return false;
    }
    return true;
}

MainMenu* MainMenu::s_instance = nullptr;