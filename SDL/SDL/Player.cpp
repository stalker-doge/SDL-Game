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
    playerSpeed = 3;
    imageID = m_Vis->AddImage("testimage.bmp");
    Entity::isEnabled = true;
    Entity::isDynamic = true;
    m_Rect = new SDL_Rect{ 100,100,64,64 };
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

    if (m_Rect->y > 720||m_Rect->y<0)
    {
        m_Rect->y = playerY;
    }
    if (m_Rect->x > 1280 || m_Rect->x < 0)
    {
        m_Rect->x = playerX;
    }
}

void Player::OnCollision(Entity*collider)
{
    if (collider != nullptr)
    {

        if (collider->GetName() == "block")
        {
            m_Rect->x = playerX;
            m_Rect->y = playerY;
        }
        else if (collider->GetName() == "spike")
        {
            int tempX, tempY;
            tempX = playerX - m_Rect->x;
            tempY = playerY - m_Rect->y;
            m_Rect->x = playerX - (playerSpeed * -tempX);
            m_Rect->y = playerY - (playerSpeed * -tempY);
        }
        else if (collider->GetName() == "star")
        {
            collider->SetStatus(false);
            playerSpeed = playerSpeed * 2;
        }
    }
}
