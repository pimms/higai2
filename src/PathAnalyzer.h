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

	/* Are there any non-walkable tiles between the two tiles?
	 */
    bool IsClearLineOfSight(PathNode *start, PathNode *b);

private:
    World *_world;

	/* Return the axis-aligned bounding box between the start- and
	 * end-positions. All tiles in this area should be tested for
	 * intersection when calculating LOS.
	 */
    void GetIntersectionTestArea(PathNode *start, PathNode *end, 
								VecF &tl, VecF &br);

	/* Assigns the positions of "start" and "end" in "pq" and "p2". 
	 * The points are modified slightly to accurately point to the
	 * center of the tile rather than the top-left corner.
	 */
    void GetPathLine(PathNode *start, PathNode *end, VecF &p1, VecF &p2);
	
	/* Are all the nodes on the path-segment between "start" and
	 * "end" on a straight line with no tunrns?
	 */
	bool IsSegmentOneDimensional(const list<PathNode*>::iterator &start,
								 const list<PathNode*>::iterator &end);

    /* Checks for intersection between the line starting at lp1 and ending
     * at lp2 going through the rectangle {rTL, rBR}.
     */
    bool LineIntersects(VecF lp1, VecF lp2, VecF rTL, VecF rBR);
};

bool LineIntersectsRect(VecF p1, VecF p2, VecF topLeft, VecF botRight);
bool LineIntersectsLine(VecF l1p1, VecF l1p2, VecF l2p1, VecF l2p2);
