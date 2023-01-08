#pragma once
#include <SDL.h>
#include "InputManager.h"
#include "Visualisation.h"
class Entity
{
public:
	Entity();
	~Entity();
	const char* GetName();
	virtual void Initialise(const char* name, const char* imageName);
	void Render();
	void SetStatus(bool enabling);
	bool GetStatus();
	bool GetDyanmic();
	void Update();
	void SetLifetime(float lf);
	float GetMaxLifetime();
	virtual void GenericAction();
	float GetLifetime();
	virtual int OnCollision(Entity* collider);
	SDL_Rect* GetLocation();
	void SetPosition(int x, int y);
	void ChangeLocation(int x, int y, int h, int w);
	void SetName(const char* name);
protected:
	const char* m_name="";
	const char* m_imageName;
	int imageID;
	Visualisation* m_Vis;
	SDL_Rect* m_Rect;
	bool isEnabled;
	bool isDynamic;
	float lifetime;
	float maxlifetime;
};

