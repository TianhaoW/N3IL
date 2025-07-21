#include "no_three_in_line.h"
#include <numeric>
#include <algorithm>
#include <cassert>

NoThreeInLine::NoThreeInLine(int n)
    : n_(n), occupied_(n, std::vector<bool>(n, false)),
      available_(n, std::vector<bool>(n, true)) {}

bool NoThreeInLine::is_available(int x, int y) const {
    return available_[x][y];
}

const std::vector<NoThreeInLine::Point>& NoThreeInLine::points() const {
    return point_set_;
}

std::vector<NoThreeInLine::Point> NoThreeInLine::get_available_points() const {
    std::vector<Point> result;
    for (int x = 0; x < n_; ++x)
        for (int y = 0; y < n_; ++y)
            if (available_[x][y])
                result.emplace_back(x, y);
    return result;
}

bool NoThreeInLine::is_dominating() const {
    for (int x = 0; x < n_; ++x)
        for (int y = 0; y < n_; ++y)
            if (available_[x][y]) return false;
    return true;
}

NoThreeInLine::Slope NoThreeInLine::reduced_slope(const Point& a, const Point& b) const {
    int dx = b.first - a.first;
    int dy = b.second - a.second;
    if (dx == 0 && dy == 0) return {0, 0};
    int g = std::gcd(dx, dy);
    return {dy / g, dx / g};
}

void NoThreeInLine::add_point(int x, int y) {
    Point new_pt{x, y};
    std::vector<std::pair<Point, Slope>> inserted;

    for (const Point& p : point_set_) {
        Slope s = reduced_slope(p, new_pt);
        if (slope_map_[p].count(s)) {
            available_[x][y] = false;
            return;  // invalid point
        }
        slope_map_[p].insert(s);
        inserted.emplace_back(p, s);

        Slope neg{-s.first, -s.second};
        slope_map_[new_pt].insert(neg);
        inserted.emplace_back(new_pt, neg);
    }

    slope_stack_.push(std::move(inserted));
    point_set_.push_back(new_pt);
    occupied_[x][y] = true;
    available_[x][y] = false;

    std::vector<Point> removed;
    mark_unavailable_due_to(x, y, removed);
    removal_stack_.push_back(std::move(removed));
}

void NoThreeInLine::remove_point() {
    if (point_set_.empty()) return;

    Point p = point_set_.back();
    point_set_.pop_back();
    occupied_[p.first][p.second] = false;
    available_[p.first][p.second] = true;

    for (const auto& [pt, s] : slope_stack_.top()) {
        slope_map_[pt].erase(s);
    }
    slope_stack_.pop();

    for (const Point& q: removal_stack_.back()){
        available_[q.first][q.second] = true;
    }

    removal_stack_.pop_back();
}

void NoThreeInLine::mark_unavailable_due_to(int x, int y, std::vector<Point>& removed) {
    const Point new_pt{x, y};
    for (int i = 0; i < n_; ++i) {
        for (int j = 0; j < n_; ++j) {
            // if the point is already blocked, we skip it
            if (!available_[i][j]) continue;
            Point test{i, j};

            for (const Point& existing : point_set_) {
                // if (existing == new_pt) continue;
                //if (reduced_slope(existing, new_pt) == reduced_slope(existing, test) | reduced_slope(new_pt, existing) == reduced_slope(existing, test)) {
                Slope s = reduced_slope(existing, test);
                if (slope_map_[existing].count(s)) {
                    available_[i][j] = false;
                    removed.push_back(test);
                    break;
                }
            }
        }
    }
}
