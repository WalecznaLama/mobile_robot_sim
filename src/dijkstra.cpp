#include "dijkstra.hpp"
#include <queue>
#include <limits>
#include <algorithm>

Dijkstra::Dijkstra(const Grid& grid) : _grid(grid) {}

std::vector<Grid::Point> Dijkstra::findPath(int startX, int startY, int goalX, int goalY) const {
    Grid::Point start(startX, startY);
    Grid::Point goal(goalX, goalY);

    auto cmp = [](const std::pair<Grid::Point, double>& left, const std::pair<Grid::Point, double>& right) {
        return left.second > right.second;
    };
    std::priority_queue<std::pair<Grid::Point, double>, std::vector<std::pair<Grid::Point, double>>, decltype(cmp)> frontier(cmp);

    std::map<Grid::Point, double> cost_so_far;
    std::map<Grid::Point, Grid::Point> came_from;

    frontier.emplace(start, 0.0);
    cost_so_far[start] = 0.0;
    came_from[start] = start;

    while (!frontier.empty()) {
        auto current = frontier.top().first;
        frontier.pop();

        if (current == goal) {
            break;
        }

        for (const auto& next : _grid.getNeighbors(current)) {
            double new_cost = cost_so_far[current] + _grid.cost(current-next);
            if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                frontier.emplace(next, new_cost);
                came_from[next] = current;
            }
        }
    }

    return reconstruct_path(start, goal, came_from);
}

std::vector<Grid::Point> Dijkstra::reconstruct_path(Grid::Point start, Grid::Point goal, std::map<Grid::Point, Grid::Point>& came_from) const {
    std::vector<Grid::Point> path;
    Grid::Point current = goal;

    while (current != start) {
        path.push_back(current);
        current = came_from[current];
    }
    path.push_back(start);

    std::reverse(path.begin(), path.end());
    return path;
}
