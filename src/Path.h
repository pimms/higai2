#pragma once

#include <list>
using std::list;


// Forward declarations
class PathNode;
class World;


/* Class Path
 *
 * A fancy wrapper around a list of PathNodes. The path
 * is attempted optimized when assigned to the Path.
 */
class Path
{
public:
	static Path* JoinPaths(Path *path1, Path *path2, World *world);

	Path(World *world);

	void SetNodes(list<PathNode*> nodes);

	/* Get the unoptimized path */
	const list<PathNode*>& GetNodes() const;

	/* Get the optimized path */
	const list<PathNode*>& GetOptimized() const;

	float GetLength(const list<PathNode*> &nodes) const;
	float GetLength() const;
	float GetOptimizedLength() const;

	const PathNode* GetSplitDivisor() const;

private:
	World *_world;
	list<PathNode*> _nodes;
	list<PathNode*> _optimized;

	PathNode *_divisor;
};
