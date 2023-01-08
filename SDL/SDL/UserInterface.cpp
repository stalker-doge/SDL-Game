#include "UserInterface.h"

UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
}

void UserInterface::Initialise()
{
    Visualisation* m_vis = Visualisation::Instance();
    Sans = TTF_OpenFont("39335_UniversCondensed.ttf", 24);
    White = { 255, 255, 255 };
    surfaceMessage = new SDL_Surface();
    HealthMessage_rect = { 0,0,150,100 };
    Message_rect = { 0,600,150,100 };
    surfaceHealthMessage = TTF_RenderUTF8_Solid(Sans, ("Health: " + std::to_string(health)).c_str(), White);
    surfaceMessage = TTF_RenderUTF8_Solid(Sans, ("Score: " + std::to_string(score)).c_str(), White);
}

void UserInterface::Update()
{
    surfaceHealthMessage = TTF_RenderUTF8_Solid(Sans, ("Health" + std::to_string(health)).c_str(), White);
    surfaceMessage = TTF_RenderUTF8_Solid(Sans, ("Score" + std::to_string(score)).c_str(), White);
}

void UserInterface::Render()
{
    Visualisation* m_vis = Visualisation::Instance();
    HealthMessage = SDL_CreateTextureFromSurface(m_vis->GetRender(), surfaceHealthMessage);
	Message = SDL_CreateTextureFromSurface(m_vis->GetRender(), surfaceMessage);
    SDL_RenderCopy(m_vis->GetRender(), Message, NULL, &Message_rect);
	SDL_RenderCopy(m_vis->GetRender(), HealthMessage, NULL, &HealthMessage_rect);
}

void UserInterface::SetScore(int score)
{
	this->score = score;
}

void UserInterface::SetHealth(int health)
{
	this->health = health;
}
