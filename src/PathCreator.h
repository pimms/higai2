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

	/* Treats the world as a partially observable environment,
	 * and simulates the path an agent would take if he was 
	 * able to view a wall from an infinite distance. This method
	 * does nothing if a wall has not been added and is blocking
	 * the existing path.
	 */
	Path* FindAgentPath();

	/* Return the path found most recently.
	 */
	Path* GetPath() const;

	/* Define wether or not to draw the intermediates in A*.
	 */
	void SetProgressRendering(bool flag);

private:
	World *_world;
	Renderer *_renderer;
	bool _drawProgress;

	PathNode *_curA;
	PathNode *_curB;
	Path *_path;
};
