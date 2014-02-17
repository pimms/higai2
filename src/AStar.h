#pragma once 

#include <list>
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
	AStar();
	~AStar();

	list<PathNode*> Find(PathNode *s, PathNode *e);

private:
};
