#include "Image.hpp"

Image::Image() = default;
Image::Image(int fd, v4l2_buffer buf, void * data, unsigned int width, 
	unsigned int height)
    : data_(data), fd_(fd), buf_(buf), width_(width), height_(height)
{
    assert(fd > 0);
    assert(data != nullptr);
}
Image::Image(Image && img)
{
    fd_ = img.fd_;
    buf_ = img.buf_;
    data_ = img.data_;

    img.fd_ = 0;
    img.buf_ = { };
    img.data_ = nullptr;
}
Image::~Image()
{
    if(data_)
    {
	if(ioctl(fd_, VIDIOC_QBUF, &buf_) == -1)
	    throw CaptureException("Enqueueing buffer failed (getFrame).");
    }
}

Image & Image::operator=(Image && img)
{
    fd_ = img.fd_;
    buf_ = img.buf_;
    data_ = img.data_;

    img.fd_ = 0;
    img.buf_ = { };
    img.data_ = nullptr;

    return *this;
}
