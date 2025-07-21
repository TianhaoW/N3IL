#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <stack>
#include <utility>

struct PointHash {
    std::size_t operator()(const std::pair<int, int>& p) const noexcept {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

class NoThreeInLine {
public:
    using Point = std::pair<int, int>;
    using Slope = std::pair<int, int>;

    explicit NoThreeInLine(int n);

    void add_point(int x, int y);
    void remove_point();
    bool is_dominating() const;
    const std::vector<Point>& points() const;
    std::vector<Point> get_available_points() const;
    bool is_available(int x, int y) const;

private:
    int n_;
    std::vector<std::vector<bool>> occupied_;
    std::vector<std::vector<bool>> available_;
    std::vector<Point> point_set_;

    std::unordered_map<Point, std::set<Slope>, PointHash> slope_map_;
    std::stack<std::vector<std::pair<Point, Slope>>> slope_stack_;
    std::vector<std::vector<Point> > removal_stack_;

    void mark_unavailable_due_to(int x, int y, std::vector<Point>& removed);
    Slope reduced_slope(const Point& a, const Point& b) const;
};
