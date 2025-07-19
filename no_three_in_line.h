#pragma once

#include <vector>
#include <utility>

class NoThreeInLine {
public:
    using Point = std::pair<int, int>;

    explicit NoThreeInLine(int n);

    void add_point(int x, int y);
    void remove_point();

    bool is_available(int x, int y) const;
    bool is_dominating() const;

    const std::vector<Point>& points() const;
    std::vector<Point> get_available_points() const;

    int grid_size() const;

private:
    int n_;
    std::vector<std::vector<bool> > occupied_;
    std::vector<std::vector<bool> > available_;
    std::vector<Point> point_set_;
    std::vector<std::vector<Point> > removal_stack_;

    bool is_collinear(const Point& a, const Point& b, const Point& c) const;
    void update_available(const Point& new_point, std::vector<Point>& removed);
};
