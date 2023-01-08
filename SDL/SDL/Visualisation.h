#pragma once
#include <SDL.h>
#include <vector>
class Visualisation
{
public:

	~Visualisation();
	static Visualisation* Instance();
	static Visualisation* Initialise(SDL_Renderer* gameRender);
	void SetRender(SDL_Renderer* gameRender);
	int AddImage(const char* character);
	void RemoveImage(int userInt);
	void DrawImage(int userInt, SDL_Rect* rect);
	SDL_Renderer* GetRender();
private:
	static Visualisation* s_instance;
	Visualisation();
	Visualisation(const Visualisation&) = delete;
	SDL_Renderer* renderer;
	std::vector<SDL_Texture*> textureStorage;
};

