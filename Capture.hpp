#ifndef CAPTURE_HPP
#define CAPTURE_HPP

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include <assert.h>

#include <string>
#include <vector>
#include <exception>

#include "Buffer.hpp"
#include "Controller.hpp"

#include "Image.hpp"


//! This exception is thrown, when none of the buffers provides an image.
/**
  * This exception can be ignored in all cases. It only exists to indicate, that
  * there was no new image in the buffers. It requires no special treatment.
  */
class NoFrameException : public std::exception
{
public:
    NoFrameException() {}
    ~NoFrameException() {}
};

//! The class which handles the communication with the camera.
/**
  * This is the interface with the hardware camera. The device (like
  * /dev/video0) is accessed and initialized with only calling the constructor
  * of this class. The width and heigt of the picture provided by the webcam are
  * stated here, as well as the fps (which is 25 by defauld) and the count of
  * the buffers (which is standard 3).
  *
  * The format of the picture has to be a string containing four characters
  * (e.g. "YUYV"). The format given to the constructor determines which format
  * the camera writes to the buffer. It has to be remembered (at the moment) for
  * later use. [TODO write the format information to the image, which is passed]
  */
class Capture
{
public:
    Capture(const char * device, unsigned int width, unsigned int height , const
	    std::string & fourcc, unsigned int bufferNr = 3);
    ~Capture();
    Image getFrame();
    Controller getController();
private:
    int fd_;
    std::vector<Buffer> buffer_;
    unsigned int width_, height_;
};

#endif
