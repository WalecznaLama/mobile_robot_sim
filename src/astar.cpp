#include "astar.hpp"

AStar::AStar(const Grid& grid) : _grid(grid) {}

double AStar::calculateH(const Grid::Point &current_point, const Grid::Point &goal) const {
    return std::hypot(goal.x - current_point.x, goal.y - current_point.y); // Using Euclidean distance for diagonal compatibility
}

std::vector<Grid::Point> AStar::findPath(const Grid::Point& start, const Grid::Point& goal) const {
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, CompareNode> openList;
    bool visited[_grid.getRows()][_grid.getCols()] = {};
    visited[start.x][start.y] = true;

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

        for (auto& direction : _grid.move_directions) {
            Grid::Point newCell(currentNode->point.x + direction.x, currentNode->point.y + direction.y);
            if (_grid.isWalkable(newCell, direction.x, direction.y) && !visited[newCell.x][newCell.y]) {
                visited[newCell.x][newCell.y] = true;
                double moveCost = _grid.cost(direction);
                auto neighborNode = std::make_shared<Node>(newCell,
                                                           currentNode->gCost + moveCost,
                                                           calculateH(newCell, goal),
                                                           currentNode);
                openList.push(neighborNode);
            }
        }
    }

    return {};  // Return an empty path if no path is found
}
