#include "two_dimensional.h"

void TDLK::find_tdlk(const fiction_img& first,
                     const fiction_img& second) const {}

void TDLK::find_tdlk(const std::vector<std::vector<uint8_t>>& first_img,
                     const std::vector<std::vector<uint8_t>>& second_img,
                     std::vector<std::vector<double>>& u,
                     std::vector<std::vector<double>>& v) const
{
    int width = first_img[0].size();
    int height = first_img.size();

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            double Ix = diff_Ix(first_img, x, y);
            double Iy = diff_Iy(first_img, x, y);
            double It = diff_It(first_img, second_img, x, y);

            double denominator = Ix * Ix + Iy * Iy;
            if (denominator != 0) {
                u[y][x] = -Ix * It / denominator;
                v[y][x] = -Iy * It / denominator;
            } else {
                u[y][x] = 0;
                v[y][x] = 0;
            }
        }
    }
}

double TDLK::diff_Ix(const std::vector<std::vector<uint8_t>>& img, int x, int y) const
{
    return (img[y][x + 1] - img[y][x - 1]) / 2.0;
}

double TDLK::diff_Iy(const std::vector<std::vector<uint8_t>>& img, int x, int y) const
{
    return (img[y + 1][x] - img[y - 1][x]) / 2.0;
}

double TDLK::diff_It(const std::vector<std::vector<uint8_t>>& first_img,
                     const std::vector<std::vector<uint8_t>>& second_img,
                     int x, int y) const
{
    return first_img[y][x] - second_img[y][x];
}
