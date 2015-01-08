#include "YUYVImage.hpp"

struct YUYV
{
    __u8 y;
    __u8 r;
};

Pixel YUYVImage::getPixel(unsigned int x, unsigned int y)
{
    YUYV tmp = static_cast<YUYV*>(data_)[x*width_+y];
    Pixel ret;
    ret.r = tmp.y;
    ret.g = tmp.y;
    ret.b = tmp.y;
    return ret;
}

void YUYVImage::setPixel(unsigned int x, unsigned int y, Pixel value)
{
    // Will ich grad nicht implementieren
}
