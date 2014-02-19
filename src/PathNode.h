#pragma once

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
	void GetColor(int *r, int *g, int *b);

	Type GetType();
	void SetType(Type type);
					
private:
	Type _type;

	int _x;
	int _y;
};

