#pragma once
#include <SDL.h>
#include <stdlib.h>
class StarScape
{
public:
	~StarScape();
	void Render(SDL_Renderer* render);
	void Update();
	void Initialise(SDL_Renderer* render);
private:
	Uint32* m_pixels;
	SDL_Texture* m_starScape;
	SDL_Rect* m_Rect;
};

