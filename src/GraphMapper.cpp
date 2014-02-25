#include "GraphMapper.h"
#include "World.h"

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



GraphMapper::GraphMapper(World *world)
	: 	_world(world),
		_state(NONE)
{
	printf("%s", GRAPH_MAPPER_HELP);
}


void GraphMapper::OnMouseClick(Vec pos) 
{
	
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
void GraphMapper::OnStateChanged() {
			
}
