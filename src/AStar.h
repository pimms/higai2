#pragma once

#include "World.h"
#include <list>
#include <vector>
#include <map>

using std::list;
using std::vector;
using std::map;

// Forward declarations
class PathNode;
class AStarNode;
class Path;
class Timer;

/* AStar
 *
 * Class responsible for finding a path between two waypoints.
 * The returned list is a set of nodes which are guaranteed to
 * have a valid, direct path. The sequential nodes need not
 * necessarily be direct neighbours - optimizations may be
 * performed.
 */
class AStar
{
public:
    AStar(World *world);
    ~AStar();

	/* Attempts to find a path between "s" and "e". If no path is 
	 * available, NULL is returned.
	 */
    Path* Find(PathNode *s, PathNode *e);

private:
	/* Initialize required values before the pathfinding actually
	 * occurs.
	 */
    void Initialize(PathNode *start, PathNode *end);

	/* Clean up after the recent path finding.
	 */
    void CleanUp();

	/* Helpful statistics about the last path-finding
	 */
	void PrintStatistics(Timer t, bool success) const;

	/* Mapper function between PathNodes and AStarNodes. If the 
	 * PathNode's corresponding AStarNode has not been requested
	 * before, it is created and stored in "_nmap".
	 */
    AStarNode* GetNode(PathNode*);

	/* Back-track from the destination-AStarNode to create the
	 * full path found.
	 */
	Path* CreatePath(AStarNode *goal);

	/* Remove the node from OPEN and put it in CLOSED. */
	void CloseNode(AStarNode *node);

	/* Remove the node from OPEN. */
	void RemoveFromOpen(AStarNode *node);

	bool IsOpen(AStarNode *node);
	bool IsClosed(AStarNode *node);

	/* Expand the node and add it's neighbours to OPEN. */
    void ExpandChildren(AStarNode *node);

    map<PathNode*,AStarNode*> _nmap;
    PathNode *_target;

    vector<AStarNode*> _open;
    vector<AStarNode*> _closed;

    World *_world;
};


/* Class AStarNode
 *
 * Class wrapping around a PathNode while associating
 * additional data to it. The extra data is used when
 * pathfinding and when generating the path once the
 * path has been defined to exist.
 */
class AStarNode
{
public:
    AStarNode(PathNode *pathNode);

    virtual int F();

    virtual void CalculateH(PathNode *target);
    virtual void SetParent(AStarNode *parent);
	AStarNode* GetParent();

    PathNode* PNode();

	void PrintInfo() const;

protected:
    PathNode *_pnode;
    AStarNode *_parent;

    int _h;
    int _g;
};
