#ifndef NODEMAP_H
#define NODEMAP_H

#include <ostream>
#include <string>

class NodeMap;
class NodeMap
{
    private:
        int x;
        int y;
        int **puzzle;
        int columns;
        int rows;
        bool start;
        std::string direction;
    public:
        NodeMap(int _x, int _y, int **_puzzle, int _columns, int _rows);

        NodeMap(int _x, int _y, int **_puzzle, int _columns, int _rows, bool _start);

        ~NodeMap();

        void copy(int **puzzle_from, int **puzzle_to, int _columns, int _rows);

        int getX() const;
        int getY() const;
        int getColumns() const;
        int getRows() const;
        int **getPuzzle() const;
        std::string getDirection() const;

        bool can_up();
        bool can_left();
        bool can_down();
        bool can_right();
        bool is_start();

        NodeMap *up();

        NodeMap *left();

        NodeMap *down();

        NodeMap *right();

        bool operator==(NodeMap& compare_node);

        bool operator==(NodeMap* compare_node);

        bool equals(NodeMap* compare_node);

        friend std::ostream& operator<<(std::ostream &os, const NodeMap &s);
        friend std::ostream& operator<<(std::ostream &os, const NodeMap *s);
};
#endif
