#ifndef BFS_H
#define BFS_H

#include "tree.hh"
#include "nodemap.h"
#include "shared.h"
#include <ostream>
#include <vector>
#include <deque>

class BFS
{
    private:
        bool solved;
        int expansions;
        NodeMap *finish;
        tree<NodeMap*>::iterator *root_node;
        tree<NodeMap*>::iterator *solution_node;
    public:
        BFS(NodeMap *_finish, tree<NodeMap*>::iterator *_root_node, tree<NodeMap*>::iterator *_solution_node);

        void print(std::ostream &output_stream);

        void solve(tree<NodeMap*> *puzzle_tree, tree<NodeMap*>::iterator *node);
};
#endif
