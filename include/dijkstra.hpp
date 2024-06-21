#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "IPathfinder.hpp"


class Dijkstra : public IPathfinder {
public:
    explicit Dijkstra(const Grid& grid);
    std::vector<Grid::Point> findPath(const Grid::Point& start, const Grid::Point& goal) const override;

private:
    const Grid& _grid;  // Reference to the grid to use
    std::vector<Grid::Point> reconstruct_path(Grid::Point start, Grid::Point goal, std::map<Grid::Point, Grid::Point>& came_from) const;
};

#endif // DIJKSTRA_HPP
