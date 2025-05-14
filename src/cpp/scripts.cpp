#include "../header/scripts.h" 

bool isForbidden(int a, int b) {
    if (a == 0 || a == 127) return true;
    if (a == 169 && b == 254) return true;
    if (a >= 224) return true;
    return false;
}

std::string generate_random_ip() {
    std::srand(std::time(0));
    int a, b, c, d;
    do {
        a = std::rand() % 256;
        b = std::rand() % 256;
    } while (isForbidden(a, b));
    c = std::rand() % 256;
    d = std::rand() % 256;
    return std::to_string(a) + "." + std::to_string(b) + "." + std::to_string(c) + "." + std::to_string(d);
}