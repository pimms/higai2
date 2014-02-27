#pragma once

#include <list>
using std::list;

#include "Vec.h"

// Forward declarations
class PathNode;
class World;

/* The path analyzer optimizes and proves analytical
 * insight to a path in the node-grid.
 */
class PathAnalyzer
{
public:
    PathAnalyzer(World *world);

    /* Returns true if any optimization was done. 
	 * The optimization is done by incrementally remove any
	 * redundant node B in the path "A-B-C" if there is a clear
	 * sight between A and C. 
	 */
    bool OptimizePath(list<PathNode*> &path);

    bool IsClearLineOfSight(PathNode *start, PathNode *b);

private:
    World *_world;

    void GetIntersectionTestArea(PathNode *start, PathNode *end, 
								Vec &tl, Vec &br);
    void GetPathLine(PathNode *start, PathNode *end, Vec &p1, Vec &p2);

    /* Checks for intersection between the line starting at lp1 and ending
     * at lp2 going through the rectangle {rTL, rBR}.
     */
    bool LineIntersects(Vec lp1, Vec lp2, Vec rTL, Vec rBR);
};

bool LineIntersectsRect(Vec p1, Vec p2, Vec topLeft, Vec botRight);
bool LineIntersectsLine(Vec l1p1, Vec l1p2, Vec l2p1, Vec l2p2);
