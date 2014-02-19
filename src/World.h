#pragma once 

#include <vector>
using std::vector;

#include "Vec.h"

// Forward declarations
class PathNode;


class World {
public:
	World(unsigned sizeX, unsigned sizeY);
	~World();
	
	void GetSize(int *x, int *y);
	Vec GetSize();
	
	PathNode* GetNode(int x, int y);
	PathNode* GetNode(Vec v);

private:
	vector< vector<PathNode*> > _nodes;
};
