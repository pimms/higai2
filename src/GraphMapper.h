#pragma once

#include "Window.h"


// Forward declarations
class World;

class GraphMapper : public InputListener {
public:
	GraphMapper(World *world);

	void OnMouseClick(Vec pos);
	void OnKeyDown(int key);

private:
	void OnStateChanged();

	World *_world;

	enum State {
		NONE, 				// Default
		WAYPOINT_SET, 		// W
		WAYPOINT_REMOVE, 	// R
		PATHFIND, 			// P
	};
	State _state;
};


