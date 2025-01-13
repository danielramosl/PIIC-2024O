#pragma once
#include <algorithm>
#include <stdfloat>
#include <string>

std::float128_t potencia(std::float128_t x, int n) {
    std::float128_t res = 1;
    for(int i = 0; i < n; ++i) {
        res *= x;
    }
    return res;
}

__int128_t potencia(int x, int n) {
    __int128_t res = 1;
    for(int i = 0; i < n; ++i) {
        res *= x;
    }
    return res;
}

std::float128_t absoluto(std::float128_t n) {
    return (n > 0) ? n : -n;
}

std::float128_t erel(std::float128_t exc, std::float128_t sim) {
    return absoluto(exc - sim) / exc;
}

std::string i128to_string(__uint128_t n) {
    if (n == 0) return "0";
    std::string res;
    while (n > 0) {
        res.push_back('0' + (n % 10));
        n /= 10;
    }
    std::reverse(res.begin(), res.end());
    return res;
}

std::string f128to_string(std::float128_t n) {
    char res[200];
    quadmath_snprintf(res, sizeof res, "%Qf", n);
    return res;
}