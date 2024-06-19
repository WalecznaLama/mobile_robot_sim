#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>

class Grid {
public:
    Grid(const std::string& filename);

    struct Point {
        int x, y;
        Point(int px, int py) : x(px), y(py) {}
        bool operator==(const Point& other) const { return x == other.x && y == other.y; }
        bool operator!=(const Point& other) const { return !(*this == other); }
    };

    void changeOccupancy(const Point &cell);

    const int getRows() const;
    const int getCols() const;
    const std::vector<std::vector<int>>& getGrid() const;

private:
    void loadFromCSV(const std::string& filename);  // Load grid from CSV file

    int rows, cols;
    std::vector<std::vector<int>> grid;

};

#endif // GRID_HPP




