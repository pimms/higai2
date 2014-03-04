#include "PathCreator.h"
#include "World.h"
#include "PathNode.h"
#include "Path.h"
#include "AStar.h"
#include "Renderer.h"
#include "PathAnalyzer.h"


PathCreator::PathCreator(World *world, Renderer *renderer)
	: 	_world(world),
	    _path(NULL),
	    _curA(NULL),
	    _curB(NULL),
	    _renderer(renderer),
	    _drawProgress(false)
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
	if (_drawProgress) {
		_renderer->DrawWorld(_world);
		astar.SetRenderer(_renderer);
	}

	_path = astar.Find(a, b, st);
	_curA = a;
	_curB = b;

	return _path;
}


Path* PathCreator::FindAgentPath()
{
	if (!_path) {
		return NULL;
	}

	PathAnalyzer pa(_world);
	const list<PathNode*> *path;
	list<PathNode*>::const_iterator ita, itb;
	PathNode *front = NULL;
	PathNode *goal = NULL;

	path = &_path->GetOptimized();
	ita = path->begin();
	itb = std::next(ita);
	front = path->front();
	goal = path->back();

	while (itb != path->end()) {
		if (!pa.IsClearLineOfSight(*ita, *itb)) {
			AStar astar(_world);
			if (_drawProgress) {
				astar.SetRenderer(_renderer);
			}

			Path *path1, *path2;
			path1 = astar.Find(front, *ita);
			path2 = astar.Find(*ita, goal);

			_path = Path::JoinPaths(path1, path2, _world);

			delete path1;
			delete path2;
			break;
		}

		ita++;
		itb++;
	}

	return _path;
}


Path* PathCreator::GetPath() const
{
	return _path;
}

void PathCreator::SetProgressRendering(bool flag)
{
	_drawProgress = flag;
}
