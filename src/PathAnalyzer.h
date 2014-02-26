#pragma once

#include <list>
using std::list;

#include "Vec.h"

// Forward declarations
class PathNode;
class World;


class PathAnalyzer
{
public:
    PathAnalyzer(World *world);

    /* Returns true if any optimization was done. */
    bool OptimizePath(list<PathNode*> &path);

    bool IsClearLineOfSight(PathNode *start, PathNode *b);

private:
    World *_world;

    /* Assigns path to "context+1" and end to "context+2" if
     * possible. If it is not possible, false is returne and the
     * contents of the iterators must be considered to be undefined.
     */
    bool GetIterators(const list<PathNode*>::iterator &context,
                      list<PathNode*>::iterator &mid,
                      list<PathNode*>::iterator &end);

    void GetIntersectionTestArea(PathNode *start, PathNode *end, 
								Vec &tl, Vec &br);
    void GetPathLine(PathNode *start, PathNode *end, Vec &p1, Vec &p2);

    /* Checks for intersection between the line starting at lp1 and ending
     * at lp2 going through the rectangle {rTL, rBR}.
     */
    bool LineIntersects(Vec lp1, Vec lp2, Vec rTL, Vec rBR);
};


bool SegmentIntersectRectangle(double a_rectangleMinX,
                               double a_rectangleMinY,
                               double a_rectangleMaxX,
                               double a_rectangleMaxY,
                               double a_p1x,
                               double a_p1y,
                               double a_p2x,
                               double a_p2y);
