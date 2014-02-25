#include "GraphMapper.h"
#include "World.h"


GraphMapper::GraphMapper(World *world)
	: 	_world(world) 
{

}


void GraphMapper::OnMouseClick(Vec pos) 
{
	printf("Mouseclick: {%i %i}\n", pos.x, pos.y);	
}
