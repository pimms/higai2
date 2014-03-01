#pragma once

#include "Window.h"


// Forward declarations
class World;
class PathNode;
class Path;


// Virtual callback class for listening to changes to
// the terrain (walls added / removed).
class MapChangeListener {
public:
	virtual void OnTerrainChanged() = 0;
};



class GraphMapper : public InputListener {
public:
	GraphMapper(World *world, Window *window);
	~GraphMapper();

	void OnMouseClick(Vec pos);
	void OnKeyDown(int key);

	const Path* GetPath() const;

	void SetMapChangeListener(MapChangeListener *listener);

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
	Path *_path;
	MapChangeListener *_listener;

	PathNode *_lastNode;

	enum State {
		NONE, 				// Default
		PATHFIND, 			// P
		ADD_WALL,			// W
	};
	State _state;
	
};


