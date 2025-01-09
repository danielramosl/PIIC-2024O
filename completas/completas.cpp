#include <iostream>

void creaCompleta(int n) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            std::cout << ((i != j) ? '1' : '0') << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    int n;
    std::cin >> n;
    std::cout << n << "\n\n";
    for(int i = 1; i <= n; ++i) {
        creaCompleta(i);
    }
}