#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include <assert.h>

#include <exception>

//! This is the general exception for ioctl errors occuring in the Capture.
/**
  * If this exception occurs, there is something wrong with the camera. It is
  * either not ready to use or not available in another way.
  */
class CaptureException : public std::exception
{
public:
    CaptureException(std::string message)
	:message_(message) {}
    ~CaptureException() {}
    virtual const char * what() const noexcept { return message_.c_str(); }
private:
    std::string message_;
};

class Image
{
public:
    Image();
    Image(int fd, v4l2_buffer buf, void * data);
    Image(Image && img);
    ~Image();

    Image & operator=(Image && img);
    
    void * getData();
private:
    void * data_ = nullptr;
    int fd_ = 0;
    v4l2_buffer buf_ = { };
};

#endif
