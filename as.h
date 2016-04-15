#ifndef AS_H
#define AS_H

#include "ai.h"
#include "shared.h"

class AS: public AI
{
    private:
        std::priority_queue<tree<NodeMap*>::iterator, std::vector<tree<NodeMap*>::iterator>, CompareNode> span;
    public:
        AS(NodeMap *_finish, tree<NodeMap*>::iterator *_root_node, tree<NodeMap*>::iterator *_solution_node);

        void setHeuristic(NodeMap *node, int cost);

        void solve(tree<NodeMap*> *puzzle_tree, tree<NodeMap*>::iterator *node);
        void solve(tree<NodeMap*> *puzzle_tree, tree<NodeMap*>::iterator *node, int cost);
};
#endif
