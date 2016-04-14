#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <string>
#include <algorithm>
#include <vector>
#include "tree.hh"
#ifdef DEBUG
    #include "tree_util.hh"
#endif

#define ALGO_DEPTH_FIRST        "DFS"
#define ALGO_BREADTH_FIRST      "BFS"
#define ALGO_GREEDY_BEST_FIRST  "GBS"
#define ALGO_A_STAR             "AS"
#define ALGO_BEAM               "BEAM"
#define ALGO_SEAN               "SEAN"

using namespace std;

class NodeMap
{
    private:
        int x;
        int y;
        int **puzzle;
        int columns;
        int rows;
        bool start;
    public:
        NodeMap(int _x, int _y, int **_puzzle, int _columns, int _rows):
            x(_x), y(_y), columns(_columns), rows(_rows), start(false)
        {
            puzzle = _puzzle;
        }

        NodeMap(int _x, int _y, int **_puzzle, int _columns, int _rows, bool _start):
            x(_x), y(_y), columns(_columns), rows(_rows), start(_start)
        {
            puzzle = _puzzle;
        }

        ~NodeMap()
        {
            for (int i(0); i < rows; i++)
            {
                delete [] puzzle[i];
            }
            delete [] puzzle;
        }

        static void copy(int **puzzle_from, int **puzzle_to, int _columns, int _rows)
        {
            for (int i(0); i < _rows; i++)
            {
                for (int ii(0); ii < _columns; ii++)
                {
                    puzzle_to[i][ii] = puzzle_from[i][ii];
                }
            }
        }

        int getX() const { return x; }
        int getY() const { return y; }
        int getColumns() const { return columns; }
        int getRows() const { return rows; }
        int **getPuzzle() const { return puzzle; }

        bool can_up() { return x > 0; }
        bool can_left() { return y > 0; }
        bool can_down() { return x < rows - 1; }
        bool can_right() { return y < columns - 1; }
        bool is_start() { return start; }

