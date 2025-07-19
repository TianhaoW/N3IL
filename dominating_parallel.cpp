#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <mutex>
#include <thread>

#include "no_three_in_line.h"
#include "symmetry_utils.h"

using Point = std::pair<int, int>;

// ======== Thread-safe global best result ========
std::mutex result_mutex;
std::vector<Point> best_solution;
size_t best_size = std::numeric_limits<size_t>::max();

// ======== Recursive DFS with symmetry pruning ========
void threaded_dfs(NoThreeInLine& env, int n, std::set<std::vector<Point>>& visited) {
    if (env.is_dominating()) {
        std::lock_guard<std::mutex> lock(result_mutex);
        if (env.points().size() < best_size) {
            best_solution = env.points();
            best_size = best_solution.size();
        }
        return;
    }

    auto canon = canonical_form(env.points(), n);
    if (visited.count(canon)) return;
    visited.insert(canon);

    for (const auto& pt : env.get_available_points()) {
        env.add_point(pt.first, pt.second);
        threaded_dfs(env, n, visited);
        env.remove_point();
    }
}

// ======== Parallel DFS launcher ========
void parallel_search(int n) {
    NoThreeInLine base_env(n);
    std::vector<Point> seeds = base_env.get_available_points();
    std::vector<std::thread> threads;

    for (const auto& seed : seeds) {
        threads.emplace_back([n, seed]() {
            NoThreeInLine env(n);
            env.add_point(seed.first, seed.second);
            std::set<std::vector<Point>> visited;
            threaded_dfs(env, n, visited);
        });
    }

    for (auto& t : threads) t.join();
}

// ======== Main ========
int main(int argc, char* argv[]) {
    int n = argc > 1 ? std::atoi(argv[1]) : 5; // Default grid size is 5
    parallel_search(n);

    std::cout << "Grid size: " << n << "\n";
    std::cout << "Smallest independent dominating set (no 3 in line):\n";
    for (const auto& p : best_solution) {
        std::cout << "(" << p.first << ", " << p.second << ")\n";
    }
    std::cout << "Size: " << best_solution.size() << std::endl;
    return 0;
}
