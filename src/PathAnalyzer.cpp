#include <algorithm>
using std::max;
using std::min;

#include "PathAnalyzer.h"
#include "PathNode.h"
#include "World.h"

// Some serious construction up in this hizhaz
PathAnalyzer::PathAnalyzer(World *world)
    :	_world(world)
{

}


bool PathAnalyzer::OptimizePath(list<PathNode*> &path)
{
    list<PathNode*>::iterator start, end, tail;
    bool opt = false;
	
	auto createits = [](const list<PathNode*> &l,
						list<PathNode*>::iterator &st,
						list<PathNode*>::iterator &ed) -> bool {
		ed = st;
		if (ed == l.end()) return false;
		ed++; if (ed == l.end()) return false;
		return true;
	};


    start = path.begin();
	tail = path.begin();
	while (createits(path, start, tail)) {
		end = tail;

		while (IsClearLineOfSight(*start, *end) && tail != path.end()) {
			end = tail;
			tail++;
		}

		list<PathNode*>::iterator it = start;
		for (it++; it != end; ) {
			it = path.erase(it);
		}

		start++;
	}

    return opt;
}


bool PathAnalyzer::IsClearLineOfSight(PathNode *start, PathNode *end)
{
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

/***** Private Methods *****/
void PathAnalyzer::GetIntersectionTestArea(PathNode *start, PathNode *end,
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

void PathAnalyzer::GetPathLine(PathNode *start, PathNode *end,
                                Vec &p1, Vec &p2)
{
    p1 = start->GetPosition();
    p2 = end->GetPosition();
}


bool PathAnalyzer::LineIntersects(Vec lp1, Vec lp2, Vec rTL, Vec rBR)
{
	return SegmentIntersectRectangle(
			rTL.x, rTL.y, rBR.x, rBR.y,
			lp1.x, lp1.y, lp2.x, lp2.y
	);
}



/* Line Intersection Algorithm
 * Code taken from:	http://stackoverflow.com/a/100165
 */
bool SegmentIntersectRectangle(double a_rectangleMinX,
                               double a_rectangleMinY,
                               double a_rectangleMaxX,
                               double a_rectangleMaxY,
                               double a_p1x,
                               double a_p1y,
                               double a_p2x,
                               double a_p2y)
{
    // Find min and max X for the segment

    double minX = a_p1x;
    double maxX = a_p2x;

    if(a_p1x > a_p2x)
    {
      minX = a_p2x;
      maxX = a_p1x;
    }

    // Find the intersection of the segment's and rectangle's x-projections

    if(maxX > a_rectangleMaxX)
    {
      maxX = a_rectangleMaxX;
    }

    if(minX < a_rectangleMinX)
    {
      minX = a_rectangleMinX;
    }

    if(minX > maxX) // If their projections do not intersect return false
    {
      return false;
    }

    // Find corresponding min and max Y for min and max X we found before

    double minY = a_p1y;
    double maxY = a_p2y;

    double dx = a_p2x - a_p1x;

    if(abs(dx) > 0.0000001)
    {
      double a = (a_p2y - a_p1y) / dx;
      double b = a_p1y - a * a_p1x;
      minY = a * minX + b;
      maxY = a * maxX + b;
    }

    if(minY > maxY)
    {
      double tmp = maxY;
      maxY = minY;
      minY = tmp;
    }

    // Find the intersection of the segment's and rectangle's y-projections

    if(maxY > a_rectangleMaxY)
    {
      maxY = a_rectangleMaxY;
    }

    if(minY < a_rectangleMinY)
    {
      minY = a_rectangleMinY;
    }

    if(minY > maxY) // If Y-projections do not intersect return false
    {
      return false;
    }

    return true;
}
