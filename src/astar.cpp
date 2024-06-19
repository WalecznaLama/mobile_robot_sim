#include "astar.hpp"
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

Astar::Astar(const Grid& grid) : _grid(grid) {}

// Check if a position (x, y) is valid within the grid and not an obstacle
bool Astar::isValid(int x, int y) {
    return (x >= 0 && x < _grid.getRows() && y >= 0 && y < _grid.getCols() && _grid.getGrid()[x][y] == 0);
}

// Calculate the heuristic value (Manhattan distance) from current_point to the goal
double Astar::calculateH(const Grid::Point &current_point, const Grid::Point &goal) {
    return std::abs(current_point.x - goal.x) + std::abs(current_point.y - goal.y);
}

// A* pathfinding algorithm implementation
std::vector<Grid::Point> Astar::aStarPath(int startX, int startY, int goalX, int goalY) {
    // Priority queue to store open nodes, ordered by fCost
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, CompareNode> openList;
    std::vector<std::shared_ptr<Node>> allNodes; // To keep track of all nodes for memory cleanup

    Grid::Point start(startX, startY);
    Grid::Point goal(goalX, goalY);

    // Initialize the start node
    auto startNode = std::make_shared<Node>(start, 0, calculateH(start, goal), nullptr);
    openList.push(startNode);
    allNodes.push_back(startNode);

    // Visited array to keep track of visited nodes
    bool visited[_grid.getRows()][_grid.getCols()] = { false };
    visited[startX][startY] = true;

    // Main loop for the A* algorithm
    while (!openList.empty()) {
        // Get the node with the lowest fCost
        auto currentNode = openList.top();
        openList.pop();

        // If the goal is reached, reconstruct the path
        if (currentNode->point == goal) {
            std::vector<Grid::Point> path;
            auto pathNode = currentNode;
            while (pathNode != nullptr) {
                path.push_back(pathNode->point);
                pathNode = pathNode->parent;
            }
            std::reverse(path.begin(), path.end()); // Reverse the path to get the correct order
            return path; // Return the found path
        }

        // Explore neighbors
        for (auto& d : _directions) {
            int newX = currentNode->point.x + d.x;
            int newY = currentNode->point.y + d.y;
            if (isValid(newX, newY) && !visited[newX][newY]) {
                visited[newX][newY] = true; // Mark the neighbor as visited
                auto neighborNode = std::make_shared<Node>(Grid::Point(newX, newY),
                                                           currentNode->gCost + 1,
                                                           calculateH(Grid::Point(newX, newY), goal),
                                                           currentNode);
                openList.push(neighborNode); // Add the neighbor to the open list
                allNodes.push_back(neighborNode); // Keep track of all nodes
            }
        }
    }

    return {};  // If no path is found, return an empty path
}
