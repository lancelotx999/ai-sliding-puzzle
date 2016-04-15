#ifndef AS_H
#define AS_H

#include "ai.h"
#include "shared.h"

class AS: public AI
{
    public:
        AS(NodeMap *_finish, tree<NodeMap*>::iterator *_root_node, tree<NodeMap*>::iterator *_solution_node);

        void setHeuristic(NodeMap *node);

        void solve(tree<NodeMap*> *puzzle_tree, tree<NodeMap*>::iterator *node);
};
#endif
