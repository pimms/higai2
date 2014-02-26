#include "AStar.h"
#include "PathNode.h"
#include "Vec.h"
#include "World.h"

/***** AStar *****/
AStar::AStar(World *world)
{

}

AStar::~AStar()
{

}


list<PathNode*> AStar::Find(PathNode *start, PathNode *end)
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

    CleanUp();
    return list<PathNode*>();
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
	printf("TODO: Add neighbours\n");
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


PathNode* AStarNode::PNode()
{
    return _pnode;
}
