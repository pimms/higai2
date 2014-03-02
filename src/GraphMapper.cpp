#include "GraphMapper.h"
#include "World.h"
#include "PathNode.h"
#include "Path.h"
#include "AStar.h"


const char *GRAPH_MAPPER_HELP =
		"You can interact with the world in many different ways.\n"
		"Change between states by clicking their respective toggle-keys.\n"
		"The states alter how clicks on tiles are interpreted.\n"
		"\nStates:\n"

		"\t(p) PATHFIND\n"
		"\t\tClicks on two nodes will, if possible, find the shortest\n"
		"\t\tpath between those nodes.\n"

		"\t(w) WALL_ADD\n"
		"\t\tToggle the state of a tile - green is walkable and blue\n"
		"\t\tis a wall. The path will update when modifiying.\n" 

		"\n";



GraphMapper::GraphMapper(World *world, Window *window)
	: 	_world(world),
		_window(window),
		_state(NONE),
		_pathcreator(world)
{
	printf("%s", GRAPH_MAPPER_HELP);
}

GraphMapper::~GraphMapper()
{
}


void GraphMapper::OnMouseClick(Vec pos) 
{
	PathNode *node = GetNodeAtPixel(pos.x, pos.y);
	if (!node) return;

	/* Attempt to treat the current state as a single-PathNode-state.
	 * If ACTION_FAILURE is returned, the state requires two PathNodes.
	 */
	if (PerformAction(node) == ACTION_FAILURE) {
		/* The current state requires two PathNodes. _lastNode and
		 * the currently pressed PathNode are the two nodes in
		 * question. 
		 */
		if (_lastNode) {
			if (PerformAction(_lastNode, node) == ACTION_SUCCESS) {
				_lastNode = NULL;
			}
		} else {
			_lastNode = node;
		}
	}
}

void GraphMapper::OnKeyDown(int key) 
{
	State nstate = NONE;

	switch (key) {
		case 'p':
			nstate = PATHFIND;
			break;
		case 'w':
			nstate = ADD_WALL;
			break;
	}

	if (_state != nstate) {
		_state = nstate;
		OnStateChanged();
	}
}


const Path* GraphMapper::GetPath() const
{
	return _pathcreator.GetPath();
}


/***** Private Methods *****/
void GraphMapper::OnStateChanged() 
{
	_lastNode = NULL;
	
	char state[32];

	switch (_state) {
		case PATHFIND:
			strcpy(state, "PATHFIND");
			break;
		case ADD_WALL:
			strcpy(state, "ADD_WALL");
			break;
		case NONE:
			strcpy(state, "NONE");
			break;
	}

	printf("[%s]\n", state);
}

GraphMapper::ActionResult GraphMapper::PerformAction(PathNode *node) 
{
	switch (_state) {
		case ADD_WALL:
		{	
			bool newPath = false;
			// Toggle the type of the node
			PathNode::Type t = node->GetType();
			t = (t==PathNode::WALL) 
					? PathNode::WALKABLE 
					: PathNode::WALL;
			node->SetType(t);

			// Update the current path using the previously 
			// used PathNodes.

			/*
			¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
			Need to find the node (if exist) that is before the new
			blocking wall. 
			Do an astar search from that node
			OR
			Do an astar search again from the original node
			Not quite sure.....
			¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
			*/
			newPath = _pathcreator.TestPath(GetPath());
			//_pathcreator.FindPath();
			return ACTION_SUCCESS;
		}
		default:
			return ACTION_FAILURE;
	}

	return ACTION_FAILURE;
}

GraphMapper::ActionResult GraphMapper::PerformAction(PathNode *node1, 
													PathNode *node2) 
{
	switch (_state) {
		case NONE:
			printf("No state. See the help output.\n");
			return ACTION_FAILURE;	
		case PATHFIND: 
		{
			// Find a path between the two nodes
			_pathcreator.FindPath(node1, node2);
			return ACTION_SUCCESS;
		}
		default:
			return ACTION_FAILURE;
	}

	return ACTION_FAILURE;
}


PathNode* GraphMapper::GetNodeAtPixel(int x, int y)
{
	Vec res = _window->GetResolution();
	Vec count = _world->GetSize();
	Vec idx(x / (res.x / count.x),
			y / (res.y / count.y));
	return _world->GetNode(idx.x, idx.y);
}

