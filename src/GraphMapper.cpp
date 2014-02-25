#include "GraphMapper.h"
#include "World.h"
#include "PathNode.h"

const char *GRAPH_MAPPER_HELP = 
	"You can interact with the world in many different ways.\n"
	"Change between states by clicking their respective toggle-keys.\n"
	"The states alter how clicks on tiles are interpreted.\n"
	"\nStates:\n"
	"\t(w) WAYPOINT_SET\n"
	"\t\tSequential clicks on two unconnected path nodes will create\n"
	"\t\ta waypoint-connection between them.\n\n"

	"\t(r) WAYPOINT_REMOVE\n"
	"\t\tSequential clicks on two connected path nodes will brea\n"
	"\t\tthe connection between them.\n\n"
	
	"\t(p) PATHFIND\n"
	"\t\tClicks on two nodes will, if possible, find the shortest\n"
	"\t\tpath between those nodes.\n";



GraphMapper::GraphMapper(World *world, Window *window)
	: 	_world(world),
		_window(window),
		_state(NONE)
{
	printf("%s", GRAPH_MAPPER_HELP);
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
		case 'w':
			if (_state != WAYPOINT_SET) {
				_state = WAYPOINT_SET;
				OnStateChanged();
			}
			break;

		case 'r':
			if (_state != WAYPOINT_REMOVE) {
				_state = WAYPOINT_REMOVE;
				OnStateChanged();
			}
			break;

		case 'p':
			if (_state != PATHFIND) {
				_state = PATHFIND;
				OnStateChanged();
			}
			break;
	}
}


/***** Private Methods *****/
void GraphMapper::OnStateChanged() 
{
	_lastNode = NULL;
	
	char state[32];

	switch (_state) {
		case WAYPOINT_SET:
			strcpy(state, "WAYPOINT_SET");
			break;
		case WAYPOINT_REMOVE:
			strcpy(state, "WAYPOINT_REMOVE");
			break;
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
		case WAYPOINT_SET:
			if (node1->AddNeighbour(_world, node2)) {
				return ACTION_SUCCESS;
			} break;
		case WAYPOINT_REMOVE:
			if (node1->RemoveNeighbour(node2)) {
				return ACTION_SUCCESS;
			} break;
		case PATHFIND:
			printf("Pathfind yolo\n");
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
