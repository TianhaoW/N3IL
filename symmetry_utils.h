#pragma once
#include <vector>
#include <utility>

using Point = std::pair<int, int>;

std::vector<std::vector<Point> > generate_D8_transforms(const std::vector<Point>& points, int n);
std::vector<Point> canonical_form(const std::vector<Point>& points, int n);
