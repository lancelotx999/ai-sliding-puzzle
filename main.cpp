#include <sys/resource.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <string>
#include <algorithm>

#include "tree.hh"
#include "nodemap.h"
#include "shared.h"
#include "dfs.h"

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
        tree<NodeMap*>::iterator tree_node, root_node, sollution_node;
        tree_node = puzzle_tree.begin();
        root_node = puzzle_tree.insert(tree_node, start);

        DFS *dfs = new DFS(&root_node, &sollution_node);
        dfs->solve(start, finish, &puzzle_tree, &root_node);
        dfs->print(cout);
        
#ifdef DEBUG
        //kptree::print_tree_bracketed(puzzle_tree, cerr);
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
        const rlim_t kStackSize = 16 * 1024 * 1024; // Increase stack size to use a maximum of 16GB RAM, required for DFS
        struct rlimit rl;
        int result;

        result = getrlimit(RLIMIT_STACK, &rl);
        if (result == 0)
        {
            if (rl.rlim_cur < kStackSize)
            {
                rl.rlim_cur = kStackSize;
                result = setrlimit(RLIMIT_STACK, &rl);
            }
        }
        return solve(argv[1], argv[2]);
    }
    else return EXIT_FAILURE;
}
