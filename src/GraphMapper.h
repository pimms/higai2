#pragma once

#include "Window.h"


// Forward declarations
class World;
class PathNode;


class GraphMapper : public InputListener {
public:
	GraphMapper(World *world, Window *window);

	void OnMouseClick(Vec pos);
	void OnKeyDown(int key);

private:
	enum ActionResult {
		ACTION_FAILURE,
		ACTION_SUCCESS,
	};

	void OnStateChanged();
	ActionResult PerformAction(PathNode *node1, PathNode *node2);
	
	PathNode* GetNodeAtPixel(int x, int y);
	

	World *_world;
	Window *_window;

	PathNode *_lastNode;

	enum State {
		NONE, 				// Default
		WAYPOINT_SET, 		// W
		WAYPOINT_REMOVE, 	// R
		PATHFIND, 			// P
	};
	State _state;
	
};


