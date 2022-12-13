#include <SDL.h>
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		return 1;
	}
	SDL_Window *gameWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
	SDL_Renderer *gameRender= SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(gameRender, 2, 209, 199, 255);
	SDL_RenderClear(gameRender);
	SDL_RenderPresent(gameRender);
	SDL_Delay(2000);
	SDL_Event* loopStopper = new SDL_Event();
	int rgb[3];
	rgb[0] = 2;
	rgb[1] = 209;
	rgb[2] = 199;
	while(1)
	{
		for (int i = 0; i < 3; i++)
		{
			if (rgb[i] > 255)
			{
				rgb[i] = 0;
			}
			else
			{
				rgb[i]++;
			}
		}
		SDL_SetRenderDrawColor(gameRender,rgb[0], rgb[1],rgb[2], 255);
		SDL_RenderClear(gameRender);
		SDL_RenderPresent(gameRender);
		SDL_Delay(20);
		SDL_PollEvent(loopStopper);
		if (loopStopper->key.keysym.scancode == SDL_SCANCODE_ESCAPE) 
		{
			break;
		}
	}
	SDL_DestroyRenderer(gameRender);
	SDL_DestroyWindow(gameWindow);
	SDL_Quit();
	return 0;
}