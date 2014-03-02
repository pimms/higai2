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


Path* PathCreator::FindPath() 
{
	if (_curA && _curB) {
		return FindPath(_curA, _curB);
	}

	return NULL;
}

Path* PathCreator::FindPath(PathNode *a, PathNode *b) 
{
	if (_path) {
		delete _path;
	}

	AStar astar(_world);
	_path = astar.Find(a, b);
	_curA = a;
	_curB = b;

	return _path;
}


Path* PathCreator::GetPath() const
{
	return _path;
}

bool PathCreator::TestPath(const Path *oldPath) {
	AStar astar(_world);
	Path *path = GetPath();
	Path *newPath = FindPath();
	if (_path == newPath) 
	{
		printf("No wall added in path. No need for new path.\n\n");
		return false;
	} else {
		printf("Wall added in path. Finding new path.\n\n");
		return true;
	}
}