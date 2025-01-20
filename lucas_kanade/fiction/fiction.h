#pragma once

#include <iostream>
#include <cstddef>
#include <vector>

struct fiction_rgb {
    size_t lum() const;

    std::byte r, g, b;
};

class fiction_img {
public:
    fiction_img() = default;

    fiction_img(size_t w, size_t h, fiction_rgb fill);

    fiction_rgb get_pixel(size_t x, size_t y) const;

    fiction_rgb& get_pixel(size_t x, size_t y);

    fiction_rgb* get_line(size_t y);

    const fiction_rgb* get_line(size_t y) const;

    size_t get_width() const;
    size_t get_height() const;

    size_t width;
    size_t height;

    std::vector<fiction_rgb> pixels;
};

// TODO element access
class fiction_lum_matrix {
public:
    fiction_lum_matrix(size_t x_sz, size_t y_sz, std::initializer_list<uint8_t>);

private:
    size_t x_size_;
    size_t y_size_;
    std::vector<std::vector<uint8_t>> matrix_;
};
