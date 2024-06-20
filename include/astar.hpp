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
    std::vector<Grid::Point> findPath(int startX, int startY, int goalX, int goalY);

private:
    struct Node {
        Grid::Point point;
        double gCost, hCost, fCost; // Cost from start, heuristic to goal, and total cost respectively.
        std::shared_ptr<Node> parent;

        Node(Grid::Point p, double g, double h, std::shared_ptr<Node> par)
            : point(p), gCost(g), hCost(h), fCost(g + h), parent(par) {}
    };

    struct CompareNode {
        bool operator()(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) const {
            return a->fCost > b->fCost;
        }
    };

    bool isValid(int x, int y, int dirX, int dirY);
    double calculateH(const Grid::Point& current_point, const Grid::Point& goal);

    const Grid& _grid;
    std::vector<Grid::Point> _directions = {
        Grid::Point(1, 0), Grid::Point(0, 1), Grid::Point(-1, 0), Grid::Point(0, -1),
        Grid::Point(1, 1), Grid::Point(-1, 1), Grid::Point(-1, -1), Grid::Point(1, -1)
    };
};

#endif // ASTAR_HPP
