#ifndef YUYVIMAGE_HPP
#define YUYVIMAGE_HPP

#include "Image.hpp"

class YUYVImage : public Image
{
public:
    using Image::Image;

    Pixel getPixel(unsigned int x, unsigned int y) override;
    void  setPixel(unsigned int x, unsigned int y, Pixel value) override;
};

#endif
