#pragma once
#include <vector>
#include <utility>
#include <unordered_set>
#include "no_three_in_line.h"

using Point = std::pair<int, int>;

std::vector<std::vector<Point> > generate_D8_transforms(const std::vector<Point>& points, int n);
std::vector<Point> canonical_form(const std::vector<Point>& points, int n);


// The following function are used to generate the full orbits of points 

// Generate full D8 orbit of a point
std::vector<Point> d8_symmetries(const Point& p, int n);
// Specific subgroups
std::vector<Point> rotation_180_symmetry(const Point& p, int n);
std::vector<Point> reflection_x_symmetry(const Point& p, int n);
std::vector<Point> reflection_y_symmetry(const Point& p, int n);
std::vector<Point> reflection_xy_symmetry(const Point& p, int n);
std::vector<Point> reflection_diag_symmetry(const Point& p, int n);
std::vector<Point> reflection_anti_diag_symmetry(const Point& p, int n);
std::vector<Point> rotation_90_symmetry(const Point& p, int n);
