#ifndef IPATHFINDER_HPP
#define IPATHFINDER_HPP

#include "grid.hpp"
#include <vector>
#include <memory>

class IPathfinder {
public:
    virtual ~IPathfinder() {}

    virtual std::vector<Grid::Point> findPath(const Grid::Point& start, const Grid::Point& goal) const = 0;
};

#endif // IPATHFINDER_HPP
