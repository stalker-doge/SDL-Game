#include "Block.h"

Block::Block()
{
}

Block::~Block()
{
}

void Block::Initialise(Visualisation* vis, const char* name, const char* imageName)
{
	Entity::m_imageName = imageName;
	Entity::m_name = name;
	Entity::Initialise(vis,name,imageName);
}
