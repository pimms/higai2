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
	bool opt = false;

	start = path.begin();
	while (GetIterators(start, mid, end)) {
		int skips = 0;
		while (IsClearLineOfSight(*start, *end)) {
			mid = path.erase(mid);
			skips++;
			end++;
			opt = true;
		}

		start = end;
	}
	
	return opt;	
}


/***** Private Methods *****/
bool PathOptimizer::GetIterators(const list<PathNode*>::iterator &context,
								list<PathNode*>::iterator &mid,
								list<PathNode*>::iterator &end)
{
	if (!*context) {
		return false;
	}

	mid = context;
	mid++;
	if (!*mid) {
		return false;
	}

	end = mid;
	end++;
	if (!*end) {
		return false;
	}

	return true;
}


bool PathOptimizer::IsClearLineOfSight(PathNode *start, PathNode *end) {
	Vec tl, br, lineP1, lineP2;
	GetIntersectionTestArea(start, end, tl, br);
	GetPathLine(start, end, lineP1, lineP2);

	for (int x = tl.x; x < br.x; x++) {
		for (int y = tl.y; y < br.y; y++) {
			PathNode *node = _world->GetNode(x, y);
			if (node->GetType() != PathNode::WALKABLE) {
				Vec rtl, rbr;	
				rtl = node->GetPosition();
				rbr = Vec(rtl.x+1, rtl.y+1);

				if (LineIntersects(lineP1, lineP2, rtl, rbr)) {
					return false;
				}
			}
		}
	}

	return true;
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


bool PathOptimizer::LineIntersects(Vec lp1, Vec lp2, Vec rTL, Vec rBR) {
	float minX = min(lp1.x, lp2.x);
	float maxX = max(lp1.x, lp2.x);

	// Find the intersection of the segment's and rectangle's x-projections

	if(maxX > rBR.x) {
		maxX = rBR.x;
	}

	if(minX < rTL.x) {
		minX = rTL.x;
	}

	if(minX > maxX) {
		// The projections do not intersect
		return false;
	}

	// Find corresponding min and max Y for min and max X we found before
	float minY = min(lp1.y, lp2.y);
	float maxY = max(lp1.y, lp2.y);

	float dx = lp2.x - lp1.x;

	if(abs(dx) > 0.0000001) {
		float a = (lp2.y - lp1.y) / dx;
		float b = lp1.y - a * lp1.x;
		minY = a * minX + b;
		maxY = a * maxX + b;
	}

	if(minY > maxY) {
		float tmp = maxY;
		maxY = minY;
		minY = tmp;
	}

	// Find the intersection of the segment's and rectangle's y-projections
	if(maxY > rTL.y) {
		maxY = rTL.y;
	}

	if(minY < rBR.y) {
		minY = rBR.y;
	}

	if(minY > maxY) {
		return false;
	}

	return true;
}
