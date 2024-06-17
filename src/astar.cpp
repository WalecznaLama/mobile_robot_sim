#include "astar.hpp"
#include "grid.hpp"
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

// Check if a position (x, y) is valid within the grid and not an obstacle
bool isValid(int x, int y) { return (x >= 0 && x < ROWS && y >= 0 && y < COLS && grid[x][y] == 0); }

// Calculate the heuristic value (Manhattan distance) from point p to the goal
double calculateH(Point p, Point goal) { return std::abs(p.x - goal.x) + std::abs(p.y - goal.y); }

// A* pathfinding algorithm implementation
std::vector<Point> aStar(int startX, int startY, int goalX, int goalY) {
    // Priority queue to store open nodes, ordered by fCost
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openList;
    std::vector<Node*> allNodes; // To keep track of all nodes for memory cleanup

    Point start(startX, startY);
    Point goal(goalX, goalY);

    // Initialize the start node
    Node* startNode = new Node(start, 0, calculateH(start, goal), nullptr);
    openList.push(startNode);
    allNodes.push_back(startNode);

    // Visited array to keep track of visited nodes
    bool visited[ROWS][COLS] = { false };
    visited[startX][startY] = true;

    // Possible directions for movement (right, down, left, up)
    std::vector<Point> directions = { Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0) };

    // Main loop for the A* algorithm
    while (!openList.empty()) {
        // Get the node with the lowest fCost
        Node* currentNode = openList.top();
        openList.pop();

        // If the goal is reached, reconstruct the path
        if (currentNode->point == goal) {
            std::vector<Point> path;
            Node* pathNode = currentNode;
            while (pathNode != nullptr) {
                path.push_back(pathNode->point);
                pathNode = pathNode->parent;
            }
            std::reverse(path.begin(), path.end()); // Reverse the path to get the correct order
            for (Node* node : allNodes) {
                delete node; // Clean up all allocated nodes
            }
            return path; // Return the found path
        }

        // Explore neighbors
        for (auto& d : directions) {
            int newX = currentNode->point.x + d.x;
            int newY = currentNode->point.y + d.y;
            if (isValid(newX, newY) && !visited[newX][newY]) {
                visited[newX][newY] = true; // Mark the neighbor as visited
                Node* neighborNode = new Node(Point(newX, newY),
                                              currentNode->gCost + 1,
                                              calculateH(Point(newX, newY), goal),
                                              currentNode);
                openList.push(neighborNode); // Add the neighbor to the open list
                allNodes.push_back(neighborNode); // Keep track of all nodes
            }
        }
    }

    // If no path is found, clean up and return an empty path
    for (Node* node : allNodes) {
        delete node;
    }

    return {};
}
