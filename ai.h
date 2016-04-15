#ifndef AI_H
#define AI_H

#include "tree.hh"
#include "nodemap.h"
#include <ostream>
#include <vector>
#include <deque>

class AI
{
    protected:
        bool solved;
        int expansions;
        NodeMap *finish;
        tree<NodeMap*>::iterator *root_node;
        tree<NodeMap*>::iterator *solution_node;
    public:
        AI();
        void print(std::ostream &output_stream);
        virtual void solve(tree<NodeMap*> *puzzle_tree, tree<NodeMap*>::iterator *node)=0;
};
#endif
