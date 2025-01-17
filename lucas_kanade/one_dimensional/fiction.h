#pragma once

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
