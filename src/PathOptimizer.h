#pragma once

#include <list>
using std::list;


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
	void GetIntersectionTestArea(PathNode *start, PathNode *end, 
								int *x1, int *y1, int *x2, int *y2);
	void GetPathLine(PathNode *start, PathNode *end, 
					 int *x1, int *y1, int *x2, int *y2);
};
