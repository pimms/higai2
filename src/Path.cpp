#include "Path.h"
#include "World.h"
#include "PathAnalyzer.h"
#include "PathNode.h"


#define COPY(_src, _dst) 							\
	{list<PathNode*>::iterator it = _src.begin(); 	\
	while (it != _src.end()) { 						\
		_dst.push_back(*it); it++; 					\
	}}

Path* Path::JoinPaths(Path *path1, Path *path2, World *world)
{
	Path *p = NULL;
	list<PathNode*> nodes;
	list<PathNode*> opt;
	p = new Path(world);

	if (path1) {
		COPY(path1->_nodes, nodes);
		COPY(path1->_optimized, opt);
	}

	if (path2) {
		p->_divisor = path2->_nodes.front();
		COPY(path2->_nodes, nodes);
		COPY(path2->_optimized, opt);
	}

	p->_nodes = nodes;
	p->_optimized = opt;

	return p;
}


Path::Path(World *world)
	:	_world(world),
	    _divisor(NULL)
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


const PathNode* Path::GetSplitDivisor() const
{
	return _divisor;
}
