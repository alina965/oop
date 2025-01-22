#include "randompopulator.h"
#include <ctime>
#include <cstdlib>

bool RandomPopulator::Populate(std::vector<std::pair<int, int>>& alive_cells,
              std::unordered_set<int>& birth_rules,
              std::unordered_set<int>& survival_rules) {
    // правила по умолчанию: B3/S23
    birth_rules = {3};
    survival_rules = {2, 3};

    std::srand(std::time(nullptr)); // используем текущее время в качестве начального значения для генератора случайных чисел

    // размер по умолчанию: 20x20
    for (int row = 0; row < 20; ++row) {
        for (int col = 0; col < 20; ++col) {
            if (std::rand() % 2 == 0) {
                alive_cells.emplace_back(row, col);
            }
        }
    }

    return true;
}
