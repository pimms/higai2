#include "Path.h"
#include "World.h"
#include "PathAnalyzer.h"


Path::Path(World *world) 
	:	_world(world)
{

}


void Path::SetNodes(list<PathNode*> nodes) 
{
	_nodes = nodes;

	PathAnalyzer path(_world);
	_optimized = _nodes;
	path.OptimizePath(_optimized);
}

const list<PathNode*>& Path::GetNodes() const 
{
	return _nodes;
}

const list<PathNode*>& Path::GetOptimized() const 
{
	return _optimized;
}
