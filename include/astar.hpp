#ifndef ASTAR_HPP
#define ASTAR_HPP

#include "IPathfinder.hpp"
#include <memory>
#include <queue>
#include <algorithm>
#include <cmath>
#include <iostream>

// Implements the A* pathfinding algorithm on a grid.
class AStar : public IPathfinder {
public:
    explicit AStar(const Grid& grid);
    std::vector<Grid::Point> findPath(const Grid::Point& start, const Grid::Point& goal) const override;

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

    double calculateH(const Grid::Point& current_point, const Grid::Point& goal) const;

    const Grid& _grid;

};

#endif // ASTAR_HPP
