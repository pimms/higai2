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

}

void PathOptimizer::GetIntersectionTestArea(PathNode *start, PathNode *end,
											Vec &tl, Vec &br)
{
	int sx, sy, ex, ey;
	start->GetPosition(&sx, &sy);
	end->GetPosition(&ex, &ey);

	tl.x = min(sx, ex);
	tl.y = min(sy, ey);
	br.x = max(sx, ex);
	br.y = max(sy, ey);
}

void PathOptimizer::GetPathLine(PathNode *start, PathNode *end,
								Vec &p1, Vec &p2) 
{
	p1 = start->GetPosition();
	p2 = end->GetPosition();
}
