#include "AStar.h"
#include "PathNode.h"
#include "Vec.h"
#include "World.h"
#include "Path.h"

/***** AStar *****/
AStar::AStar(World *world)
{

}

AStar::~AStar()
{

}


Path* AStar::Find(PathNode *start, PathNode *end)
{
    Initialize(start, end);

    bool success;
    _open.push_back(GetNode(start));
    AStarNode *node = NULL;

    while (_open.size() > 0) {
        AddToOpen(node);

        node = _open[0];
        for (int i = 1; i < _open.size(); ++i) {
            if (node < _open[i]) {
                node = _open[i];
            }
        }

        _closed.push_back(node);

        if (node->PNode() == end) {
            success = true;
            break;
        }
    }
		
	if (!success) {
		return NULL;
	}

	// Generate the path by stepping backwards
	list<PathNode*> nodes;
	while (node->GetParent()) {
		nodes.push_front(node->PNode());
		node = node->GetParent();
	}
	nodes.push_front(start);

    CleanUp();

	Path *path = new Path(_world);
	path->SetNodes(nodes);
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

void AStar::AddToOpen(AStarNode *node)
{
	Vec dirs[4] = {
		Vec(-1, 0), Vec(1, 0),
		Vec(0, -1), Vec(0, 1),
	};

	for (int i=0; i<4; i++) {
		PathNode *nb;

		Vec p = node->PNode()->GetPosition();
		p.x += dirs[i].x;
		p.y += dirs[i].y;

		nb = _world->GetNode(p);
		if (nb) {
			if (nb->GetType() == PathNode::WALKABLE) {
				AStarNode *asnb = GetNode(nb);
				_open.push_back(asnb);
				asnb->SetParent(node);
			}
		}
	}
}







/***** AStarNode ****/
AStarNode::AStarNode(PathNode *pathNode)
    :	_pnode(pathNode),
        _g(0),
        _h(0)
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

    _h = abs(p1.x-p2.x) + abs(p1.y+p2.y);
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
