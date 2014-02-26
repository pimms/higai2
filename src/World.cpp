#include "World.h"
#include "PathNode.h"


World::World(unsigned sizeX, unsigned sizeY)
{
    if (!sizeX || !sizeY) {
        throw "The world cannot be 0 in any dimension. World::World()";
    }

    _nodes.resize(sizeX);

    for (unsigned x = 0; x < sizeX; x++) {
        _nodes[x].resize(sizeY);
        for (unsigned y = 0; y < sizeY; y++) {
            _nodes[x][y] = new PathNode(x, y);
        }
    }
}

World::~World()
{
    for (int x = 0; x < _nodes.size(); x++) {
        for (int y = 0; y < _nodes[x].size(); y++) {
            delete _nodes[x][y];
        }
    }
}



void World::GetSize(int *x, int *y)
{
    *x = _nodes.size();
    *y = _nodes[0].size();
}

Vec World::GetSize()
{
    return Vec(_nodes.size(), _nodes[0].size());
}


PathNode* World::GetNode(int x, int y)
{
    if (x < 0 || y < 0 || x >= _nodes.size() || y >= _nodes[x].size()) {
		return NULL;
    }

    return _nodes[x][y];
}

PathNode* World::GetNode(Vec vec)
{
    return GetNode(vec.x, vec.y);
}
