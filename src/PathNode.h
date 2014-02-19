#pragma once

#include <list>
using std::list;

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

	void GetPosition(int *x, int *y) const;
	Vec GetPosition() const;

	void GetColor(int *r, int *g, int *b) const;
	Color GetColor() const;

	Type GetType() const;
	void SetType(Type type);

	void AddNeighbour(PathNode *node);
	const list<PathNode*>& GetNeighbours() const; 	

private:
	Type _type;
	list<PathNode*> _neighbours;

	int _x;
	int _y;
};

