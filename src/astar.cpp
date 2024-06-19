#include "astar.hpp"

AStar::AStar(const Grid& grid) : _grid(grid) {}

bool AStar::isValid(int x, int y) {
    // Check boundaries and obstacle status
    return x >= 0 && x < _grid.getRows() && y >= 0 && y < _grid.getCols() && _grid.getGrid()[x][y] == 0;
}

double AStar::calculateH(const Grid::Point &current_point, const Grid::Point &goal) {
    // Heuristic using Manhattan distance calculation
    return std::abs(current_point.x - goal.x) + std::abs(current_point.y - goal.y);
}

std::vector<Grid::Point> AStar::findPath(int startX, int startY, int goalX, int goalY) {
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, CompareNode> openList;
    bool visited[_grid.getRows()][_grid.getCols()] = {false};
    visited[startX][startY] = true;

    Grid::Point start(startX, startY);
    Grid::Point goal(goalX, goalY);
    auto startNode = std::make_shared<Node>(start, 0, calculateH(start, goal), nullptr);
    openList.push(startNode);

    while (!openList.empty()) {
        auto currentNode = openList.top();
        openList.pop();

        if (currentNode->point == goal) {
            std::vector<Grid::Point> path;
            for (auto pathNode = currentNode; pathNode != nullptr; pathNode = pathNode->parent) {
                path.push_back(pathNode->point);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (auto& direction : _directions) {
            int newX = currentNode->point.x + direction.x;
            int newY = currentNode->point.y + direction.y;
            if (isValid(newX, newY) && !visited[newX][newY]) {
                visited[newX][newY] = true;
                auto neighborNode = std::make_shared<Node>(Grid::Point(newX, newY), currentNode->gCost + 1, calculateH(Grid::Point(newX, newY), goal), currentNode);
                openList.push(neighborNode);
            }
        }
    }

    return {};  // Return an empty path if no path is found
}
