#include <SDL.h>
#include <iostream>
#include "Game.h"
#include <time.h>
using namespace std;
int main(int argc, char* argv[])
{
	srand(time(NULL));
	Game* game=Game::Instance();

	while (game->IsGameRunning())
	{
		game->Render();
		game->Update();
	}
	return 0;
}