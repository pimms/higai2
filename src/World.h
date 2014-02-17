#pragma once 

#include <vector>
using std::vector;

// Forward declarations
class PathNode;


class World {
public:
	World(unsigned sizeX, unsigned sizeY);
	~World();
	
	PathNode* GetNode(int x, int y);

private:
	vector< vector<PathNode*> > _nodes;
};
