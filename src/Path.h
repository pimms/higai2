#pragma once

#include <list>
using std::list;


// Forward declarations
class PathNode;
class World;

class Path {
public:
	Path(World *world);

	void SetNodes(list<PathNode*> nodes);
	const list<PathNode*>& GetNodes() const;
	const list<PathNode*>& GetOptimized() const;

private:
	World *_world;
	list<PathNode*> _nodes;
	list<PathNode*> _optimized;
};
