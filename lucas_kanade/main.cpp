#include "two_dimensional/two_dimensional.h"

int main() {
    std::vector<std::vector<uint8_t>> img1 = {
        {100, 102, 101},
        {98, 100, 99},
        {97, 98, 96}
    };

    std::vector<std::vector<uint8_t>> img2 = {
        {101, 103, 102},
        {99, 101, 100},
        {98, 99, 97}
    };

    int width = img1[0].size();
    int height = img1.size();

    std::vector<std::vector<double>> u(height, std::vector<double>(width));
    std::vector<std::vector<double>> v(height, std::vector<double>(width));

    TDLK tdlk;
    tdlk.find_tdlk(img1, img2, u, v);

    std::cout << "Optical flow (u):" << std::endl;
    for (const auto& row : u) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Optical flow (v):" << std::endl;
    for (const auto& row : v) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
