#include <iostream>
#include <fstream>
#include <sstream>
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

#ifdef DEBUG
        void print() 
        {
            cerr << x << " " << y << endl;
            for (int i(0); i < rows; i++)
            {
                for (int ii(0); ii < columns; ii++)
                {
                    cerr << puzzle[i][ii] << " ";
                }
                cerr << endl;
            }
        }
#endif

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
#ifdef DEBUG
                cerr << solution_map[i][ii] << " ";
#endif
            }
#ifdef DEBUG
            cerr << endl;
#endif
        }

        NodeMap *start = new NodeMap(x, y, puzzle_map, columns, rows);
        NodeMap *next = start->up();
        NodeMap *next_left = next->left();
        NodeMap *next_right = next->right();
        NodeMap *next_down = next_right->down();
        NodeMap *finish = new NodeMap(x, y, solution_map, columns, rows);
#ifdef DEBUG
        cerr << "Start" << endl;
        start->print();
        cerr << "Start moves up" << endl;
        next->print();
        cerr << "Next moves left" << endl;
        next_left->print();
        cerr << "Next moves right" << endl;
        next_right->print();
        cerr << "Right moves down" << endl;
        next_down->print();
        cerr << "Finish" << endl;
        finish->print();
#endif
        delete start;
        delete next;
        delete next_left;
        delete next_right;
        delete next_down;
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
