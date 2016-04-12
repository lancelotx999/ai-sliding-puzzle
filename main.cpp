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
