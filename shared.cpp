#include "shared.h"

tree<NodeMap*>::iterator get_parent(tree<NodeMap*> *tr, tree<NodeMap*>::iterator *node)
{
    return tr->parent(*node);
}

std::vector<tree<NodeMap*>::iterator> get_parents(tree<NodeMap*> *tr, tree<NodeMap*>::iterator *node)
{
    std::vector<tree<NodeMap*>::iterator> _parents;
    if (! (**node)->is_start())
    {
        tree<NodeMap*>::iterator parent;
        parent = tr->parent(*node);
        _parents.push_back(parent);
        while (parent != tr->begin())
        {
            parent = get_parent(tr, &parent);
            _parents.push_back(parent);
        }
    }
    return _parents;
}

bool is_parent(NodeMap *s, std::vector<tree<NodeMap*>::iterator> p)
{
    for (tree<NodeMap*>::iterator parent: p)
    {
        if (*(*parent) == *s)
        {
            return true;
        }
    }
    return false;
}

NodeMap *like(tree<NodeMap*>::iterator &root_node, NodeMap *compare)
{
    tree<NodeMap*>::pre_order_iterator traverse(root_node);
    while (traverse != root_node.end())
    {
        if (*(*traverse) == *compare) // Compare values
            if(*traverse != compare) // Compare pointers
                return *traverse;
        traverse++;
    }
    return NULL;
}

bool CompareNode::operator()(const tree<NodeMap*>::iterator &lhs, const tree<NodeMap*>::iterator &rhs)
{
    return (*lhs)->getHeuristic() < (*rhs)->getHeuristic();
}
