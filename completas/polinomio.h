#include "ops128.h"
#include <string>
#include <vector>

class polinomio {
    private:
    struct arista {
        int u;
        int v;
    };
    std::string sPolinomio;
    std::vector<std::vector<bool>> g;
    std::vector<int> fun;

    bool no_arista(const std::vector<std::vector<bool>>& mat) {
        for(int i = 0; i < mat.size(); ++i) {
            for(int j = i + 1; j < mat.size(); ++j) {
                if(mat[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    arista primer_arista(const std::vector<std::vector<bool>>& mat) {
        for(int i = 0; i < mat.size(); ++i) {
            for(int j = i + 1; j < mat.size(); ++j) {
                if(mat[i][j] == 1) {
                    return arista {i, j};
                }
            }
        }
        return arista {0,0};
    }

    std::vector<std::vector<bool>> borrado(std::vector<std::vector<bool>> mat, arista arista) {
        mat[arista.u][arista.v] = 0; mat[arista.v][arista.u] = 0;
        return mat;
    }

    std::vector<std::vector<bool>> contracción(const std::vector<std::vector<bool>>& mat, arista arista) {
        std::vector<std::vector<bool>> res;
        for(int i = 0; i < mat.size(); ++i) {
            if(i == arista.u || i == arista.v) {
                continue;
            }
            std::vector<bool> arr;
            for(int j = 0; j < mat.size(); ++j) {
                if(j != arista.u && j != arista.v) {
                    arr.push_back(mat[i][j]);
                }
            }
            res.push_back(arr);
        }

        int ini = 0;
        for(int i = 0; i < mat.size(); ++i) {
            if(i != arista.u && i != arista.v) {
                res[ini++].push_back(mat[i][arista.u] | mat[i][arista.v]);
            }
        }

        res.push_back(std::vector<bool>());
        int size = res.size() - 1;
        for(int j = 0; j < mat.size(); ++j) {
            if(j != arista.u && j != arista.v) {
                res[size].push_back(mat[arista.u][j] | mat[arista.v][j]);
            }
        }
        res[size].push_back(0);
        return res;
    }

    std::string cromático(const std::vector<std::vector<bool>>& mat) {
        if(no_arista(mat)) {
            return "x" + std::to_string(mat.size());
        } else {
            arista arista = primer_arista(mat);
            return cromático(borrado(mat, arista)) + "-(" + cromático(contracción(mat, arista)) + ")";
        }
    }

    std::vector<int> traductor(int n, std::string fun) {
        std::vector<int> res(n + 1, 0);
        int signo = 1;
        std::vector<int> ant;
        for(int i = 0; i < fun.size(); ++i) {
            if(fun[i] == 'x') {
                std::string num = "";
                while(std::isdigit(fun[i + 1])) {
                    num += fun[i + 1];
                    ++i;
                }
                res[std::stoi(num)] += signo;
            } else if(fun[i] == '-') {
                ant.push_back(-1);
                signo *= -1;
                ++i;
            } else if(fun[i] == ')') {
                signo *= ant.back(); ant.pop_back();
            }
        }
        return res;
    }

    __int128_t evaluación(const std::vector<int>& f, int k) {
        __int128_t res = 0;
        for(int i = 0; i < f.size(); ++i) {
            res += f[i] * potencia(k, i);
        }
        return res;
    }

    public:
    polinomio(const std::vector<std::vector<bool>>& g) {
        this->g = g;
    }
    
    void creaPolinomio() {
        sPolinomio = cromático(g);
    }

    void traducePolinomio() {
        fun = traductor(g.size(), sPolinomio);
    }

    __int128_t P(int k) {
        return evaluación(fun, k);
    }
};