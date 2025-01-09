#pragma once
#include <immintrin.h>
#include <limits>
#include <random>
#include <vector>

class coloración {
    private:
    struct random_rand {
    using result_type = uint64_t;
    uint64_t operator()() {
        uint64_t res;
        while (_rdrand64_step(reinterpret_cast<unsigned long long*>(&res)) == 0) {
            continue;
        }
        return res;
    }
    static constexpr result_type min() {
        return std::numeric_limits<result_type>::min( );
    }
    static constexpr result_type max() {
        return std::numeric_limits<result_type>::max( );
    }
    };

    random_rand gen;

    public:
    std::vector<int> coloraciónAleatoria(int n, int c) {
        std::vector<int> arr(n);
        std::uniform_int_distribution<int> distribución(0, c - 1);
        for(int i = 0; i < n; ++i) {
            arr[i] = distribución(gen);
        }
        return arr;
    }

    bool verificarColoración(const std::vector<std::vector<bool>>& g, const std::vector<int>& colores) {
        for(int i = 0; i < g.size(); ++i) {
            for(int j = i + 1; j < g.size(); ++j) {
                if(g[i][j] && colores[i] == colores[j]) {
                    return false;
                }
            }
        }
        return true;
    }
};