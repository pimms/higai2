#pragma once

#include <list>
using std::list;

#include "Vec.h"
#include "Color.h"

class World;

/* Class PathNode
 *
 * The PathNode class is not aware of what
 * is done to it when pathfinding. It is simply a
 * representation of a tile, whose data can be used
 * to find a path.
 */
class PathNode
{
public:
	enum Type {
		WALKABLE,
		WALL,
	};

	PathNode(int x, int y);
	~PathNode();

	/* Returns the position of the PathNode in tilespace.
	 */
	void GetPosition(int *x, int *y) const;
	Vec GetPosition() const;

	/* The PathNode reports it's color based on its type.
	 */
	void GetColor(int *r, int *g, int *b) const;
	Color GetColor() const;

	Type GetType() const;
	void SetType(Type type);

private:
	Type _type;

	int _x;
	int _y;
};

