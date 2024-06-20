#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "IPathfinder.hpp"
#include <map>

class Dijkstra : public IPathfinder {
public:
    explicit Dijkstra(const Grid& grid);
    std::vector<Grid::Point> findPath(int startX, int startY, int goalX, int goalY) const override;

private:
    const Grid& _grid;  // Reference to the grid to use
    std::vector<Grid::Point> reconstruct_path(Grid::Point start, Grid::Point goal, std::map<Grid::Point, Grid::Point>& came_from) const;
};

#endif // DIJKSTRA_HPP
