#include "StarScape.h"

StarScape::~StarScape()
{
	
}

void StarScape::Render(SDL_Renderer* render)
{
	SDL_RenderCopy(render, m_starScape, NULL, NULL);
}

void StarScape::Update()
{
	//makes the starscape move horizontally
	for (int i = 0; i < 1280 * 720; i++)
	{
		m_pixels[i] = m_pixels[i + 1];
	}
	SDL_UpdateTexture(m_starScape, NULL, m_pixels, 1280 * sizeof(Uint32));
}

void StarScape::Initialise(SDL_Renderer* render)
{
	m_pixels = new Uint32[1280 * 720];
	m_starScape = SDL_CreateTexture(render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 1280, 720);
	for (int i = 0; i < 1280 * 720; i++)
	{
		m_pixels[i] = 0x00000000;
	}
	for (int i = 0; i < 1000; i++)
	{
		int x = rand() % 1280;
		int y = rand() % 720;
		m_pixels[x + y * 1280] = 0xFFFFFFFF;
	}
	m_Rect = new SDL_Rect{ 0,0,1280,720 };
	SDL_SetTextureBlendMode(m_starScape, SDL_BLENDMODE_BLEND);
	SDL_UpdateTexture(m_starScape, NULL, m_pixels, 1280 * sizeof(Uint32));
}

