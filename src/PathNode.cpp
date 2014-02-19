#include "PathNode.h"
#include <stdio.h>


PathNode::PathNode(int x, int y) 
	: 	_x(x),
		_y(y) 
{
	this->GetPosition(NULL, NULL);
	this->GetPosition(NULL, NULL);

	_type = Type::WALKABLE;
}

PathNode::~PathNode() {

}

struct nodeValue {
	int g;
	int h;
};

void PathNode::GetPosition(int *x, int *y) {
	*x = _x;
	*y = _y;
}

Vec PathNode::GetPosition() {
	return VecI(_x, _y);
}

void PathNode::GetColor(int *r, int *g, int *b) {
	*r = 0;
	*g = 255;
	*b = 0;
}

PathNode::Type PathNode::GetType() {
	return _type;
}

void PathNode::SetType(PathNode::Type type) {
	_type = type;
}