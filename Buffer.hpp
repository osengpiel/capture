#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <stddef.h>

//! An image container that holds a pointer to the camera memory.
/**
  * This class holds a pointer to the memory of a buffer in which the camera
  * puts its output, as well as the size of the buffer and the dimensions of the
  * picture, which were specified on the initialization of the camera.
  * 
  * The only way to pass this objects is via the move constructor/operator, so
  * the data behind the data pointer is not duplicated.
  */
class Buffer
{
public:
    Buffer();
    Buffer(void * data, unsigned int width, unsigned int height, size_t size);
    Buffer(const Buffer&) = delete; // No copy allowed!
    Buffer(Buffer&&); // Copy-Constructor
    ~Buffer();

    Buffer & operator=(const Buffer&) = delete; // No copy allowed!
    Buffer & operator=(Buffer&&); // Copy-Assignment

    //! Returns a void pointer to the data, which is then to be interpreted.
    void * getData() const;

    int getWidth() const;
    int getHeight() const;
    size_t getSize() const;
private:
    void * data_ = nullptr;
    unsigned int width_ = 0, height_ = 0;
    size_t size_ = 0;
};

#endif
