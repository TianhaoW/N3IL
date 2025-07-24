#include "symmetry_utils.h"
#include <algorithm>

static Point apply_transform(const Point& p, int n, int type) {
    int x = p.first, y = p.second;
    switch (type) {
        case 0: return {x, y};
        case 1: return {y, n - 1 - x};
        case 2: return {n - 1 - x, n - 1 - y};
        case 3: return {n - 1 - y, x};
        case 4: return {x, n - 1 - y};
        case 5: return {n - 1 - x, y};
        case 6: return {y, x};
        case 7: return {n - 1 - y, n - 1 - x};
        default: return {x, y}; // should not happen
    }
}

std::vector<std::vector<Point>> generate_D8_transforms(const std::vector<Point>& points, int n) {
    std::vector<std::vector<Point>> result(8);
    for (int i = 0; i < 8; ++i) {
        for (const Point& p : points) {
            result[i].push_back(apply_transform(p, n, i));
        }
        std::sort(result[i].begin(), result[i].end());
    }
    return result;
}

std::vector<Point> canonical_form(const std::vector<Point>& points, int n) {
    auto transforms = generate_D8_transforms(points, n);
    return *std::min_element(transforms.begin(), transforms.end());
}

static Point rotate90(const Point& p, int n) {
    return {p.second, n - 1 - p.first};
}

static Point rotate180(const Point& p, int n) {
    return {n - 1 - p.first, n - 1 - p.second};
}

static Point rotate270(const Point& p, int n) {
    return {n - 1 - p.second, p.first};
}

static Point reflect_x(const Point& p, int n) {
    return {p.first, n - 1 - p.second};
}

static Point reflect_y(const Point& p, int n) {
    return {n - 1 - p.first, p.second};
}

static Point reflect_diag(const Point& p, int n) { // y = x
    return {p.second, p.first};
}

static Point reflect_anti_diag(const Point& p, int n) { // y = -x
    return {n - 1 - p.second, n - 1 - p.first};
}

std::vector<Point> d8_symmetries(const Point& p, int n) {
    std::unordered_set<Point, PointHash> unique;

    unique.insert(p);
    unique.insert(rotate90(p, n));
    unique.insert(rotate180(p, n));
    unique.insert(rotate270(p, n));
    unique.insert(reflect_x(p, n));
    unique.insert(reflect_y(p, n));
    unique.insert(reflect_diag(p, n));
    unique.insert(reflect_anti_diag(p, n));

    return std::vector<Point>(unique.begin(), unique.end());
}

std::vector<Point> rotation_180_symmetry(const Point& p, int n) {
    std::unordered_set<Point, PointHash> unique;
    unique.insert(p);
    unique.insert(rotate180(p, n));
    return std::vector<Point>(unique.begin(), unique.end());
}

std::vector<Point> reflection_x_symmetry(const Point& p, int n) {
    std::unordered_set<Point, PointHash> unique;
    unique.insert(p);
    unique.insert(reflect_x(p, n));
    return std::vector<Point>(unique.begin(), unique.end());
}

std::vector<Point> reflection_y_symmetry(const Point& p, int n) {
    std::unordered_set<Point, PointHash> unique;
    unique.insert(p);
    unique.insert(reflect_y(p, n));
    return std::vector<Point>(unique.begin(), unique.end());
}

std::vector<Point> reflection_xy_symmetry(const Point& p, int n) {
    std::unordered_set<Point, PointHash> unique;
    unique.insert(p);
    unique.insert(reflect_y(p, n));
    unique.insert(reflect_x(p, n));
    unique.insert(rotate180(p, n));
    return std::vector<Point>(unique.begin(), unique.end());
}

std::vector<Point> reflection_diag_symmetry(const Point& p, int n) {
    std::unordered_set<Point, PointHash> unique;
    unique.insert(p);
    unique.insert(reflect_diag(p, n));
    return std::vector<Point>(unique.begin(), unique.end());
}

std::vector<Point> reflection_anti_diag_symmetry(const Point& p, int n) {
    std::unordered_set<Point, PointHash> unique;
    unique.insert(p);
    unique.insert(reflect_anti_diag(p, n));
    return std::vector<Point>(unique.begin(), unique.end());
}

std::vector<Point> rotation_90_symmetry(const Point& p, int n) {
    std::unordered_set<Point, PointHash> unique;
    unique.insert(p);
    unique.insert(rotate90(p, n));
    unique.insert(rotate180(p, n));
    unique.insert(rotate270(p, n));
    return std::vector<Point>(unique.begin(), unique.end());
}