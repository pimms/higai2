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
	"\t\tpath between those nodes.\n";



GraphMapper::GraphMapper(World *world, Window *window)
	: 	_world(world),
		_window(window),
		_state(NONE),
		_path(NULL)
{
	printf("%s", GRAPH_MAPPER_HELP);
}

GraphMapper::~GraphMapper()
{
	if (_path) {
		delete _path;
	}
}

void GraphMapper::OnMouseClick(Vec pos) 
{
	PathNode *node = GetNodeAtPixel(pos.x, pos.y);
	if (!node) return;
	
	if (_lastNode) {
		if (PerformAction(_lastNode, node) == ACTION_SUCCESS) {
			_lastNode = NULL;
		}
	} else {
		_lastNode = node;
	}
}

void GraphMapper::OnKeyDown(int key) 
{
	switch (key) {
		case 'p':
			if (_state != PATHFIND) {
				_state = PATHFIND;
				OnStateChanged();
			}
			break;
	}
}


const Path* GraphMapper::GetPath() const
{
	return _path;
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
		case NONE:
			strcpy(state, "NONE");
			break;
	}

	printf("[%s]\n", state);
}

GraphMapper::ActionResult GraphMapper::PerformAction(PathNode *node1, 
													PathNode *node2) 
{
	switch (_state) {
		case NONE:
			printf("No state. See the help output.\n");
			return ACTION_FAILURE;	
		case PATHFIND:
			AStar astar(_world);
			SetNewPath(astar.Find(node1, node2));
			break;
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


void GraphMapper::SetNewPath(Path *path)
{
	if (_path) {
		delete _path;
	}

	_path = path;
}
