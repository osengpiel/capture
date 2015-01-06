#include "Buffer.hpp"

Buffer::Buffer() : data_(0), size_(0), width_(0), height_(0) { }

Buffer::Buffer(void * data,unsigned int width, unsigned int height, size_t size)
    :data_(data), size_(size), width_(width), height_(height)
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
}

Buffer & Buffer::operator=(Buffer&& other)
{
    data_ = other.data_;
    width_ = other.width_;
    height_ = other.height_;
    size_ = other.size_;
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