        NodeMap *up()
        {
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

        NodeMap *left()
        {
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

        NodeMap *down()
        {
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

        NodeMap *right()
        {
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

        inline bool operator==(const NodeMap& compare_node)
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

        inline bool operator==(const NodeMap* compare_node)
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
};

ostream& operator<<(std::ostream &os, const NodeMap &s)
{
    for (int i(0); i < s.getRows(); i++)
    {
        for (int ii(0); ii < s.getColumns(); ii++)
        {
            os << s.getPuzzle()[i][ii] << " ";
        }
        os << endl;
    }
    return os;
}

ostream& operator<<(std::ostream &os, const NodeMap *s)
{
    for (int i(0); i < s->getRows(); i++)
    {
        for (int ii(0); ii < s->getColumns(); ii++)
        {
            os << s->getPuzzle()[i][ii] << " ";
        }
        os << endl;
    }
    return os;
}

tree<NodeMap*>::iterator get_parent(tree<NodeMap*> *tr, tree<NodeMap*>::iterator *node)
{
    return tr->parent(*node);
}

vector<tree<NodeMap*>::iterator> get_parents(tree<NodeMap*> *tr, tree<NodeMap*>::iterator *node)
{
    vector<tree<NodeMap*>::iterator> _parents;
    if (! (**node)->is_start())
    {
        tree<NodeMap*>::iterator parent;
        parent = tr->parent(*node);
        _parents.push_back(parent);
        while (parent != tr->begin())
        {
            parent = get_parent(tr, &parent);
            _parents.push_back(parent);
        }
    }
    return _parents;
}

bool is_parent(NodeMap *s, vector<tree<NodeMap*>::iterator> p)
{
    for (tree<NodeMap*>::iterator parent: p)
    {
        if (*parent == s)
        {
            return true;
        }
    }
    return false;
}

class BFS
{
    private:
        bool solved;
    public:
        BFS():
            solved(false)
    {
    }
        void solve(NodeMap *current, NodeMap *finish, tree<NodeMap*> *puzzle_tree, tree<NodeMap*>::iterator *node)
        {
#ifdef DEBUG
            cerr << "Current:" << endl;
            cerr << current << endl;
#endif
            if (solved) return;
            if (current == finish)
            {
                cout << "solved" << endl;
                solved = true;
                return;
            }
            if (current->can_up())
            {
                vector<tree<NodeMap*>::iterator> _parents = get_parents(puzzle_tree, node);
                tree<NodeMap*>::iterator child;
                NodeMap *next = current->up();
#ifdef DEBUG
                cerr << "Next:" << endl;
                cerr << next << endl;
#endif
                if (! is_parent(next, _parents))
                {
                    child = puzzle_tree->append_child(*node, next);
                    solve(next, finish, puzzle_tree, &child);
                }
            }
            if (current->can_left())
            {
                vector<tree<NodeMap*>::iterator> _parents = get_parents(puzzle_tree, node);
                tree<NodeMap*>::iterator child;
                NodeMap *next = current->left();
                if (! is_parent(next, _parents))
                {
                    child = puzzle_tree->append_child(*node, next);
                    solve(next, finish, puzzle_tree, &child);
                }
            }
            if (current->can_down())
            {
                vector<tree<NodeMap*>::iterator> _parents = get_parents(puzzle_tree, node);
                tree<NodeMap*>::iterator child;
                NodeMap *next = current->down();
                if (! is_parent(next, _parents))
                {
                    child = puzzle_tree->append_child(*node, next);
                    solve(next, finish, puzzle_tree, &child);
                }
            }
            if (current->can_right())
            {
                vector<tree<NodeMap*>::iterator> _parents = get_parents(puzzle_tree, node);
                tree<NodeMap*>::iterator child;
                NodeMap *next = current->right();
                if (! is_parent(next, _parents))
                {
                    child = puzzle_tree->append_child(*node, next);
                    solve(next, finish, puzzle_tree, &child);
                }
            }
        }
};

bool verify_file(string file)
{
    ifstream exists(file);
    return exists.good();
}

bool verify_algorithm(string algorithm)
{
    return 
        algorithm == ALGO_DEPTH_FIRST       ||
        algorithm == ALGO_BREADTH_FIRST     ||
        algorithm == ALGO_GREEDY_BEST_FIRST ||
        algorithm == ALGO_A_STAR            ||
        algorithm == ALGO_BEAM              ||
        algorithm == ALGO_SEAN;
}

int solve(string file, string algorithm)
{
    if (verify_file(file) && verify_algorithm(algorithm))
    {
        ifstream puzzle(file);
        string line;
        stringstream size_stream;
        int columns(0);
        int rows(0);
        int x, y;
        int X, Y;

        getline(puzzle, line);
        replace(line.begin(), line.end(), 'x', ' ');
        size_stream << line;
        size_stream >> columns >> rows;
        int **puzzle_map = new int*[rows];
        int **solution_map = new int*[rows];
        for (int i(0); i < rows; i++)
        {
            puzzle_map[i] = new int[columns];
            solution_map[i] = new int[columns];
        }
#ifdef DEBUG
        cout << columns << "x" << rows << endl;
#endif

        stringstream puzzle_stream;
        getline(puzzle, line);
        puzzle_stream << line;
#ifdef DEBUG
        cerr << line << endl;
#endif

        for (int i(0); i < rows; i++)
        {
            for (int ii(0); ii < columns; ii++)
            {
                puzzle_stream >> puzzle_map[i][ii];
                if (puzzle_map[i][ii] == 0)
                {
                    x = i;
                    y = ii;
                }
#ifdef DEBUG
                cerr << puzzle_map[i][ii] << " ";
#endif
            }
#ifdef DEBUG
            cerr << endl;
#endif
        }

        stringstream solution_stream;
        getline(puzzle, line);
        solution_stream << line;
#ifdef DEBUG
        cerr << line << endl;
#endif

        for (int i(0); i < rows; i++)
        {
            for (int ii(0); ii < columns; ii++)
            {
                solution_stream >> solution_map[i][ii];
                if (solution_map[i][ii] == 0)
                {
                    X = i;
                    Y = ii;
                }
#ifdef DEBUG
                cerr << solution_map[i][ii] << " ";
#endif
            }
#ifdef DEBUG
            cerr << endl;
#endif
        }

        NodeMap *start = new NodeMap(x, y, puzzle_map, columns, rows, true);
        NodeMap *finish = new NodeMap(X, Y, solution_map, columns, rows);

        tree<NodeMap*> puzzle_tree;
        tree<NodeMap*>::iterator tree_node, root_node;
        tree_node = puzzle_tree.begin();
        root_node = puzzle_tree.insert(tree_node, start);


        BFS *bfs = new BFS();
        bfs->solve(start, finish, &puzzle_tree, &root_node);
#ifdef DEBUG
        kptree::print_tree_bracketed(puzzle_tree, cerr);
#endif

        delete start;
        delete finish;

        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        return solve(argv[1], argv[2]);
    }
    else return EXIT_FAILURE;
}
