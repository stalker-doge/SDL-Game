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



void MainMenu::Render()
{
    if (IsGameRunning())
    {
        SDL_RenderClear(gameRender);

        m_startbutton->Render();
        m_button->Render();
        m_mousepos->Render();
        m_stars->Render(gameRender);

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

    m_startbutton = new Entity();
    m_button = new Entity();
    m_mousepos = new Entity();
    m_stars = new StarScape();

    rgb[0] = 0;
    rgb[1] = 0;
    rgb[2] = 0;
    SDL_Init(SDL_INIT_EVERYTHING);
    gameWindow = SDL_CreateWindow("Main Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    gameRender = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
    m_visualisation = Visualisation::Initialise(gameRender);
    SDL_SetRenderDrawColor(gameRender, rgb[0], rgb[1], rgb[2], 255);

    m_button->Initialise("quit", "quit.bmp");
    m_button->ChangeLocation(450, 320, 128 , 384);

    m_startbutton->Initialise("play", "play.bmp");
    m_startbutton->ChangeLocation(450, 120, 128, 384);

    m_mousepos->Initialise("player", "eh.1.bmp");

    m_entities.push_back(m_button);
    m_entities.push_back(m_startbutton);
    m_entities.push_back(m_mousepos);

    m_stars->Initialise(gameRender);
}

void MainMenu::StopGame()
{
    RunGame = false;
    RunGameCheck = false;
    //Uninitialise();
}

void MainMenu::Update()
{
    inputManager->Update();
    m_stars->Update();
    int x, y;
    SDL_GetMouseState(&x, &y);
    //m = new SDL_Rect(SDL_GetMouseState(&x), SDL_GetMouseState(&y), 1, 1);

    mouseY = y;
    mouseX = x;

    m_mousepos->ChangeLocation(mouseX, mouseY, 1, 1);
    //m_mousepos = new SDL_Rect{ x, y, 1, 1 };

    if (TestCollision(m_mousepos, m_startbutton))
    {
        if (inputManager->GetMouseDown(1))
        {
            RunGame = false;
        }
    }

    if (inputManager->GetMouseDown(1))
    {
        if (TestCollision(m_mousepos, m_button))
        {
            StopGame();
        }
    }
    /*
    if (inputManager->GetKeyDown(SDLK_ESCAPE))
    {
        StopGame();
    }
    */
}

void MainMenu::Uninitialise()
{

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