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
	virtual void GenericAction();
	int GetLifetime();
	virtual void OnCollision(Entity* collider);
	SDL_Rect* GetLocation();
protected:
	const char* m_name="";
	const char* m_imageName;
	int imageID;
	Visualisation* m_Vis;
	SDL_Rect* m_Rect;
	bool isEnabled;
	bool isDynamic;
	int lifetime;
	int maxlifetime;
};

