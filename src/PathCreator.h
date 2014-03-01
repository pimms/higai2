#pragma once

class Path;
class World;
class PathNode;


class PathCreator {
public:
	PathCreator(World *world);
	~PathCreator();

	Path* FindPath();
	Path* FindPath(PathNode *a, PathNode *b);

	Path* GetPath() const;

private:
	World *_world;

	PathNode *_curA;
	PathNode *_curB;
	Path *_path;
};
