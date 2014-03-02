#pragma once

class Path;
class World;
class PathNode;


class PathCreator {
public:
	PathCreator(World *world);
	~PathCreator();

	/* Find a path between _curA and _curB, the previously
	 * used nodes. This method should only be called if the
	 * world has changed, as it will return the exact same
	 * path otherwise.
	 */
	Path* FindPath();

	/* Finds a path between A and B.
	 */
	Path* FindPath(PathNode *a, PathNode *b);

	/* Return the path found most recently.
	 */
	Path* GetPath() const;

	bool TestPath(const Path *path);

private:
	World *_world;

	PathNode *_curA;
	PathNode *_curB;
	Path *_path;
};
