#include "grid.hpp"
#include <fstream>
#include <sstream>
#include <string>

Grid::Grid(const std::string& filename) { loadFromCSV(filename); }

void Grid::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    rows = 0;  // Initialize rows
    cols = 0;  // Initialize cols

    while (std::getline(file, line)) {
        std::vector<int> row;
        std::string cell;
        std::istringstream ss(line);
        int tempCols = 0;  // Temporary column count

        while (getline(ss, cell, ',')) {
            row.push_back(cell == "O" ? 0 : 1);
            tempCols++;
        }

        if (rows == 0) {  // Set cols based on the first row
            cols = tempCols;
        }

        grid.push_back(row);
        rows++;
    }
}

void Grid::changeOccupancy(const Grid::Point &cell) { grid[cell.x][cell.y] ^= 1; } // Toggle between 1 and 0 using XOR

const int Grid::getRows() const { return rows; }

const int Grid::getCols() const { return cols; }

const std::vector<std::vector<int>>& Grid::getGrid() const { return grid; }