#pragma once 

#include "World.h"
#include <list>
#include <vector>
using std::list;


// Forward declarations
class PathNode;


/* AStar
 *
 * Class responsible for finding a path between two waypoints.
 * The returned list is a set of nodes which are guaranteed to
 * have a valid, direct path. The sequential nodes need not 
 * necessarily be direct neighbours - optimizations may be 
 * performed.
 */
class AStar {
public:
	AStar(World *world);
	~AStar();

	list<PathNode*> Find(PathNode *s, PathNode *e);
	void addToOpen(PathNode *node);
	virtual int f();

private:
	std::vector<PathNode*> open;
	std::vector<PathNode*> closed;
	World *_world;
};


/*
struct AStarNode {
		PathNode *parent;
		PathNode* node;
		int h;
		int g;
	};
*/