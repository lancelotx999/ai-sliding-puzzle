#include "bfs.h"
#include <iostream>

BFS::BFS(NodeMap *_finish, tree<NodeMap*>::iterator *_root_node, tree<NodeMap*>::iterator *_solution_node):
    solved(false), expansions(0)
{
    finish = _finish;
    root_node = _root_node;
    solution_node = _solution_node;
}

void BFS::print(std::ostream &output_stream)
{
    if (! solved) return;
    std::deque<NodeMap*> moves;
    moves.push_front(*(*solution_node));

    tree<NodeMap*>::pre_order_iterator DIT(*solution_node);
    tree_node_<NodeMap*> solution_node = DIT.get_node();
    tree_node_<NodeMap*> *solution_node_parent = solution_node.parent;

    moves.push_front(solution_node_parent->data);

    int steps(1);

    while(! solution_node_parent->data->is_start())
    {
        solution_node_parent= solution_node_parent->parent;
        moves.push_front(solution_node_parent->data);
        steps++;
    }

    std::deque<NodeMap*>::iterator move = moves.begin();

    output_stream << expansions << " " << steps << " ";
    while (move != moves.end())
    {
        output_stream << (*move)->getDirection() << " ";
        move++;
    }
    output_stream << std::endl;
}

void BFS::solve(tree<NodeMap*> *puzzle_tree, tree<NodeMap*>::iterator *node)
{
    NodeMap *current = *(*node);
    if (solved) return;
    if (*current == *finish)
    {
        solved = true;
        solution_node = node;
        return;
    }

    std::deque<tree<NodeMap*>::iterator*> span;

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
            span.push_back(&child);
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
            span.push_back(&child);
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
            span.push_back(&child);
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
            span.push_back(&child);
        }
    }

    std::deque<tree<NodeMap*>::iterator*>::iterator child = span.begin();
    while (child != span.end())
    {
        solve(puzzle_tree, *child);
        child++;
    }
}
