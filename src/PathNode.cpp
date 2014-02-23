#include "PathNode.h"
#include <stdio.h>


PathNode::PathNode(int x, int y) 
	: 	_x(x),
		_y(y) 
{
	_type = PathNode::WALKABLE;
}

PathNode::~PathNode() {

}

struct nodeValue {
	int g;
	int h;
};

void PathNode::GetPosition(int *x, int *y) const {
	*x = _x;
	*y = _y;
}

Vec PathNode::GetPosition() const {
	return VecI(_x, _y);
}


void PathNode::GetColor(int *r, int *g, int *b) const {
	Color c = GetColor();

	*r = c.r;
	*g = c.g;
	*b = c.b;
}

Color PathNode::GetColor() const {
	switch (_type) {
		case WALKABLE:
			return Color(0, 180, 0);
		case WALL:
			return Color(0, 0, 160);
	}
	
	return Color(0, 255, 0);
}

PathNode::Type PathNode::GetType() const {
	return _type;
}

void PathNode::SetType(PathNode::Type type) {
	_type = type;
}


void PathNode::AddNeighbour(PathNode *node) {
	_neighbours.push_back(node);
}

const list<PathNode*>& PathNode::GetNeighbours() const {
	return _neighbours;
}
