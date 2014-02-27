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

		while (tail != path.end() 
				&& IsClearLineOfSight(*start, *tail)) {
			opt = true;
			end = tail++;
		}
	
		list<PathNode*>::iterator it = start;
		for (it++; it != end; ) {
			it = path.erase(it);
		}

		start = end;
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
	return LineIntersectsRect(lp1, lp2, rTL, rBR);
}



/* Line Intersection Algorithm
 * Code taken from:	http://stackoverflow.com/q/5514366
 */
bool LineIntersectsRect(Vec p1, Vec p2, Vec topLeft, Vec botRight)
{
	// If p1 or p2 is contained in the rectangle, they intersect 
	if (p1.x > topLeft.x && p1.x < botRight.x &&
		p1.y > topLeft.y && p1.y < botRight.y) {
		return true;
	}

	if (p2.x > topLeft.x && p2.x < botRight.x &&
		p2.y > topLeft.y && p2.y < botRight.y) {
		return true;
	}

	// If the line intersects any of the four lines in the
	// rectangle, an intersection is happening.
	Vec l = topLeft;
	Vec r = botRight;
	return ( 
		LineIntersectsLine(p1, p2, Vec(l.x, l.y), Vec(r.x, l.y)) ||
		LineIntersectsLine(p1, p2, Vec(l.x, l.y), Vec(l.x, r.y)) ||
		LineIntersectsLine(p1, p2, Vec(r.x, r.y), Vec(r.x, l.y)) ||
		LineIntersectsLine(p1, p2, Vec(r.x, r.y), Vec(l.x, r.y))
	);	
}

bool LineIntersectsLine(Vec l1p1, Vec l1p2, Vec l2p1, Vec l2p2)
{
	float q = (l1p1.y-l2p1.y)*(l2p2.x-l2p1.x)
			 -(l1p1.x-l2p1.x)*(l2p2.y-l2p1.y);
	float d = (l1p2.x-l1p1.x)*(l2p2.y-l2p1.y)
			 -(l1p2.y-l1p1.y)*(l2p2.x-l2p1.x);

	if( d == 0 ) {
		return false;
	}

	float r = q / d;

	q = (l1p1.y - l2p1.y)*(l1p2.x-l1p1.x)
	   -(l1p1.x-l2p1.x)*(l1p2.y-l1p1.y);
	float s = q / d;

	if (r < 0 || r > 1 || s < 0 || s > 1) {
		return false;
	}

	return true;
}
