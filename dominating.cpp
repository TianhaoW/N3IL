#include "no_three_in_line.h"
#include "symmetry_utils.h"
#include <set>
#include <limits>
#include <iostream>
#include <functional>

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
                std::cout << "updating the best to " << best_size << std::endl;
            }
            return;
        }

        if (env.points().size() >= best_size) return; //pruning

        auto canon = canonical_form(env.points(), n);
        if (visited.count(canon)) return;
        visited.insert(canon);

        if (visited.size() % 100000 == 0){
            std::cout << visited.size() << " cases checked." << std::endl;
        } 

        for (const auto& pt : env.get_available_points()) {
            env.add_point(pt.first, pt.second);
            dfs();
            env.remove_point();
        }
    };

    dfs();
}

void find_largest_set(int n, std::vector<NoThreeInLine::Point>& best_solution) {
    NoThreeInLine env(n);
    std::set<std::vector<NoThreeInLine::Point> > visited;
    std::vector<NoThreeInLine::Point> current_best;
    size_t best_size = std::numeric_limits<size_t>::min();

    std::function<void()> dfs = [&]() {
        if (env.is_dominating()) {
            const auto& pts = env.points();
            if (pts.size() > best_size) {
                best_solution = pts;
                best_size = pts.size();
                std::cout << "updating the best to " << best_size << std::endl;
            }
            return;
        }

        if (env.points().size() + env.get_available_points().size() <= best_size) return; //pruning

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

void debug();

int main(int argc, char* argv[]) {
    // debug();

    int n = argc > 1 ? std::atoi(argv[1]) : 5; // Default grid size is 5
    int largest = argc > 2 ? std::atoi(argv[2]): 0; //Default to find smallest

    std::cout << "Grid size: " << n << "\n";
    std::vector<std::pair<int, int> > result;

    if (largest){
        std::cout << "Finding largest point set now" << std::endl;
        find_largest_set(n, result);
    }
    else {
        std::cout << "Finding smallest point set now" << std::endl;
        find_smallest_independent_dominating_set(n, result);
    }

    std::cout << "Found point set:\n";
    for (const auto& [x, y] : result) {
        std::cout << "(" << x << ", " << y << ")\n";
    }
    std::cout << "Size: " << result.size() << "\n";
}

void debug(){
    NoThreeInLine env(5);
    while (true){
        int x, y;
        std::cout << "Please enter the coordinates: ";
        std::cin >> x >> y;
        if (x==-1){
            env.remove_point();

            std::cout << "Current points: ";
            for (const auto& [x, y] : env.points()) {
                std::cout << "(" << x << ", " << y << "), ";
            }
            std::cout << std::endl;

            std::cout << "Available points: ";
            for (const auto& [x, y] : env.get_available_points()) {
                std::cout << "(" << x << ", " << y << "), ";
            }
            std::cout << std::endl;
        }
        else {
            env.add_point(x, y);

            std::cout << "Current points: ";
            for (const auto& [x, y] : env.points()) {
                std::cout << "(" << x << ", " << y << "), ";
            }
            std::cout << std::endl;

            std::cout << "Available points: ";
            for (const auto& [x, y] : env.get_available_points()) {
                std::cout << "(" << x << ", " << y << "), ";
            }
            std::cout << std::endl;
        }
    }
}