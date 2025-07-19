#include "no_three_in_line.h"

NoThreeInLine::NoThreeInLine(int n)
    : n_(n), occupied_(n, std::vector<bool>(n, false)),
      available_(n, std::vector<bool>(n, true)) {}

int NoThreeInLine::grid_size() const {
    return n_;
}

bool NoThreeInLine::is_available(int x, int y) const {
    return available_[x][y];
}

void NoThreeInLine::add_point(int x, int y) {
    Point p{x, y};
    point_set_.push_back(p);
    occupied_[x][y] = true;
    available_[x][y] = false;

    std::vector<Point> removed;
    update_available(p, removed);
    removal_stack_.push_back(std::move(removed));
}

void NoThreeInLine::remove_point() {
    if (point_set_.empty()) return;
    Point p = point_set_.back();
    point_set_.pop_back();

    occupied_[p.first][p.second] = false;
    available_[p.first][p.second] = true;

    for (const Point& q : removal_stack_.back()) {
        available_[q.first][q.second] = true;
    }
    removal_stack_.pop_back();
}

bool NoThreeInLine::is_collinear(const Point& a, const Point& b, const Point& c) const {
    return (b.first - a.first) * (c.second - a.second)
         == (c.first - a.first) * (b.second - a.second);
}

void NoThreeInLine::update_available(const Point& new_point, std::vector<Point>& removed) {
    for (int x = 0; x < n_; ++x) {
        for (int y = 0; y < n_; ++y) {
            if (!available_[x][y]) continue;
            Point test{x, y};
            for (const Point& existing : point_set_) {
                if (existing == new_point) continue; // skip the new point itself

                if (is_collinear(existing, new_point, test)) {
                    if (available_[x][y]) {
                        available_[x][y] = false;
                        removed.push_back(test);
                        break;  // no need to test further
                    }

                }
            }
        }
    }
}

const std::vector<NoThreeInLine::Point>& NoThreeInLine::points() const {
    return point_set_;
}

std::vector<NoThreeInLine::Point> NoThreeInLine::get_available_points() const {
    std::vector<Point> result;
    for (int x = 0; x < n_; ++x) {
        for (int y = 0; y < n_; ++y) {
            if (available_[x][y]) {
                result.emplace_back(x, y);
            }
        }
    }
    return result;
}

bool NoThreeInLine::is_dominating() const {
    for (int x = 0; x < n_; ++x) {
        for (int y = 0; y < n_; ++y) {
            if (available_[x][y]) return false;
        }
    }
    return true;
}
