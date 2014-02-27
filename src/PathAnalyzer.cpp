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

		// Move the "end" iterator to the last visible tile
		// from "start" 
		while (tail != path.end() 
				&& IsClearLineOfSight(*start, *tail)) {
			opt = true;
			end = tail++;
		}

		// Remove everything between start and end
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
    VecF tl, br, lineP1, lineP2;
    GetIntersectionTestArea(start, end, tl, br);
    GetPathLine(start, end, lineP1, lineP2);

    for (int x = tl.x; x <= br.x; x++) {
        for (int y = tl.y; y <= br.y; y++) {
            PathNode *node = _world->GetNode(x, y);
            if (node->GetType() != PathNode::WALKABLE) {
                VecF rtl, rbr;
                rtl = node->GetPosition();
                rbr = VecF(rtl.x+1, rtl.y+1);

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
        VecF &tl, VecF &br)
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
                                VecF &p1, VecF &p2)
{
    p1 = start->GetPosition();
    p2 = end->GetPosition();

	p1.x += 0.5f;
	p1.y += 0.5f;
	p2.x += 0.5f;
	p2.y += 0.5f;
}


bool PathAnalyzer::LineIntersects(VecF lp1, VecF lp2, VecF rTL, VecF rBR)
{
	return LineIntersectsRect(lp1, lp2, rTL, rBR);
}



/* Line Intersection Algorithm
 * Code based on:	http://stackoverflow.com/q/5514366
 */
bool LineIntersectsRect(VecF p1, VecF p2, VecF topLeft, VecF botRight)
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
	VecF l = topLeft;
	VecF r = botRight;
	return ( 
		LineIntersectsLine(p1, p2, VecF(l.x, l.y), VecF(r.x, l.y)) ||
		LineIntersectsLine(p1, p2, VecF(l.x, l.y), VecF(l.x, r.y)) ||
		LineIntersectsLine(p1, p2, VecF(r.x, r.y), VecF(r.x, l.y)) ||
		LineIntersectsLine(p1, p2, VecF(r.x, r.y), VecF(l.x, r.y))
	);	
}

bool LineIntersectsLine(VecF l1p1, VecF l1p2, VecF l2p1, VecF l2p2)
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
