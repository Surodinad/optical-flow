#include <img_lib.h>
#include "one_dimensional/one_dimensional.h"

#include <bitset>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <utility>

void run_fiction_one_dimensional() {
    fiction_rgb fill{static_cast<std::byte>(0),
                    static_cast<std::byte>(0),
                    static_cast<std::byte>(0)};

    fiction_img first_img(20, 1, fill);
    fiction_img second_img(20, 1, fill);

    for (size_t d = 13, i = 2, c = 1; i < 13; ++i, ++c) {
        size_t dc = d * c;
        first_img.pixels[i].r = static_cast<std::byte>(static_cast<size_t>(first_img.pixels[i].r) - dc);
        first_img.pixels[i].g = static_cast<std::byte>(static_cast<size_t>(first_img.pixels[i].g) - dc);
        first_img.pixels[i].b = static_cast<std::byte>(static_cast<size_t>(first_img.pixels[i].b) - dc);

        std::cout << "lum=" << first_img.pixels[i].lum() << std::endl;
    }

    for (size_t d = 13, i = 7, c = 1; i < 18; ++i, ++c) {
        size_t dc = d * c;
        second_img.pixels[i].r = static_cast<std::byte>(static_cast<size_t>(second_img.pixels[i].r) - dc);
        second_img.pixels[i].g = static_cast<std::byte>(static_cast<size_t>(second_img.pixels[i].g) - dc);
        second_img.pixels[i].b = static_cast<std::byte>(static_cast<size_t>(second_img.pixels[i].b) - dc);
    }

    
}

int main() {
    run_fiction_one_dimensional();
    return 0;
}
