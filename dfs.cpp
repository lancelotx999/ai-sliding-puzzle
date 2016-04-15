#include "dfs.h"

DFS::DFS(NodeMap *_finish, tree<NodeMap*>::iterator *_root_node, tree<NodeMap*>::iterator *_solution_node):
    AI()

{
    finish = _finish;
    root_node = _root_node;
    solution_node = _solution_node;
}

void DFS::solve(tree<NodeMap*> *puzzle_tree, tree<NodeMap*>::iterator *node)
{
    NodeMap *current = *(*node);
    if (solved) return;
    if (*current == *finish)
    {
        solved = true;
        solution_node = node;
        return;
    }
    if (current->can_up())
    {
        if (solved) return;
        std::vector<tree<NodeMap*>::iterator> _parents = get_parents(puzzle_tree, node);
        tree<NodeMap*>::iterator child;
        NodeMap *next = current->up();
        NodeMap *like_next = like(*root_node, next);
        if (like_next != NULL)
        {
            delete next;
            next = like_next;
        }
        if (! is_parent(next, _parents))
        {
            child = puzzle_tree->append_child(*node, next);
            expansions++;
            solve(puzzle_tree, &child);
        }
    }
    if (current->can_left())
    {
        if (solved) return;
        std::vector<tree<NodeMap*>::iterator> _parents = get_parents(puzzle_tree, node);
        tree<NodeMap*>::iterator child;
        NodeMap *next = current->left();
        NodeMap *like_next = like(*root_node, next);
        if (like_next != NULL)
        {
            delete next;
            next = like_next;
        }
        if (! is_parent(next, _parents))
        {
            child = puzzle_tree->append_child(*node, next);
            expansions++;
            solve(puzzle_tree, &child);
        }
    }
    if (current->can_down())
    {
        if (solved) return;
        std::vector<tree<NodeMap*>::iterator> _parents = get_parents(puzzle_tree, node);
        tree<NodeMap*>::iterator child;
        NodeMap *next = current->down();
        NodeMap *like_next = like(*root_node, next);
        if (like_next != NULL)
        {
            delete next;
            next = like_next;
        }
        if (! is_parent(next, _parents))
        {
            child = puzzle_tree->append_child(*node, next);
            expansions++;
            solve(puzzle_tree, &child);
        }
    }
    if (current->can_right())
    {
        if (solved) return;
        std::vector<tree<NodeMap*>::iterator> _parents = get_parents(puzzle_tree, node);
        tree<NodeMap*>::iterator child;
        NodeMap *next = current->right();
        NodeMap *like_next = like(*root_node, next);
        if (like_next != NULL)
        {
            delete next;
            next = like_next;
        }
        if (! is_parent(next, _parents))
        {
            child = puzzle_tree->append_child(*node, next);
            expansions++;
            solve(puzzle_tree, &child);
        }
    }
}
