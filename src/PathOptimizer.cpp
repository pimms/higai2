#include <algorithm>
using std::max;
using std::min;

#include "PathOptimizer.h"
#include "PathNode.h"
#include "World.h"


PathOptimizer::PathOptimizer(World *world) 
	:	_world(world)
{

}


bool PathOptimizer::OptimizePath(list<PathNode*> &path) {
	/* Start is the start of the current mid. Mid is the node
	 * that may be optimized out. End is the end of the mid. */
	list<PathNode*>::iterator start, mid, end;

	return false;	
}


/***** Private Methods *****/
void PathOptimizer::GetIterators(const list<PathNode*>::iterator &context,
								list<PathNode*>::iterator &mid,
								list<PathNode*>::iterator &end)
{
	mid = context;
	mid++;

	end = mid;
	end++;
}


bool PathOptimizer::ClearLineOfSight(PathNode *start, PathNode *end) {
	int rx1, rx2, ry1, ry2;
	GetIntersectionTestArea(start, end, &rx1, &ry1, &rx2, &ry2);
	

}

void PathOptimizer::GetIntersectionTestArea(PathNode *start, PathNode *end,
											int *x1, int *y1, int *x2, int *y2)
{
	int sx, sy, ex, ey;
	start->GetPosition(&sx, &sy);
	end->GetPosition(&ex, &ey);

	*x1 = min(sx, ex);
	*y1 = min(sy, ey);
	*x2 = max(sx, ex);
	*y2 = max(sy, ey);
}

void PathOptimizer::GetPathLine(PathNode *start, PathNode *end,
								int *x1, int *y1, int *x2, int *y2) 
{
	start->GetPosition(x1, y1);
	end->GetPosition(x2, y2);
}
