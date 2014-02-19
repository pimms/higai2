#include "AStar.h"
#include "PathNode.h"
#include "Vec.h"
#include "World.h"

AStar::AStar(World *world) {

}

AStar::~AStar() {

}


list<PathNode*> AStar::Find(PathNode *start, PathNode *end) {
	bool success;
	open.push_back(start);
	PathNode *node = start;

	while (open.size() > 0) {

		addToOpen(node);
		node = open[0];
	
		for (int i = 1; i < open.size(); ++i) {
			if (node < open[i]) {
				node = open[i];
			}
		}

		closed.push_back(node);

		if (node == end) {
			success = true;
			break;
		}
	}


	return list<PathNode*>();
}


/***** Private Methods *****/
void AStar::addToOpen(PathNode *node) {
	Vec pos = node->GetPosition();

	const list<PathNode*> nbs = node->GetNeighbours();
	list<PathNode*>::const_iterator it; 

	for (it = nbs.begin(); it != nbs.end(); it++) {
		PathNode *nb = *it;
		if (nb->GetType() == PathNode::WALKABLE) {
			open.push_back(nb);
		}
	}
}

int f() {
	//return pathValue.h + pathValue.g;
	return 0;
}
