#include "fiction.h"

#include <cassert>

size_t fiction_rgb::lum() const {
    return static_cast<size_t>(r)*0.299
    + static_cast<size_t>(g)*0.587
    + static_cast<size_t>(b)*0.114;
}

fiction_img::fiction_img(size_t w, size_t h, fiction_rgb fill)
    : width(w)
    , height(h)
    , pixels(w * h, fill) {
}

fiction_rgb fiction_img::get_pixel(size_t x, size_t y) const {
    return const_cast<fiction_img*>(this)->get_pixel(x, y);
}

fiction_rgb& fiction_img::get_pixel(size_t x, size_t y) {
    assert(x < get_width() && y < get_height() && x >= 0 && y >= 0);
    return get_line(y)[x];
}

fiction_rgb* fiction_img::get_line(size_t y) {
    assert(y >= 0 && y < height);
    return pixels.data() + width * y;
}

const fiction_rgb* fiction_img::get_line(size_t y) const {
    return const_cast<fiction_img*>(this)->get_line(y);
}

size_t fiction_img::get_width() const {
    return width;
}

size_t fiction_img::get_height() const {
    return height;
}
