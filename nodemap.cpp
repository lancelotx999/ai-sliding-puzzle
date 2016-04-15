#include "nodemap.h"

NodeMap::NodeMap(int _x, int _y, int **_puzzle, int _columns, int _rows):
    x(_x), y(_y), columns(_columns), rows(_rows), start(false)
{
    puzzle = _puzzle;
}

NodeMap::NodeMap(int _x, int _y, int **_puzzle, int _columns, int _rows, bool _start):
    x(_x), y(_y), columns(_columns), rows(_rows), start(_start)
{
    puzzle = _puzzle;
}

NodeMap::~NodeMap()
{
    for (int i(0); i < rows; i++)
    {
        delete [] puzzle[i];
    }
    delete [] puzzle;
}

void NodeMap::copy(int **puzzle_from, int **puzzle_to, int _columns, int _rows)
{
    for (int i(0); i < _rows; i++)
    {
        for (int ii(0); ii < _columns; ii++)
        {
            puzzle_to[i][ii] = puzzle_from[i][ii];
        }
    }
}

int NodeMap::getX() const { return x; }
int NodeMap::getY() const { return y; }
int NodeMap::getColumns() const { return columns; }
int NodeMap::getRows() const { return rows; }
int **NodeMap::getPuzzle() const { return puzzle; }
std::string NodeMap::getDirection() const { return direction; }

bool NodeMap::can_up() { return x > 0; }
bool NodeMap::can_left() { return y > 0; }
bool NodeMap::can_down() { return x < rows - 1; }
bool NodeMap::can_right() { return y < columns - 1; }
bool NodeMap::is_start() { return start; }

NodeMap *NodeMap::up()
{
    direction = "Up;";
    int **new_puzzle = new int*[rows];
    for (int i(0); i < rows; i++)
    {
        new_puzzle[i] = new int[columns];
    }
    copy(puzzle, new_puzzle, columns, rows);
    int swap = puzzle[x-1][y];
    new_puzzle[x-1][y] = new_puzzle[x][y];
    new_puzzle[x][y] = swap;
    NodeMap *node = new NodeMap(x - 1, y, new_puzzle, columns, rows);
    return node;
}

NodeMap *NodeMap::left()
{
    direction = "Left;";
    int **new_puzzle = new int*[rows];
    for (int i(0); i < rows; i++)
    {
        new_puzzle[i] = new int[columns];
    }
    copy(puzzle, new_puzzle, columns, rows);
    int swap = puzzle[x][y-1];
    new_puzzle[x][y-1] = new_puzzle[x][y];
    new_puzzle[x][y] = swap;
    NodeMap *node = new NodeMap(x, y - 1, new_puzzle, columns, rows);
    return node;
}

NodeMap *NodeMap::down()
{
    direction = "Down;";
    int **new_puzzle = new int*[rows];
    for (int i(0); i < rows; i++)
    {
        new_puzzle[i] = new int[columns];
    }
    copy(puzzle, new_puzzle, columns, rows);
    int swap = puzzle[x+1][y];
    new_puzzle[x+1][y] = new_puzzle[x][y];
    new_puzzle[x][y] = swap;
    NodeMap *node = new NodeMap(x + 1, y, new_puzzle, columns, rows);
    return node;
}

NodeMap *NodeMap::right()
{
    direction = "Right;";
    int **new_puzzle = new int*[rows];
    for (int i(0); i < rows; i++)
    {
        new_puzzle[i] = new int[columns];
    }
    copy(puzzle, new_puzzle, columns, rows);
    int swap = puzzle[x][y+1];
    new_puzzle[x][y+1] = new_puzzle[x][y];
    new_puzzle[x][y] = swap;
    NodeMap *node = new NodeMap(x, y + 1, new_puzzle, columns, rows);
    return node;
}

bool NodeMap::operator==(NodeMap& compare_node)
{
    int **compare_puzzle = compare_node.getPuzzle();
    for (int i(0); i < rows; i++)
    {
        for (int ii(0); ii < columns; ii++)
        {
            if (compare_puzzle[i][ii] != puzzle[i][ii])
                return false;
        }
    }
    return true;
}

bool NodeMap::operator==(NodeMap* compare_node)
{
    int **compare_puzzle = compare_node->getPuzzle();
    for (int i(0); i < rows; i++)
    {
        for (int ii(0); ii < columns; ii++)
        {
            if (compare_puzzle[i][ii] != puzzle[i][ii])
                return false;
        }
    }
    return true;
}

bool NodeMap::equals(NodeMap* compare_node)
{
    int **compare_puzzle = compare_node->getPuzzle();
    for (int i(0); i < rows; i++)
    {
        for (int ii(0); ii < columns; ii++)
        {
            if (compare_puzzle[i][ii] != puzzle[i][ii])
                return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream &os, const NodeMap &s)
{
    for (int i(0); i < s.getRows(); i++)
    {
        for (int ii(0); ii < s.getColumns(); ii++)
        {
            os << s.getPuzzle()[i][ii] << " ";
        }
        os << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const NodeMap *s)
{
    for (int i(0); i < s->getRows(); i++)
    {
        for (int ii(0); ii < s->getColumns(); ii++)
        {
            os << s->getPuzzle()[i][ii] << " ";
        }
        os << std::endl;
    }
    return os;
}
