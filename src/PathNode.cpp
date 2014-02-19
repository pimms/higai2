#include "PathNode.h"
#include <stdio.h>


PathNode::PathNode(int x, int y) 
	: 	_x(x),
		_y(y) 
{
	this->GetPosition(NULL, NULL);
	this->GetPosition(NULL, NULL);
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

void PathNode::GetColor(int *r, int *g, int *b) {
	*r = 0;
	*g = 255;
	*b = 0;
}

int f() {
	return nodeValue.g + nodeValue.h;
}