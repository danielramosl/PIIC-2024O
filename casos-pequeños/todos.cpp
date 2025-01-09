#include <fstream>
#include <iostream>
#include "montecarlo.h"
#include "ops128.h"
#include "polinomio.h"
#include <stdfloat>
#include <time.h>
#include <vector>

double tp, tm;
std::ifstream ent;
std::ofstream sal;

__int128_t res_polinomio(std::vector<std::vector<bool>>& g, int k) {
    polinomio p(g);
    clock_t t0 = clock();
    p.creaPolinomio();
    p.traducePolinomio();
    __int128_t res = p.P(k);
    clock_t t1 = clock();
    sal << "Usando el algoritmo de borrado contraccion:\n" 
            << "P(G, " << k << ") = " << i128to_string(res) << "\n"
            << "Tiempo: " << double(t1 - t0) / CLOCKS_PER_SEC << "\n";
    tp += double(t1 - t0) / CLOCKS_PER_SEC;
    return res;
}

monteCarlo::resultado res_montecarlo(std::vector<std::vector<bool>>& g, int k) {
    std::float128_t e = 0.01, z = 2.575;
    clock_t t0 = clock();
    monteCarlo mc(z, e, g, k);
    monteCarlo::resultado res = mc.intervalo();
    clock_t t1 = clock();
    sal << "Usando el metodo de Montecarlo:\n"
        << "Intervalo de confianza: [" << f128to_string(res.intervalo.first) << ", "
        << f128to_string(res.intervalo.second) << "]\n"
        << "Media: " << f128to_string(res.media) << "\n"
        << "Tiempo: " << double(t1 - t0) / CLOCKS_PER_SEC << "\n";
    tm += double(t1 - t0) / CLOCKS_PER_SEC;
    return res;
}

void guiones() {
    for(int i = 0; i < 20; ++i) {
        sal << "-";
    }
    sal << "\n";
}

void leerMatriz(std::vector<std::vector<bool>>& g) {
    for(int i = 0; i < g.size(); ++i) {
        for(int j = 0; j < g.size(); ++j) {
            int p;
            ent >> p;
            g[i][j] = p;
        }
    }
}

void imprimeMatriz(std::vector<std::vector<bool>>& g) {
    for(int i = 0; i < g.size(); ++i) {
        for(int j = 0; j < g.size(); ++j) {
            sal << "[" << g[i][j] << "]";
        }
        sal << "\n";
    }
}

bool compara(const __int128_t &poli, const monteCarlo::resultado &monte) {
    std::float128_t err = erel(poli, monte.media);
    sal << "Error relativo: " << f128to_string(err) << "\n";
    if(std::float128_t(poli) >= monte.intervalo.first && std::float128_t(poli) <= monte.intervalo.second) {
        sal << "El resultado SI esta dentro del intervalo :)\n";
        return 1;
    } else {
        sal << "El resultado NO esta dentro del intervalo ):\n";
        return 0;
    }
}

int main() {
    for(int u = 1; u <= 12; ++u) {
        tp = 0, tm = 0;
        clock_t t0 = clock();
        std::string sent = "n" + std::to_string(u) + "/ent.txt";
        ent = std::ifstream(sent);
        std::string ssal = "n" + std::to_string(u) + "/sal.txt";
        sal = std::ofstream(ssal);
        int m;
        ent >> m;
        int veces = 0;
        for(int i = 0; i < m; ++i) {
            int n = u;
            std::vector<std::vector<bool>> g(n, std::vector<bool>(n));
            leerMatriz(g);
            guiones();
            imprimeMatriz(g);
            guiones();
            for(int k = 0; k < 5; ++k) {
                __int128_t resp = res_polinomio(g, n + 5 * k);
                monteCarlo::resultado resm = res_montecarlo(g, n + 5 * k);
                veces += compara(resp, resm);
                guiones();
            }
        }
        guiones();
        sal << "Numero de vertices: " << u << "\n";
        sal << "Total de graficas: " << m << "\n";
        sal << "Total de evaluaciones calculadas: " << m * 5 << "\n";
        sal << "Intervalos de evaluaciones correctamente resueltos: " << veces << "\n";
        sal << "Tiempo medio Montecarlo: " << tm / (m * 5) << "\n";
        sal << "Tiempo medio Borrado-Contraccion: " << tp / (m * 5) << "\n";
        clock_t t1 = clock();
        std::cout << "n = " << u << " " << double(t1 - t0) / CLOCKS_PER_SEC << "s :)\n";
    }
}