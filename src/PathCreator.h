#pragma once
#include "AStar.h"

class Path;
class World;
class PathNode;
class Renderer;


class PathCreator {
public:
	PathCreator(World *world, Renderer *renderer);
	~PathCreator();

	/* Find a path between _curA and _curB, the previously
	 * used nodes. This method should only be called if the
	 * world has changed, as it will return the exact same
	 * path otherwise.
	 */
	Path* FindPath(AStar::SearchType st);

	/* Finds a path between A and B.
	 */
	Path* FindPath(PathNode *a, PathNode *b, AStar::SearchType st);

	/* Return the path found most recently.
	 */
	Path* GetPath() const;

private:
	World *_world;
	Renderer *_renderer;

	PathNode *_curA;
	PathNode *_curB;
	Path *_path;
};
