#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/videodev2.h>

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
