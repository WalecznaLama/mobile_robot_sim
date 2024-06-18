#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <vector>
#include <memory>
#include "grid.hpp"

struct Node {
    Point point;
    double gCost, hCost, fCost;
    std::shared_ptr<Node> parent;

    Node(Point p, double g, double h, std::shared_ptr<Node> par) 
        : point(p), gCost(g), hCost(h), fCost(g + h), parent(par) {}
};

struct CompareNode {
    bool operator()(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) const {
        return a->fCost > b->fCost;
    }
};

bool isValid(int x, int y);
std::vector<Point> aStar(int startX, int startY, int goalX, int goalY);

#endif // ASTAR_HPP
