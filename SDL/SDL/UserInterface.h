#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Visualisation.h"
#include <string>
class UserInterface
{
public:
	UserInterface();
	~UserInterface();
	void Initialise();
	void Update();
	void Render();
	void SetScore(int score);
	void SetHealth(int health);
private:
	//Text
//Fonts
	TTF_Font* Sans;
	SDL_Color White;
	//test
	SDL_Surface* surfaceMessage;
	SDL_Rect Message_rect;
	SDL_Texture* Message;
	//health
	SDL_Surface* surfaceHealthMessage;
	SDL_Texture* HealthMessage;
	SDL_Rect HealthMessage_rect;
	int score=0;
	int health=0;
};

