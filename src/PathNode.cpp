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


void PathNode::GetPosition(int *x, int *y) {
	*x = _x;
	*y = _y;
}
