#include "Game.h"

void Game::Update()
{

}

void Game::Render()
{
    SDL_RenderClear(gameRender);
    SDL_RenderPresent(gameRender);
}

bool Game::IsGameRunning()
{
    return true;
}

void Game::Initialise()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    gameWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    gameRender = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(gameRender, 2, 209, 199, 255);

}

void Game::Uninitialise()
{
    SDL_Quit();
    SDL_DestroyRenderer(gameRender);
    SDL_DestroyWindow(gameWindow);
}
