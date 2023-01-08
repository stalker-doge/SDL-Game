#include <SDL.h>
#include <iostream>
#include "Game.h"
#include <time.h>
#include "MainMenu.h"
using namespace std;
int main(int argc, char* argv[])
{
	srand(time(NULL));
	MainMenu* Mmenu = MainMenu::Instance();

	bool loadGame = false;

	
	while (!Mmenu->ExitGame)
	{
		while (Mmenu->IsGameRunning())
		{

			Mmenu->Render();
			Mmenu->Update();
		}

		Mmenu->Uninitialise();

		if (Mmenu->RunGameCheck == true)
		{
			Game* game = Game::Instance();

			while (game->IsGameRunning())
			{
				game->Render();
				game->Update();
			}
		}
	}

	return 0;
}