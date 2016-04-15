#include "as.h"

AS::AS(NodeMap *_finish, tree<NodeMap*>::iterator *_root_node, tree<NodeMap*>::iterator *_solution_node):
    AI()
{
    finish = _finish;
    root_node = _root_node;
    solution_node = _solution_node;
}

void AS::setHeuristic(NodeMap *node, int cost)
{
    int **finish_puzzle = finish->getPuzzle();
    int **node_puzzle = node->getPuzzle();
    int differences(0);
    for (int i(0); i < finish->getRows(); i++)
    {
        for (int ii(0); ii < finish->getColumns(); ii++)
        {
            if (finish_puzzle[i][ii] != node_puzzle[i][ii])
                differences++;
        }
    }
    node->setHeuristic(differences + cost);
}

void AS::solve(tree<NodeMap*> *puzzle_tree, tree<NodeMap*>::iterator *node)
{
    solve(puzzle_tree, node, 0);
}

void AS::solve(tree<NodeMap*> *puzzle_tree, tree<NodeMap*>::iterator *node, int cost)
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
            cost++;
            setHeuristic(next, cost);
            child = puzzle_tree->append_child(*node, next);
            expansions++;
            span.push(child);
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
            cost++;
            setHeuristic(next, cost);
            child = puzzle_tree->append_child(*node, next);
            expansions++;
            span.push(child);
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
            cost++;
            setHeuristic(next, cost);
            child = puzzle_tree->append_child(*node, next);
            expansions++;
            span.push(child);
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
            cost++;
            setHeuristic(next, cost);
            child = puzzle_tree->append_child(*node, next);
            expansions++;
            span.push(child);
        }
    }

    tree<NodeMap*>::iterator next = span.top();
    span.pop();
    solve(puzzle_tree, &next);
}
