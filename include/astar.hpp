#ifndef ASTAR_HPP
#define ASTAR_HPP

#include "grid.hpp"
#include <vector>
#include <memory>
#include <queue>
#include <algorithm>
#include <cmath>
#include <iostream>

// Implements the A* pathfinding algorithm on a grid.
class AStar {
public:
    explicit AStar(const Grid& grid);
    // Calculates the path from start to goal using the A* algorithm.
    std::vector<Grid::Point> findPath(int startX, int startY, int goalX, int goalY);

private:
    // Represents a node in the pathfinding algorithm, holding costs and parent for backtracking.
    struct Node {
        Grid::Point point;
        double gCost, hCost, fCost; // Cost from start, heuristic to end, and total cost respectively.
        std::shared_ptr<Node> parent;

        Node(Grid::Point p, double g, double h, std::shared_ptr<Node> par) 
            : point(p), gCost(g), hCost(h), fCost(g + h), parent(par) {}
    };

    // Comparator for prioritizing nodes based on their total cost.
    struct CompareNode {
        bool operator()(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) const {
            return a->fCost > b->fCost;
        }
    };

    // Checks if the specified coordinates are within the grid boundaries and not in obstacle.
    bool isValid(int x, int y);
    // Calculates the heuristic value (H-cost) from the current point to the goal.
    double calculateH(const Grid::Point &current_point, const Grid::Point &goal);

    const Grid& _grid; // Reference to the grid on which the pathfinding is performed.

    // Directions representing possible movement (right, down, left, up).
    std::vector<Grid::Point> _directions = { Grid::Point(0, 1), Grid::Point(1, 0), Grid::Point(0, -1), Grid::Point(-1, 0) };
};

#endif // ASTAR_HPP
