#pragma once
#include "ops128.h"
#include <quadmath.h>
#include <stdfloat>
#include <utility>
#include <vector>

class estadística {
    private:
    std::float128_t z;
    std::float128_t e;
    std::float128_t n;

    std::float128_t desv(const std::vector<std::float128_t>& d, std::float128_t med) {
        std::float128_t res = 0;
        for(int i = 0; i < d.size(); ++i) {
            res += potencia(d[i] - med, 2);
        }
        return sqrtq(res / std::float128_t(d.size() - 1));
    }

    public:
    estadística(std::float128_t z, std::float128_t e, std::float128_t n) {
        this->z = z;
        this->e = e;
        this->n = n;
    }

    std::pair<std::float128_t, std::float128_t> intervalo(const std::vector<std::float128_t>& datos, std::float128_t media) {
        std::float128_t de = desv(datos, media);
        std::float128_t em = 0.05;
        return std::pair<std::float128_t, std::float128_t> (media - media * em, media + media * em);
    }
};