#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <vector>

namespace img_lib {

struct size {
    int width;
    int height;
};

struct color {
    static color black() {
        return {std::byte{0}, std::byte{0}, std::byte{0}, std::byte{255}};
    }

    std::byte r, g, b, a;
};

class image {
public:
    image() = default;

    image(int w, int h, color fill);

    color get_pixel(int x, int y) const {
        return const_cast<image*>(this)->get_pixel(x, y);
    }
    color& get_pixel(int x, int y) {
        assert(x < get_width() && y < get_height() && x >= 0 && y >= 0);
        return get_line(y)[x];
    }

    color* get_line(int y);
    const color* get_line(int y) const;

    int get_width() const;
    int get_height() const;

    int get_step() const;

    explicit operator bool() const {
        return get_width() > 0 && get_height() > 0;
    }

    bool operator!() const {
        return !operator bool();
    }

private:
    int width_ = 0;
    int height_ = 0;
    int step_;

    std::vector<color> pixels_;
};

}  // namespace img_lib
