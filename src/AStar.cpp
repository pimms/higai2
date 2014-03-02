#include "AStar.h"
#include "PathNode.h"
#include "Vec.h"
#include "World.h"
#include "Path.h"
#include "Timer.h"

/***** AStar *****/
AStar::AStar(World *world)
	:	_world(world)
{

}

AStar::~AStar()
{

}


Path* AStar::Find(PathNode *start, PathNode *end, SearchType stype)
{
	const int max_iterations = 10000;
	int iterations = 0;

    Initialize(start, end);
	Timer time;
	time.Start();

    bool success = false;
    AStarNode *node = GetNode(start, stype);
    _open.push_back(node);

    while (_open.size() > 0 && ++iterations < max_iterations) {
		node = SelectNextFromOpen();

		/* DEUBG PRINT OF _OPEN */
		/*
		printf("\n_open: %lu elems\n", _open.size());
		for (int i=0; i<_open.size(); i++) {
			int x, y, f;
			_open[i]->PNode()->GetPosition(&x, &y);
			f = _open[i]->F();
			printf("%c [%i, %i] F() = %i\n", 
					node==_open[i]?'x':'-',x, y, f);
		}
		getchar();
		*/

        if (node->PNode() == end) {
            success = true;
            break;
        }

		if (stype == GRAPH) {
			CloseNode(node);
		}

        ExpandChildren(node, stype);
    }

	time.Stop();
	PrintStatistics(time, success);
		
	if (!success) {
		CleanUp();
		return NULL;
	}

	Path *path = CreatePath(node);
	CleanUp();

	return path;
}


/***** Private Methods *****/
void AStar::Initialize(PathNode *start, PathNode *end)
{
    _nmap.clear();
    _open.clear();
    _closed.clear();

    _target = end;
}

void AStar::CleanUp()
{
    map<PathNode*,AStarNode*>::iterator it;
    for (it = _nmap.begin(); it != _nmap.end(); it++) {
        delete it->second;
    }

    _target = NULL;
}


void AStar::PrintStatistics(Timer t, bool success) const
{
	printf("Path%sfound:\n", success?" ":" NOT ");

	printf(" - %f seconds spent\n", t.Get());
	printf(" - %lu nodes searched\n", _closed.size());
	printf(" - %lu open nodes\n", _open.size());
	printf("\n");
}


AStarNode* AStar::GetNode(PathNode *pathnode, AStar::SearchType stype)
{
	AStarNode *astar = NULL;

	if (stype == GRAPH) {
		if (_nmap.count(pathnode) != 0) {
			return _nmap[pathnode];
		}

		astar = new AStarNode(pathnode);
		astar->CalculateH(_target);

		_nmap[pathnode] = astar;
	} else if (stype == TREE) {
		astar = new AStarNode(pathnode);
		astar->CalculateH(_target, 2);
	}

	return astar;
}

Path* AStar::CreatePath(AStarNode *goal) 
{
	// Generate the path by stepping backwards
	list<PathNode*> nodes;
	while (goal->GetParent()) {
		nodes.push_front(goal->PNode());
		goal = goal->GetParent();
	}
	nodes.push_front(goal->PNode());

	Path *path = new Path(_world);
	path->SetNodes(nodes);
	return path;
}


AStarNode* AStar::SelectNextFromOpen() 
{
	AStarNode *node = _open[0];

	for (int i=1; i<_open.size(); i++) {
		if (_open[i]->F() <= node->F()) {
			node = _open[i];
		}
	}

	return node;
}

void AStar::CloseNode(AStarNode *node) 
{
	RemoveFromOpen(node);
	_closed.push_back(node);
}

void AStar::RemoveFromOpen(AStarNode *node) 
{
	for (int i=0; i<_open.size(); i++) {
		if (_open[i] == node) {
			_open.erase(_open.begin()+i);
			return;
		}
	}
}

bool AStar::IsOpen(AStarNode *node) 
{
	for (int i=0; i<_open.size(); i++) {
		if (_open[i] == node) {
			return true;
		}
	}

	return false;
}

bool AStar::IsClosed(AStarNode *node)
{
	for (int i=0; i<_closed.size(); i++) {
		if (_closed[i] == node) {
			return true;
		}
	}

	return false;
}

void AStar::ExpandChildren(AStarNode *node, AStar::SearchType stype)
{
	const Vec dirs[4] = {
		Vec(-1, 0), Vec(1, 0),
		Vec(0, -1), Vec(0, 1),
	};
	
	const Vec coord = node->PNode()->GetPosition();

	for (int i=0; i<4; i++) {
		PathNode *nb;

		Vec p = coord;
		p.x += dirs[i].x;
		p.y += dirs[i].y;
		
		/* The node is upated if:
		 * - The node exists
		 * - The node is not closed
		 * - The node is walkable
		 *
		 * The node is also added to the open list if 
		 * it has not been already. 
		 * Note that when tree-searching, the CLOSED list is
		 * empty at all times, and children are ALWAYS added to
		 * the OPEN list.
		 */
		nb = _world->GetNode(p);
		if (nb && nb->GetType() == PathNode::WALKABLE) {
			AStarNode *asnb = GetNode(nb, stype);
			if (!IsClosed(asnb)) {
				asnb->SetParent(node);
				if (!IsOpen(asnb) || stype == TREE) {
					_open.push_back(asnb);
				}
			}
		}
	}
}





/***** AStarNode ****/
AStarNode::AStarNode(PathNode *pathNode)
    :	_pnode(pathNode),
        _g(0),
        _h(0),
		_parent(NULL)
{

}


int AStarNode::F()
{
    return _g + _h;
}


void AStarNode::CalculateH(PathNode *target, int cost)
{
    Vec p1 = _pnode->GetPosition();
    Vec p2 = target->GetPosition();

    _h = abs(p1.x-p2.x) + abs(p1.y-p2.y);
	_h *= cost;
}

void AStarNode::SetParent(AStarNode *parent)
{
    _parent = parent;
    _g = _parent->_g + 1;
}

AStarNode* AStarNode::GetParent() 
{
	return _parent;
}


PathNode* AStarNode::PNode()
{
    return _pnode;
}


void AStarNode::PrintInfo() const 
{
	Vec pos = _pnode->GetPosition();
	printf("pos[%i,%i] - F() = g%i + h%i\n",
			pos.x, pos.y, _g, _h);
}
