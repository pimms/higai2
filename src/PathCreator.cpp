#include "PathCreator.h"
#include "World.h"
#include "PathNode.h"
#include "Path.h"
#include "AStar.h"


PathCreator::PathCreator(World *world)
	: 	_world(world),
		_path(NULL),
		_curA(NULL),
		_curB(NULL)
{

}

PathCreator::~PathCreator()
{
	if (_path) {
		delete _path;
	}
}


Path* PathCreator::FindPath(AStar::SearchType st) 
{
	if (_curA && _curB) {
		return FindPath(_curA, _curB, st);
	}

	return NULL;
}

Path* PathCreator::FindPath(PathNode *a, 
							PathNode *b, AStar::SearchType st) 
{
	if (_path) {
		delete _path;
	}

	AStar astar(_world);
	_path = astar.Find(a, b, st);
	_curA = a;
	_curB = b;

	return _path;
}


Path* PathCreator::GetPath() const
{
	return _path;
}
