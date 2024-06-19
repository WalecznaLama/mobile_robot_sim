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

void Grid::changeOccupancy(const Grid::Point &cell) {
    grid[cell.x][cell.y] ^= 1; // Toggle between 1 (occupied) and 0 (unoccupied)
}

int Grid::getRows() const { return rows; }

int Grid::getCols() const { return cols; }

const std::vector<std::vector<int>>& Grid::getGrid() const { return grid; }
