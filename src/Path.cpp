#include "Path.h"
#include "World.h"
#include "PathAnalyzer.h"
#include "PathNode.h"


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

float Path::GetLength(const list<PathNode*> &path) const
{
	list<PathNode*>::const_iterator it, next;
	int length = 0;

	it = path.begin();
	next = std::next(it);

	while (next != path.end()) {
		Vec pa, pb;
		pa = (*it)->GetPosition();
		pb = (*next)->GetPosition();

		float dx = abs(pb.x - pa.x);
		float dy = abs(pb.y - pa.y);
		length += sqrt(dx*dx + dy*dy);

		it++;
		next = std::next(it);
	}

	return length;
}

float Path::GetLength() const
{
	return GetLength(_nodes);
}

float Path::GetOptimizedLength() const
{
	return GetLength(_optimized);
}
