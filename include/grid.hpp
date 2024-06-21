#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

// Represents a grid loaded from a CSV file where each cell can have different states.
class Grid {
public:
    // Constructor that initializes the grid from a CSV file.
    Grid(const std::string& filename);

    // Represents a point or position in the grid.
    struct Point {
        int x, y;
        Point() : x(0), y(0) {}  // Default constructor
        Point(int x_coord, int y_coord) : x(x_coord), y(y_coord) {}
        bool operator==(const Point& other) const { return x == other.x && y == other.y; }
        bool operator!=(const Point& other) const { return !(*this == other); }
        Point operator-(const Point& other) const { return Point(x-other.x, y-other.y); }

        bool operator<(const Point& other) const {
            if (x == other.x) return y < other.y;
            return x < other.x;
        }
    };

    // Changes the occupancy state of a specified cell in the grid.
    void changeOccupancy(const Point &cell);

    // Returns the number of rows in the grid.
    int getRows() const;

    // Returns the number of columns in the grid.
    int getCols() const;

    // Provides read-only access to the grid data.
    const std::vector<std::vector<int>>& getGrid() const;

    // Check if the cell is free from obstacles
    bool isCellFree(const Point &cell) const; 

    // Check if the cell is in grid borders and free from obstacles
    bool isWalkable(const Point &cell, const int dirX, const int dirY) const; 

    // Retrieve walkable neighboring cells
    std::vector<Point> getNeighbors(const Point &cell) const; 

    // Returns the cost of move.
    double cost(const Point &move) const;

    const std::vector<Point> move_directions = {
        Point(1, 0), Point(0, 1),  Point(-1, 0),  Point(0, -1),
        Point(1, 1), Point(-1, 1), Point(-1, -1), Point(1, -1)
    };

private:
    // Loads grid data from the specified CSV file.
    void loadFromCSV(const std::string& filename);

    int rows, cols;
    std::vector<std::vector<int>> grid;
};

#endif // GRID_HPP
