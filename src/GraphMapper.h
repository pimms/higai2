#pragma once

#include "Window.h"
#include "PathCreator.h"


// Forward declarations
class World;
class PathNode;
class Path;



class GraphMapper : public InputListener {
public:
	GraphMapper(World *world, Window *window);
	~GraphMapper();

	void OnMouseClick(Vec pos);
	void OnKeyDown(int key);

	const Path* GetPath() const;

private:
	enum ActionResult {
		ACTION_FAILURE,
		ACTION_SUCCESS,
	};

	void OnStateChanged();
	ActionResult PerformAction(PathNode *node);
	ActionResult PerformAction(PathNode *node1, PathNode *node2);
	
	PathNode* GetNodeAtPixel(int x, int y);

	void SetNewPath(Path *path);
	

	World *_world;
	Window *_window;
	PathCreator _pathcreator;
	PathNode *_lastNode;

	enum State {
		NONE, 				// Default
		PATHFIND, 			// P
		ADD_WALL,			// W
	};
	State _state;
	
};


