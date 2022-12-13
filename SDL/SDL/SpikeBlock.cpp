#include "SpikeBlock.h"

SpikeBlock::SpikeBlock()
{
}

SpikeBlock::~SpikeBlock()
{

}

void SpikeBlock::Initialise(Visualisation* vis, const char* name, const char* imageName)
{
	Entity::m_imageName = imageName;
	Entity::m_name = name;
	Entity::Initialise(vis, name, imageName);
}
