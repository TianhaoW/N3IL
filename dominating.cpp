#include "no_three_in_line.h"
#include "symmetry_utils.h"
#include <set>
#include <limits>
#include <iostream>

void find_smallest_independent_dominating_set(int n, std::vector<NoThreeInLine::Point>& best_solution) {
    NoThreeInLine env(n);
    std::set<std::vector<NoThreeInLine::Point> > visited;
    std::vector<NoThreeInLine::Point> current_best;
    size_t best_size = std::numeric_limits<size_t>::max();

    std::function<void()> dfs = [&]() {
        if (env.is_dominating()) {
            const auto& pts = env.points();
            if (pts.size() < best_size) {
                best_solution = pts;
                best_size = pts.size();
            }
            return;
        }

        auto canon = canonical_form(env.points(), n);
        if (visited.count(canon)) return;
        visited.insert(canon);

        for (const auto& pt : env.get_available_points()) {
            env.add_point(pt.first, pt.second);
            dfs();
            env.remove_point();
        }
    };

    dfs();
}

int main(int argc, char* argv[]) {
    int n = argc > 1 ? std::atoi(argv[1]) : 5; // Default grid size is 5

    // Uncomment the following lines to test NoThreeInLine functionality
    // NoThreeInLine env(n);
    // env.add_point(0, 0);
    // env.add_point(1, 1);
    // std::cout << env.get_available_points().size() << std::endl; // Should print 1 (true)

    std::vector<std::pair<int, int> > result;
    find_smallest_independent_dominating_set(n, result);

    std::cout << "Grid size: " << n << "\n";
    std::cout << "Smallest independent dominating set:\n";
    for (const auto& [x, y] : result) {
        std::cout << "(" << x << ", " << y << ")\n";
    }
    std::cout << "Size: " << result.size() << "\n";
}