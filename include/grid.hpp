#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

const int ROWS = 10;
const int COLS = 10;

extern int grid[ROWS][COLS];

struct Point {
    int x, y;
    Point(int px, int py) : x(px), y(py) {}
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Point& other) const { return !(*this == other); }
};

#endif // GRID_HPP
