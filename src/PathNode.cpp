#include "PathNode.h"
#include <stdio.h>


PathNode::PathNode(int x, int y) 
	: 	_x(x),
		_y(y) 
{
	this->GetPosition(NULL, NULL);
	this->GetPosition(NULL, NULL);

	_type = PathNode::WALKABLE;
}

PathNode::~PathNode() {

}


void PathNode::GetPosition(int *x, int *y) {
	*x = _x;
	*y = _y;
}

Vec PathNode::GetPosition() {
	return VecI(_x, _y);
}


void PathNode::GetColor(int *r, int *g, int *b) {
	Color c = GetColor();

	*r = c.r;
	*g = c.g;
	*b = c.b;
}

Color PathNode::GetColor() {
	switch (_type) {
		case WALKABLE:
			return Color(0, 180, 0);
		case WALL:
			return Color(0, 0, 160);
	}
	
	return Color(0, 255, 0);
}


PathNode::Type PathNode::GetType() {
	return _type;
}

void PathNode::SetType(PathNode::Type type) {
	_type = type;
}
