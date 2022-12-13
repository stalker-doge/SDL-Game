#include "Visualisation.h"

Visualisation::Visualisation()
{
}

Visualisation::~Visualisation()
{
    textureStorage.clear();
    s_instance = nullptr;
}

Visualisation* Visualisation::Instance()
{
    return s_instance;
}

Visualisation* Visualisation::Initialise(SDL_Renderer* gameRender)
{
    if (s_instance == nullptr)
    {
        s_instance = new Visualisation();
        s_instance->SetRender(gameRender);
        return s_instance;
    }
    return s_instance;
}

void Visualisation::SetRender(SDL_Renderer* gameRender)
{
    renderer = gameRender;
}

int Visualisation::AddImage(const char* character)
{
    SDL_Surface* tempSurface = SDL_LoadBMP(character);
    if (tempSurface)
    {
        SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 255, 0, 255));
        textureStorage.push_back(SDL_CreateTextureFromSurface(renderer, tempSurface));
        SDL_FreeSurface(tempSurface);
        return textureStorage.size() - 1;
    }
    return -1;
}

void Visualisation::RemoveImage(int userInt)
{
    textureStorage.erase(textureStorage.begin()+userInt);
}
void Visualisation::DrawImage(int userInt, SDL_Rect* rect)
{
    SDL_RenderCopy(renderer, textureStorage[userInt], NULL, rect);
}

Visualisation* Visualisation::s_instance = nullptr;
