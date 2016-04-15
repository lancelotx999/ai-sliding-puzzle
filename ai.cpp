#include "ai.h"

AI::AI():
    solved(false), expansions(0)
{}

void AI::print(std::ostream &output_stream)
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
