#include "grid.hpp"

Grid::Grid(const std::string& filename) {
    loadFromCSV(filename);
}

void Grid::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    std::string line;
    rows = 0; // Initialize row count
    cols = 0; // Initialize column count

    while (std::getline(file, line)) {
        std::vector<int> row;
        std::istringstream ss(line);
        std::string cell;
        int currentRowColumnCount = 0;

        while (getline(ss, cell, ',')) {
            row.push_back(cell == "O" ? 0 : 1); // 'O' represents an empty cell
            currentRowColumnCount++;
        }

        if (rows == 0) { // Set column count based on the first row
            cols = currentRowColumnCount;
        }

        grid.push_back(row);
        rows++;
    }
}

// Toggle between 1 (occupied) and 0 (unoccupied)
void Grid::changeOccupancy(const Grid::Point &cell) { grid[cell.x][cell.y] ^= 1; } 

int Grid::getRows() const { return rows; }

int Grid::getCols() const { return cols; }

const std::vector<std::vector<int>>& Grid::getGrid() const { return grid; }

bool Grid::isCellFree(const Point &cell) const { return getGrid()[cell.x][cell.y] == 0; }

bool Grid::isWalkable(const Point &cell, const int dirX, const int dirY) const { 
    if (!(cell.x >= 0 && cell.x < getRows() && cell.y >= 0 && cell.y < getCols() && isCellFree(cell)))
        return false;
    if (std::abs(dirX) + std::abs(dirY) == 2) // Diagonal move
        return isCellFree(Point(cell.x - dirX, cell.y)) && isCellFree(Point(cell.x, cell.y - dirY));
    return true;
}

std::vector<Grid::Point> Grid::getNeighbors(const Point &cell) const {
    std::vector<Point> neighbors;

    for (const auto& dir : move_directions) {
        Point neighbor{cell.x + dir.x, cell.y + dir.y};
        if (isWalkable(neighbor, dir.x, dir.y)) 
            neighbors.push_back(neighbor);
    }

    return neighbors;
}

double Grid::cost(const Point &move) const { return (std::abs(move.x) + std::abs(move.y) == 2) ? 1.414 : 1; } // Diagonal move cost square root of 2
