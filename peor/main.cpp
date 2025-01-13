#include "montecarlo.h"
#include <chrono>
#include <iostream>

double tm;

__int128_t P(int n, int k) {
    return 0;
}

__int128_t res_polinomio(std::vector<std::vector<bool>>& g, int k) {
    return P(g.size(), k);
}

monteCarlo::resultado res_montecarlo(const std::vector<std::vector<bool>>& g, int k) {
    std::float128_t e = 0.01, z = 2.575;
    monteCarlo mc(z, e, g, k);
    const auto t0 = std::chrono::high_resolution_clock::now();
    monteCarlo::resultado res = mc.intervalo();
    const auto t1 = std::chrono::high_resolution_clock::now();
    tm = std::chrono::duration_cast<std::chrono::duration<double>>(t1 - t0).count();
    return res;
}

void leerMatriz(std::vector<std::vector<bool>>& g) {
    for(int i = 0; i < g.size(); ++i) {
        for(int j = 0; j < g.size(); ++j) {
            int p;
            std::cin >> p;
            g[i][j] = p;
        }
    }
}

bool compara(const __int128_t &poli, const monteCarlo::resultado &monte) {
    std::float128_t err = erel(poli, monte.media);
    if(std::float128_t(poli) >= monte.intervalo.first && std::float128_t(poli) <= monte.intervalo.second) {
        return 1;
    } else {
        return 0;
    }
} 

int main() {
    int n;
    std::cin >> n;
    int veces = 0;
    std::cout << "Vértices\tTiempo\n";
    for(int i = 1; i <= n; ++i) {
        std::vector<std::vector<bool>> g(i, std::vector<bool>(i));
        leerMatriz(g);
        __int128_t resp = res_polinomio(g, i - 1);
        monteCarlo::resultado resm = res_montecarlo(g, i - 1);
        veces += compara(resp, resm);
        std::cout << i << "\t" << tm << "\n";
    } 
    std::cout << "Evaluaciones: " << n << "\n"
        << "Montecarlos correctos: " << veces << "\n";
    return 0;
}