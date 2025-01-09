#include "montecarlo.h"
#include <chrono>
#include <iostream>

int tm;

__int128_t P(int n, int k) {
    __int128_t res = 1;
    for(int i = 0; i < n; ++i) {
        res *= __int128_t(k - i);
    }
    return res;
}

__int128_t res_polinomio(std::vector<std::vector<bool>>& g, int k) {
    __int128_t res = P(g.size(), k);
    clock_t t1 = clock();
    std::cout << "P(G, " << k << ") = " << i128to_string(res) << "\n";
    return res;
}

monteCarlo::resultado res_montecarlo(std::vector<std::vector<bool>>& g, int k) {
    std::float128_t e = 0.01, z = 2.575;
    const auto t0 = std::chrono::high_resolution_clock::now();
    monteCarlo mc(z, e, g, k);
    monteCarlo::resultado res = mc.intervalo();
    const auto t1 = std::chrono::high_resolution_clock::now();
    double tiempo = std::chrono::duration_cast<std::chrono::duration<double>>(t1 - t0).count();
    std::cout << "Usando el metodo de Montecarlo:\n"
        << "Intervalo de confianza: [" << f128to_string(res.intervalo.first) << ", "
        << f128to_string(res.intervalo.second) << "]\n"
        << "Media: " << f128to_string(res.media) << "\n"
        << "Tiempo: " << tiempo << "\n";
    tm += tiempo;
    return res;
}

void guiones() {
    for(int i = 0; i < 20; ++i) {
        std::cout << "-";
    }
    std::cout << "\n";
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
    std::cout << "Error relativo: " << f128to_string(err) << "\n";
    if(std::float128_t(poli) >= monte.intervalo.first && std::float128_t(poli) <= monte.intervalo.second) {
        std::cout << "El resultado SI esta dentro del intervalo :)\n";
        return 1;
    } else {
        std::cout << "El resultado NO esta dentro del intervalo ):\n";
        return 0;
    }
}

void imprimeMatriz(std::vector<std::vector<bool>>& g) {
    for(int i = 0; i < g.size(); ++i) {
        for(int j = 0; j < g.size(); ++j) {
            std::cout << "[" << g[i][j] << "]";
        }
        std::cout << "\n";
    }
}

int main() {
    int n;
    std::cin >> n;
    int veces = 0;
    for(int i = 1; i <= n; ++i) {
        std::vector<std::vector<bool>> g(i, std::vector<bool>(i));
        leerMatriz(g);
        guiones();
        imprimeMatriz(g);
        guiones();
        for(int j = 1; j <= 5; ++j) {
            __int128_t resp = res_polinomio(g, 2 * i + 5 * j);
            monteCarlo::resultado resm = res_montecarlo(g, 2 * i + 5 * j);
            veces += compara(resp, resm);
            guiones();
        }
    }
    std::cout << "Evaluaciones: " << n * 5 << "\n"
        << "Montecarlos correctos: " << veces << "\n";
    return 0;
}