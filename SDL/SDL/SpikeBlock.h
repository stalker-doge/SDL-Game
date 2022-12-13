#pragma once
#include "Entity.h"
class SpikeBlock : public Entity
{
public:
	SpikeBlock();
	~SpikeBlock();
	void Initialise(Visualisation* vis, const char* name, const char* imageName);
private:
};

