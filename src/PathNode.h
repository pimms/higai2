#pragma once

#include "Vec.h"
#include "Color.h"

/* The PathNode class should not be aware of what
 * the pathfinding algorithm does. Calculate G, H and F 
 * values in a wrapper class of some description.
 */
class PathNode {
public:
	enum Type {
		WALKABLE,
		WALL,
	};

	PathNode(int x, int y);
	~PathNode();

	void GetPosition(int *x, int *y);
	Vec GetPosition();

	void GetColor(int *r, int *g, int *b);
	Color GetColor();


	Type GetType();
	void SetType(Type type);

private:
	Type _type;

	int _x;
	int _y;
};

