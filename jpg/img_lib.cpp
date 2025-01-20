#include "img_lib.h"

namespace img_lib {

image::image(int w, int h, color fill)
    : width_(w)
    , height_(h)
    , step_(w)
    , pixels_(step_ * height_, fill) {
}

color* image::get_line(int y) {
    assert(y >= 0 && y < height_);
    return pixels_.data() + step_ * y;
}

const color* image::get_line(int y) const {
    return const_cast<image*>(this)->get_line(y);
}

int image::get_width() const {
    return width_;
}

int image::get_height() const {
    return height_;
}

int image::get_step() const {
    return step_;
}

}  // namespace img_lib
