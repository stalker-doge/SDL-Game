#pragma once
#include "Entity.h"

class Block: public Entity
{
public:
	Block();
	~Block();
	void Initialise(Visualisation* vis, const char* name, const char* imageName);
private:
};

