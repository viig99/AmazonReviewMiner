import AdvancedMath;
#include <iostream>
#include "spdlog/spdlog.h"

int main() {
    spdlog::info("Hello, World!");
    spdlog::info("5 + 3 = {}", AdvancedMath::add(5, 3));
    spdlog::info("5 - 3 = {}", AdvancedMath::sub(5, 3));
    return 0;
}
