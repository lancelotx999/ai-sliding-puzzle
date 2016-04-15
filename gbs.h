#ifndef GBS_H
#define GBS_H

#include "ai.h"
#include "shared.h"

class GBS: public AI
{
    public:
        GBS(NodeMap *_finish, tree<NodeMap*>::iterator *_root_node, tree<NodeMap*>::iterator *_solution_node);

        void setHeuristic(NodeMap *node);

        void solve(tree<NodeMap*> *puzzle_tree, tree<NodeMap*>::iterator *node);
};
#endif
