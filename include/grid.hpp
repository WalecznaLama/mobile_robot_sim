#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// Represents a grid loaded from a CSV file where each cell can have different states.
class Grid {
public:
    // Constructor that initializes the grid from a CSV file.
    Grid(const std::string& filename);

    // Represents a point or position in the grid.
    struct Point {
        int x, y;
        Point(int x_coord, int y_coord) : x(x_coord), y(y_coord) {}
        bool operator==(const Point& other) const { return x == other.x && y == other.y; }
        bool operator!=(const Point& other) const { return !(*this == other); }
    };

    // Changes the occupancy state of a specified cell in the grid.
    void changeOccupancy(const Point &cell);

    // Returns the number of rows in the grid.
    int getRows() const;

    // Returns the number of columns in the grid.
    int getCols() const;

    // Provides read-only access to the grid data.
    const std::vector<std::vector<int>>& getGrid() const;

private:
    // Loads grid data from the specified CSV file.
    void loadFromCSV(const std::string& filename);

    int rows, cols;
    std::vector<std::vector<int>> grid;
};

#endif // GRID_HPP
