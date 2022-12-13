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
}

void MainMenu::Render()
{
    if (IsGameRunning())
    {
        SDL_RenderClear(gameRender);
        SDL_RenderPresent(gameRender);
        SDL_Delay(1000 / 60);
    }
}

bool MainMenu::IsGameRunning()
{
	return false;
}

void MainMenu::Initialise()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    gameWindow = SDL_CreateWindow("Main Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    gameRender = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
    m_visualisation = Visualisation::Initialise(gameRender);
    SDL_SetRenderDrawColor(gameRender, rgb[0], rgb[1], rgb[2], 255);
}

void MainMenu::Uninitialise()
{
    SDL_Quit();
    SDL_DestroyRenderer(gameRender);
    SDL_DestroyWindow(gameWindow);
    inputManager->~InputManager();
    m_visualisation->~Visualisation();
}
MainMenu* MainMenu::s_instance = nullptr;