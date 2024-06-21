#include "gui.hpp"

Gui::Gui(int n_rows, int n_cols, int cellSize) : _n_rows(n_rows), _n_cols(n_cols), _cellSize(cellSize) {}

void Gui::drawGrid(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i <= _n_rows; ++i) {
        SDL_RenderDrawLine(renderer, 0, i * _cellSize, _n_rows * _cellSize, i * _cellSize);
    }
    for (int i = 0; i <= _n_cols; ++i) {
        SDL_RenderDrawLine(renderer, i * _cellSize, 0, i * _cellSize, _n_cols * _cellSize);
    }
}

void Gui::drawRobot(SDL_Renderer* renderer, const std::vector<Grid::Point>& points) {
    // Map to track all robots at each position
    std::map<std::pair<int, int>, std::vector<int>> position_map;

    // Populate the map with index of robots at each position
    for (size_t i = 0; i < points.size(); ++i) {
        position_map[{points[i].x, points[i].y}].push_back(i);
    }

    // Draw each robot position
    for (const auto& entry : position_map) {
        auto& pos = entry.first; // The grid position (x, y)
        const auto& indexes = entry.second; // Vector of robot indexes at this position

        // Calculate stripe width
        int stripe_width = _cellSize / indexes.size();

        // Draw stripes for each robot at this position
        for (size_t j = 0; j < indexes.size(); ++j) {
            SDL_SetRenderDrawColor(renderer,
                                   _draw_colors[indexes[j] % _draw_colors.size()].r,
                                   _draw_colors[indexes[j] % _draw_colors.size()].g,
                                   _draw_colors[indexes[j] % _draw_colors.size()].b,
                                   SDL_ALPHA_OPAQUE);
            for (int stripe = j * stripe_width; stripe < _cellSize; stripe += indexes.size() * stripe_width) {
                SDL_Rect rect = {pos.second * _cellSize + stripe, pos.first * _cellSize, stripe_width, _cellSize};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void Gui::drawObstacles(SDL_Renderer* renderer, const std::vector<std::vector<int>>& grid) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < _n_rows; ++i) {
        for (int j = 0; j < _n_cols; ++j) {
            if (grid[i][j] == 1) {
                SDL_Rect rect = {j * _cellSize, i * _cellSize, _cellSize, _cellSize};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void Gui::drawPath(SDL_Renderer* renderer, const std::vector<std::vector<Grid::Point>>& paths) {
    std::map<Grid::Point, std::vector<int>> pathPointsMap;
    int dot_size = _cellSize / 3;

    // Map each point to the paths that include it
    for (size_t i = 0; i < paths.size(); ++i) {
        for (const auto& point : paths[i]) {
            pathPointsMap[point].push_back(i);
        }
    }

    // Draw paths, adjusting for overlaps
    for (const auto& entry : pathPointsMap) {
        const auto& point = entry.first; // The grid point
        const auto& indexes = entry.second; // Vector of path indexes at this point

        if (indexes.size() > 1) { // Multiple paths at this point
            int slice_width = dot_size / indexes.size(); // Adjust the dot size based on overlap
            for (int j = 0; j < indexes.size(); ++j) {
                SDL_SetRenderDrawColor(renderer,
                                       _draw_colors[indexes[j] % _draw_colors.size()].r,
                                       _draw_colors[indexes[j] % _draw_colors.size()].g,
                                       _draw_colors[indexes[j] % _draw_colors.size()].b,
                                       SDL_ALPHA_OPAQUE);
                SDL_Rect rect = {(point.y * _cellSize) + _cellSize / 2 - dot_size / 2 + slice_width * j,
                                 (point.x * _cellSize) + _cellSize / 2 - dot_size / 2,
                                 slice_width, // width adjusted for overlap
                                 dot_size};
                SDL_RenderFillRect(renderer, &rect);
            }
        } else { // Single path at this point
            SDL_SetRenderDrawColor(renderer,
                                   _draw_colors[indexes[0] % _draw_colors.size()].r,
                                   _draw_colors[indexes[0] % _draw_colors.size()].g,
                                   _draw_colors[indexes[0] % _draw_colors.size()].b,
                                   SDL_ALPHA_OPAQUE);
            SDL_Rect rect = {(point.y * _cellSize) + _cellSize / 2 - dot_size / 2,
                             (point.x * _cellSize) + _cellSize / 2 - dot_size / 2,
                             dot_size, dot_size};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
