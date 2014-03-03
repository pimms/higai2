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
class Renderer;

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
	enum SearchType {
		GRAPH,
		TREE,
	};

    AStar(World *world);
    ~AStar();
	
	/* Rendering the pathfinding is completely optional.
	 * If the renderer is assigned, the progress will be drawn.
	 */
	void SetRenderer(Renderer *renderer);

	/* Attempts to find a path between "s" and "e". If no path is 
	 * available, NULL is returned.
	 */
    Path* Find(PathNode *s, PathNode *e, SearchType=GRAPH);

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
	void PrintStatistics(Timer t, bool success, const Path *p=NULL) const;

	/* Mapper function between PathNodes and AStarNodes. 
	 *
	 * GRAPH:
	 * If the PathNode's corresponding AStarNode has not been 
	 * requested before, it is created and stored in "_nmap".
	 *
	 * TREE:
	 * A new AStarNode* is created on every request.
	 */
    AStarNode* GetNode(PathNode*, SearchType);

	/* Back-track from the destination-AStarNode to create the
	 * full path found.
	 */
	Path* CreatePath(AStarNode *goal);

	/* Returns the next node to be examined in the pathfinding.
	 */
	AStarNode* SelectNextFromOpen();

	/* Remove the node from OPEN and put it in CLOSED. */
	void CloseNode(AStarNode *node);

	/* Remove the node from OPEN. */
	void RemoveFromOpen(AStarNode *node);

	bool IsOpen(AStarNode *node);
	bool IsClosed(AStarNode *node);

	/* Expand the node and add it's neighbours to OPEN. */
    void ExpandChildren(AStarNode *node, SearchType stype);

	/* If a Renderer has been assigned, draw the current open
	 * tile and present the buffer. The previoius tile is 
	 * drawn in it's original color.
	 */
	void DrawCurrentNode(AStarNode *prev, AStarNode *cur);

    map<PathNode*,AStarNode*> _nmap;
    PathNode *_target;

    vector<AStarNode*> _open;
    vector<AStarNode*> _closed;

    World *_world;
	Renderer *_renderer;
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

	/* Calculate the heuristics cost from _pnode to target.
	 * H = cost * manhattan_dist(_pnode, target)
	 */
    virtual void CalculateH(PathNode *target, int cost=1);
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
