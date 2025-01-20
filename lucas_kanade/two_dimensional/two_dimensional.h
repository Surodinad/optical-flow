#pragma once

#include "../fiction/fiction.h"

#include <iostream>

class TDLK {
public:
    void find_tdlk(const fiction_img& first,
                   const fiction_img& second) const;

    void find_tdlk(const std::vector<std::vector<uint8_t>>& first_img,
                   const std::vector<std::vector<uint8_t>>& second_img,
                   std::vector<std::vector<double>>& u,
                   std::vector<std::vector<double>>& v) const;

private:
    double diff_Ix(const std::vector<std::vector<uint8_t>>& img, int x, int y) const;

    double diff_Iy(const std::vector<std::vector<uint8_t>>& img, int x, int y) const;
    
    double diff_It(const std::vector<std::vector<uint8_t>>& first_img,
                   const std::vector<std::vector<uint8_t>>& second_img,
                   int x, int y) const;
};
