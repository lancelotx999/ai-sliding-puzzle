#ifndef SHARED_H
#define SHARED_H

#include "tree.hh"
#include "nodemap.h"
#include <vector>

tree<NodeMap*>::iterator get_parent(tree<NodeMap*> *tr, tree<NodeMap*>::iterator *node);

std::vector<tree<NodeMap*>::iterator> get_parents(tree<NodeMap*> *tr, tree<NodeMap*>::iterator *node);

bool is_parent(NodeMap *s, std::vector<tree<NodeMap*>::iterator> p);

NodeMap *like(tree<NodeMap*>::iterator &root_node, NodeMap *compare);

class CompareNode
{
    public:
        bool operator()(const tree<NodeMap*>::iterator &lhs, const tree<NodeMap*>::iterator &rhs);
};
#endif
