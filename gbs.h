#ifndef GBS_H
#define GBS_H

#include "ai.h"
#include "shared.h"

class GBS: public AI
{
    private:
        std::priority_queue<tree<NodeMap*>::iterator, std::vector<tree<NodeMap*>::iterator>, CompareNode> span;
    public:
        GBS(NodeMap *_finish, tree<NodeMap*>::iterator *_root_node, tree<NodeMap*>::iterator *_solution_node);

        void setHeuristic(NodeMap *node);

        void solve(tree<NodeMap*> *puzzle_tree, tree<NodeMap*>::iterator *node);
};
#endif
