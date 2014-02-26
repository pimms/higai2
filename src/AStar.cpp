#include "AStar.h"
#include "PathNode.h"
#include "Vec.h"
#include "World.h"
#include "Path.h"

/***** AStar *****/
AStar::AStar(World *world)
	:	_world(world)
{

}

AStar::~AStar()
{

}


Path* AStar::Find(PathNode *start, PathNode *end)
{
    Initialize(start, end);
	printf("Attempting to pathfind... \n");

    bool success;
    AStarNode *node = GetNode(start);
    _open.push_back(node);

    while (_open.size() > 0) {
        node = _open[0];
        for (int i = 1; i < _open.size(); ++i) {
            if (node->F() < _open[i]->F()) {
                node = _open[i];
            }
        }

        if (node->PNode() == end) {
            success = true;
            break;
        }

		CloseNode(node);
        ExpandChildren(node);
    }
		
	if (!success) {
		printf("No path available\n");
		return NULL;
	}

	printf("huge success!\n");
    CleanUp();
	
	return CreatePath(node);
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


AStarNode* AStar::GetNode(PathNode *pathnode)
{
    if (_nmap.count(pathnode) != 0) {
        return _nmap[pathnode];
    }

    AStarNode *an = new AStarNode(pathnode);
    an->CalculateH(_target);

    _nmap[pathnode] = an;
    return an;
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

bool AStar::IsExpanded(AStarNode *node) 
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

void AStar::ExpandChildren(AStarNode *node)
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
		 */
		nb = _world->GetNode(p);
		if (nb && nb->GetType() == PathNode::WALKABLE) {
			AStarNode *asnb = GetNode(nb);
			if (!IsClosed(asnb)) {
				asnb->SetParent(node);
				if (!IsExpanded(asnb)) {
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


void AStarNode::CalculateH(PathNode *target)
{
    Vec p1 = _pnode->GetPosition();
    Vec p2 = target->GetPosition();

    _h = abs(p1.x-p2.x) + abs(p1.y-p2.y);
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
