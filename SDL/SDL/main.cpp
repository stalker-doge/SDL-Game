#include <SDL.h>
#include <iostream>
#include "MainMenu.h"
#include "Game.h"
#include <time.h>
using namespace std;

int main(int argc, char* argv[])
{
	srand(time(NULL));	
	MainMenu* Mmenu = MainMenu::Instance();

	bool loadGame = false;


	while (Mmenu->IsGameRunning()) 
	{
		if (loadGame == true)
		{
			//Mmenu->Uninitialise();
			break;
			//return 0;
		}

		Mmenu->Render();
		Mmenu->Update();

		//loadGame = true;
		//Mmenu->Uninitialise();
	}

	Mmenu->Uninitialise();

	Game* game = Game::Instance();

	while (game->IsGameRunning())
	{
		game->Render();
		game->Update();
	}

	return 0;
}