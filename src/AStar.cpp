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

void AStar::addToOpen(PathNode *node) {
	Vec pos = node->GetPosition();

	Vec vecs[4];

	vecs[0] = Vec(pos.x, pos.y + 1);
	vecs[1] = Vec(pos.x, pos.y - 1);
	vecs[2] = Vec(pos.x - 1, pos.y);
	vecs[3] = Vec(pos.x - 1, pos.y);

	for (int i = 0; i < 4; ++i)
	{
		if (_world->GetNode(vecs[i].x, vecs[i].y)->GetType() == PathNode::WALKABLE) {
			open.push_back(_world->GetNode(vecs[i].x, vecs[i].y));
			
		}
	}
}

int AStar::f() {
	//return pathValue.h + pathValue.g;
}