#pragma once
#include <atomic>
#include <quadmath.h>
#include <thread>
#include <stdfloat>
#include <utility>
#include <vector>
#include "coloración.h"
#include "estadística.h"
#include "ops128.h"

class monteCarlo {
    private:
    std::float128_t z;
    std::float128_t e;
    std::vector<std::vector<bool>> g;
    int c;
    coloración col;
    std::float128_t media;

    public:
    monteCarlo(std::float128_t z, std::float128_t e, const std::vector<std::vector<bool>>& g, int c) {
        this->z = z;
        this->e = e;
        this->g = g;
        this->c = c;
    }

    private:
    void simulación(int bloqueTam, std::atomic<int>& validas) {
        for (int i = 0; i < bloqueTam; ++i) {
            std::vector<int> coloración = col.coloraciónAleatoria(g.size(), c);
            if (col.verificarColoración(g, coloración)) {
                ++validas;
            }
        }
    }

    std::float128_t montecarlo() {
        std::float128_t p = 0.5;
        std::float128_t ep = 1;
        std::float128_t factor = 1;
        do {
            __int128_t n = factor * (potencia(z, 2) * p * (1 - p)) / (potencia(e, 2));
            std::atomic<int> validas(0);
            int nhilos = std::thread::hardware_concurrency() - 1;
            int tam = n / nhilos;
            int resto = n % nhilos;
            std::vector<std::thread> hilos;
            for (int i = 0; i < nhilos; ++i) {
                int bloqueTam = tam + (i == nhilos - 1 ? resto : 0);
                hilos.emplace_back(&monteCarlo::simulación, this, bloqueTam, std::ref(validas));
            }
            for (auto& hilo : hilos) {
                hilo.join();
            }
            std::float128_t pact = std::float128_t(validas) / std::float128_t(n);
            if (pact == 0) {
                if(potencia(c, g.size()) < n) {
                    return 0;
                }
                factor *= 2;
                continue;
            }
            p = pact;
            ep = sqrtq(p * (1 - p) / n);
            if (ep > e) {
                factor *= (1 + (ep - e) / e);
            }
        } while (ep > e);
        return p * potencia(c, g.size());
    }

    std::vector<std::float128_t> mediamc() {
        media = montecarlo();
        std::float128_t cabs, crel;
        int i = 1;
        std::vector<std::float128_t> datos = {media};
        do {
            std::float128_t actual = montecarlo();
            std::float128_t manterior = media / std::float128_t(i++);
            media += actual;
            datos.push_back(actual);
            cabs = absoluto(media / std::float128_t(i) - manterior);
            crel = cabs / manterior;
        } while(cabs > e && crel > e);
        media /= std::float128_t(i);
        return datos;
    }
    
    public:
    struct resultado {
        std::pair<std::float128_t, std::float128_t> intervalo;
        std::float128_t media;
    };

    resultado intervalo() {
        estadística est(z, e, std::float128_t(g.size()));
        std::vector<std::float128_t> d = mediamc();
        return {est.intervalo(d, media), media};
    }
};