#pragma once
#include "img_lib.h"

#include <filesystem>

namespace img_lib {
using path = std::filesystem::path;

bool save_JPEG(const path& file, const image& image);
image load_JPEG(const path& file);

} // namespace img_lib
