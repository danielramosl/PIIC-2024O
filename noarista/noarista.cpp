#include <iostream>
#include <vector>

void creaGráfica(int n) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            std::cout << "0 ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    int n;
    std::cin >> n;
    std::cout << n << "\n\n";
    for(int i = 0; i < n; ++i) {
        creaGráfica(i + 1);
    }
    return 0;
}