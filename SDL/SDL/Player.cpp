#include "Player.h"
#include "Game.h"
Player::Player()
{
}
Player::~Player()
{
}

const char* Player::GetName()
{
    return "player";
}

void Player::Initialise()
{
    m_Vis = Visualisation::Instance();
    m_name="player";
    playerSpeed = 5;
    imageID = m_Vis->AddImage("testimage.bmp");
    Entity::isEnabled = true;
    Entity::isDynamic = true;
    m_Rect = new SDL_Rect{ 100,100,64,64 };
    HP = 100;
}


void Player::Update()
{
    playerInput = InputManager::Instance();
    Game* game = Game::Instance();
    playerX = m_Rect->x;
    playerY = m_Rect->y;
    if (playerInput->GetKeyHeld(SDLK_w))
    {
		m_Rect->y -= playerSpeed;
    }
    if (playerInput->GetKeyHeld(SDLK_s))
    {
		m_Rect->y += playerSpeed;
    }
    if (playerInput->GetKeyHeld(SDLK_a))
    {
		m_Rect->x -= playerSpeed;
    }
    if (playerInput->GetKeyHeld(SDLK_d))
    {
		m_Rect->x += playerSpeed;
    }

    if (m_Rect->y+m_Rect->h > 720||m_Rect->y<0)
    {
        m_Rect->y = playerY;
    }
    if (m_Rect->x+m_Rect->w > 1280 || m_Rect->x < 0)
    {
        m_Rect->x = playerX;
    }
	
}

int Player::OnCollision(Entity*collider)
{
    if (collider != nullptr)
    {

        if (collider->GetName() == "EnemyBullet")
        {
            HP--;
        }
		else if (collider->GetName() == "enemy")
		{
			HP--;
		}
    }
    return 0;
}

void Player::RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, SDL_Renderer* render)
{
    SDL_Rect background;
    background.x = x;
    background.y = y;
    background.w = w;
    background.h = h;
    SDL_SetRenderDrawColor(render, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
    SDL_RenderFillRect(render, &background);

    SDL_Rect foreground;
    foreground.x = x;
    foreground.y = y;
    foreground.w = (int)(w * Percent);
    foreground.h = h;
    SDL_SetRenderDrawColor(render, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
    SDL_RenderFillRect(render, &foreground);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
}

void Player::Render()
{
    m_Vis = Visualisation::Instance();
	m_Vis->DrawImage(imageID, m_Rect);
    SDL_Color FGColor = { 0, 255, 0, 255 };
    SDL_Color BGColor = { 255, 0, 0, 255 };
	RenderHPBar(0, 0, 100, 20, 1, FGColor, BGColor, m_Vis->GetRender());
}

int Player::GetHP()
{
    return HP;
}
