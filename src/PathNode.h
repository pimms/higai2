#pragma once


class PathNode {
public:
	PathNode(int x, int y);
	~PathNode();
	
	void GetPosition(int *x, int *y);

					
private:
	int _x;
	int _y;
};

