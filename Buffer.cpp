#include "Buffer.hpp"

Buffer::Buffer() { }

Buffer::Buffer(void * data,unsigned int width, unsigned int height, size_t size)
    :data_(data), width_(width), height_(height), size_(size)
{

}

Buffer::~Buffer() 
{

}

Buffer::Buffer(Buffer&& other)
{
    data_ = other.data_;
    width_ = other.width_;
    height_ = other.height_;
    size_ = other.size_;

    other.data_ = nullptr;
    other.width_ = 0;
    other.height_ = 0;
    other.size_ = 0;
}

Buffer & Buffer::operator=(Buffer&& other)
{
    data_ = other.data_;
    width_ = other.width_;
    height_ = other.height_;
    size_ = other.size_;

    other.data_ = nullptr;
    other.width_ = 0;
    other.height_ = 0;
    other.size_ = 0;

    return *this;
}	

void * Buffer::getData() const
{
    return data_;
}

int Buffer::getWidth() const
{
    return width_;
}

int Buffer::getHeight() const
{
    return height_;
}

size_t Buffer::getSize() const
{
    return size_;
}
