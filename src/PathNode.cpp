#include "PathNode.h"
#include "PathAnalyzer.h"
#include "World.h"
#include <stdio.h>


PathNode::PathNode(int x, int y)
    : 	_x(x),
        _y(y)
{
    _type = PathNode::WALKABLE;
}

PathNode::~PathNode()
{

}

struct nodeValue {
    int g;
    int h;
};

void PathNode::GetPosition(int *x, int *y) const
{
    *x = _x;
    *y = _y;
}

Vec PathNode::GetPosition() const
{
    return VecI(_x, _y);
}


void PathNode::GetColor(int *r, int *g, int *b) const
{
    Color c = GetColor();

    *r = c.r;
    *g = c.g;
    *b = c.b;
}

Color PathNode::GetColor() const
{
    switch (_type) {
    case WALKABLE:
        return Color(0, 180, 0);
    case WALL:
        return Color(0, 0, 160);
    }

    return Color(0, 255, 0);
}

PathNode::Type PathNode::GetType() const
{
    return _type;
}

void PathNode::SetType(PathNode::Type type)
{
    _type = type;
}


bool PathNode::AddNeighbour(World *world, PathNode *node)
{
	bool success = false;

	PathAnalyzer analyzer(world);
	if (!analyzer.IsClearLineOfSight(this, node)) {
		return false;
	}

	if (this == node) {
		return false;
	}

	if (!IsNeighbour(node)) {
    	_neighbours.push_back(node);
		success = true;
	}

	if (!node->IsNeighbour(this)) {
		node->_neighbours.push_back(this);
		success = true;
	}

	return success;
}

bool PathNode::RemoveNeighbour(PathNode *node)
{
	if (IsNeighbour(node)) {
		_neighbours.remove(node);

		if (node->IsNeighbour(this)) {
			node->_neighbours.remove(this);
		}

		return true;
	}

	return false;
}

bool PathNode::IsNeighbour(PathNode *node) 
{
	list<PathNode*>::iterator it;
	for (it=_neighbours.begin(); it!=_neighbours.end(); it++) {
		if (*it == node) {
			return true;
		}
	}

	return false;
}

const list<PathNode*>& PathNode::GetNeighbours() const
{
    return _neighbours;
}
