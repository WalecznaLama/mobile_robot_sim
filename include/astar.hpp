#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <vector>
#include <memory>
#include "grid.hpp"

class Astar {
public:
    Astar(const Grid& grid);
    std::vector<Grid::Point> aStarPath(int startX, int startY, int goalX, int goalY);

private:
    struct Node {
        Grid::Point point;
        double gCost, hCost, fCost;
        std::shared_ptr<Node> parent;

        Node(Grid::Point p, double g, double h, std::shared_ptr<Node> par) 
            : point(p), gCost(g), hCost(h), fCost(g + h), parent(par) {}
    };

    struct CompareNode {
        bool operator()(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) const {
            return a->fCost > b->fCost;
        }
    };

    bool isValid(int x, int y);
    double calculateH(const Grid::Point &current_point, const Grid::Point &goal);

    const Grid& _grid;

    // Possible directions for movement (right, down, left, up)
    std::vector<Grid::Point> _directions = { Grid::Point(0, 1), Grid::Point(1, 0), Grid::Point(0, -1), Grid::Point(-1, 0) };
};


#endif // ASTAR_HPP
