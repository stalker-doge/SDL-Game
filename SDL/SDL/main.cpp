#include <SDL.h>
#include <iostream>
#include "MainMenu.h"
#include "Game.h"
#include <time.h>
using namespace std;

int main(int argc, char* argv[])
{
	srand(time(NULL));
	Game* game=Game::Instance();
	
	MainMenu* Mmenu = MainMenu::Instance();

	bool RunGame = false;

	while (Mmenu->IsGameRunning()) 
	{
		RunGame = true;
	}

	if (RunGame == true) 
	{
		while (game->IsGameRunning())
		{
			game->Render();
			game->Update();
		}
	}

	return 0;
}