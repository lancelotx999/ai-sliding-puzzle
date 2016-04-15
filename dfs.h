#ifndef DFS_H
#define DFS_H

#include "ai.h"
#include "shared.h"

class DFS: public AI
{
    public:
        DFS(NodeMap *_finish, tree<NodeMap*>::iterator *_root_node, tree<NodeMap*>::iterator *_solution_node);

        void solve(tree<NodeMap*> *puzzle_tree, tree<NodeMap*>::iterator *node);
};
#endif
