#include <immintrin.h>
#include <iostream>
#include <random>

struct random_rand {
    using result_type = uint64_t;
    uint64_t operator()() {
        uint64_t res;
        while (_rdrand64_step(&res) == 0) {
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

void creamatriz(int n) {
    int mat[n][n] = {};
    random_rand gen;
    std::uniform_int_distribution<int> distribución(0, 1);
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            mat[i][j] = distribución(gen);
            mat[j][i] = mat[i][j];
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    int n = 12;
    std::cin >> n;
    std::cout << 50 << "\n\n";
    for(int i = 0; i < 100; ++i) {
        creamatriz(n);
    }
