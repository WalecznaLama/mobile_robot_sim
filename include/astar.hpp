#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <vector>

struct Point {
    int x, y;
    Point(int px, int py) : x(px), y(py) {}
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Point& other) const { return !(*this == other); }
};

struct Node {
    Point point;
    double gCost, hCost, fCost;
    Node* parent;

    Node(Point p, double g, double h, Node* par) : point(p), gCost(g), hCost(h), fCost(g + h), parent(par) {}
};

struct CompareNode {
    bool operator()(const Node* a, const Node* b) const {
        return a->fCost > b->fCost;
    }
};

bool isValid(int x, int y);
std::vector<Point> aStar(int startX, int startY, int goalX, int goalY);

#endif // ASTAR_HPP
