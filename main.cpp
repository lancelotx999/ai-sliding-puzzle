#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <string>
#include <algorithm>
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
    public:
        NodeMap(int _x, int _y, int **_puzzle, int _columns, int _rows):
            x(_x), y(_y), columns(_columns), rows(_rows)
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

        NodeMap *start = new NodeMap(x, y, puzzle_map, columns, rows);
        NodeMap *finish = new NodeMap(X, Y, solution_map, columns, rows);

        tree<NodeMap*> puzzle_tree;
        tree<NodeMap*>::iterator tree_node, root_node;
        tree_node = puzzle_tree.begin();
        root_node = puzzle_tree.insert(tree_node, start);
#ifdef DEBUG
        kptree::print_tree_bracketed(puzzle_tree, cout);
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
