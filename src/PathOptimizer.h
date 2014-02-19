#pragma once

#include <list>
using std::list;

#include "Vec.h"

// Forward declarations
class PathNode;
class World;


class PathOptimizer {
public:
	PathOptimizer(World *world);

	bool OptimizePath(list<PathNode*> &path);

private:
	World *_world;

	/* Assigns path to "context+1" and end to "context+2" */
	void GetIterators(const list<PathNode*>::iterator &context,
						list<PathNode*>::iterator &mid,
						list<PathNode*>::iterator &end);

	bool ClearLineOfSight(PathNode *start, PathNode *b);
	void GetIntersectionTestArea(PathNode *start, PathNode *end, Vec &tl, Vec &br);
	void GetPathLine(PathNode *start, PathNode *end, Vec &p1, Vec &p2);
};
