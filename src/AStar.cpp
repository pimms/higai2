#include "AStar.h"
#include "PathNode.h"
#include <vector>

AStar::AStar() {
	
}

AStar::~AStar() {

}


list<PathNode*> Find(PathNode *start, PathNode *end) {
	bool success;
	std::vector<PathNode*> open;
	std::vector<PathNode*> closed;

	while (open.size() > 0) {

		PathNode *node = open[0];
	
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