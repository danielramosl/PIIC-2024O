#include <iostream>

void creaCamino(int n) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            std::cout << ((j == (i - 1) || j == (i + 1)) ? '1' : '0') << " ";
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
        creaCamino(i);
    }
}