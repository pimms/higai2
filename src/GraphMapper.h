#pragma once

#include "Window.h"
#include "PathCreator.h"
#include "AStar.h"


// Forward declarations
class World;
class PathNode;
class Path;
class Renderer;


/* Class GraphMapper
 *
 * Class used to handle input.
 * TODO: Rename the class to something more appropriate.
 */
class GraphMapper : public InputListener
{
public:
	GraphMapper(World *world, Window *window, Renderer *renderer);
	~GraphMapper();

	void OnMouseClick(Vec pos);
	void OnKeyDown(int key);

	/* Return the current path. */
	const Path* GetPath() const;

private:
	/* Used when attempting to perform actions.
	 */
	enum ActionResult {
		ACTION_FAILURE,
		ACTION_SUCCESS,
	};

	void OnStateChanged();

	/* Attempts to perform an action based on the current state.
	 * If the current state requires only a single PathNode, it
	 * should perform it's action here and return ACTION_SUCCESS.
	 * Called after a PathNode has been clicked.
	 */
	ActionResult PerformAction(PathNode *node);

	/* Attempts to perform an action based on the current state.
	 * This method is called when PerformAction(PathNode*) has
	 * failed twice. States requiring two PathNodes to function
	 * should perform their action here and return ACTION_SUCCESS.
	 */
	ActionResult PerformAction(PathNode *node1, PathNode *node2);

	PathNode* GetNodeAtPixel(int x, int y);

	void NewPath();

	void FindNewPath(PathNode *a, PathNode *end);


	World *_world;
	Window *_window;
	Renderer *_renderer;
	PathCreator _pathcreator;
	PathNode *_lastNode;

	/* The GraphMapper can exist in either of these states.
	 * The states are changed through key-presses. The states
	 * should be used to differentiate how presses of tiles
	 * are handled. States can need either one or two PathNodes
	 * to be able to perform their designated action.
	 */
	enum State {
		NONE, 				// Default
		PATHFIND, 			// P
		ADD_WALL,			// W
	};
	State _state;

	AStar::SearchType _searchType;
	bool _drawProgress;
};


