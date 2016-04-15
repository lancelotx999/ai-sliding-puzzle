#ifndef BFS_H
#define BFS_H

#include "ai.h"
#include "shared.h"

class BFS: public AI
{
    public:
        BFS(NodeMap *_finish, tree<NodeMap*>::iterator *_root_node, tree<NodeMap*>::iterator *_solution_node);

        void solve(tree<NodeMap*> *puzzle_tree, tree<NodeMap*>::iterator *node);
};
#endif
