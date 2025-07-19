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
