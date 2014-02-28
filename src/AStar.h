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

    Path* Find(PathNode *s, PathNode *e);

private:
    void Initialize(PathNode *start, PathNode *end);
    void CleanUp();

	void PrintStatistics(Timer t, bool success) const;

    AStarNode* GetNode(PathNode*);
	Path* CreatePath(AStarNode *goal);

	void CloseNode(AStarNode *node);
	void RemoveFromOpen(AStarNode *node);
	bool IsExpanded(AStarNode *node);
	bool IsClosed(AStarNode *node);
    void ExpandChildren(AStarNode *node);

    map<PathNode*,AStarNode*> _nmap;
    PathNode *_target;

    vector<AStarNode*> _open;
    vector<AStarNode*> _closed;

    World *_world;
};


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
