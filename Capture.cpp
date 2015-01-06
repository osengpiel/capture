#include "Capture.hpp"
#include <iostream>

inline __u32 resolveFormat(const std::string & fourcc)
{
    assert(fourcc.size() == 4);
    return ((__u32)(fourcc[0]) | (__u32)(fourcc[1])<<8 | (__u32)(fourcc[2])<<16
	    | (__u32)(fourcc[3])<<24);
}

Capture::Capture(const char * device, unsigned int width, unsigned int height,
	const std::string & fourcc, unsigned int bufferNr)
	    :width_(width), height_(height)
{
    assert(bufferNr > 0);

    // Open the device
    fd_ = open(device,O_RDWR | O_NONBLOCK, 0);
    if(fd_ == -1)
	throw CaptureException("Device not found.");
     
    // Check for the capabilities
    v4l2_capability caps = { };
    if(ioctl(fd_, VIDIOC_QUERYCAP, &caps) == -1)
	throw CaptureException("Capabilities not supported.");
    
    // Setting the format
    v4l2_format fmt = { };
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = width;
    fmt.fmt.pix.height = height;
    fmt.fmt.pix.pixelformat = resolveFormat(fourcc);
    fmt.fmt.pix.field = V4L2_FIELD_NONE;

    if(ioctl(fd_, VIDIOC_S_FMT, &fmt) == -1)
	throw CaptureException("Setting format failed.");

    // Request buffers
    v4l2_requestbuffers request = { };

    request.count = bufferNr;
    request.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    request.memory = V4L2_MEMORY_MMAP;

    if(ioctl(fd_, VIDIOC_REQBUFS, &request) == -1)
	throw CaptureException("Buffer request failed.");

    // Create the image buffer
    for(int i = 0; i < request.count; i++)
    {
	v4l2_buffer buf = { };
	buf.index = i;
	buf.type = request.type;
	buf.memory = request.memory;

	if(ioctl(fd_, VIDIOC_QUERYBUF, &buf) == -1)
	    throw CaptureException("Buffer query failed.");
	
	auto start = mmap (NULL, buf.length, PROT_READ | PROT_WRITE,
		MAP_SHARED, fd_, buf.m.offset);
	if (start == MAP_FAILED)
	    throw CaptureException("MMAP failed.");

	buffer_.emplace_back(start, width_, height_, buf.length);
    }

    for(int i = 0 ; i < buffer_.size() ; i++)
    {
	v4l2_buffer buf = { };
	buf.index = i;
	buf.type = request.type;
	buf.memory = request.memory;

	if(ioctl(fd_, VIDIOC_QBUF, &buf) == -1)
	    throw CaptureException("Enqueueing buffer failed (constructor).");

    }

    // Start the stream
    auto type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if(ioctl(fd_, VIDIOC_STREAMON, &type) == -1)
	throw CaptureException("Not able to start stream.");
}
Capture::~Capture()
{
    // Stop the stream
    auto type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if(ioctl(fd_, VIDIOC_STREAMOFF, &type) == -1)

    // Release the memory
    for(auto& img : buffer_)
    {
	munmap(img.getData(),img.getSize());
    }

    // Close the file
    close(fd_);
}

Image Capture::getFrame()
{
    // Get a frame
    v4l2_buffer buf = { };
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    if(ioctl(fd_, VIDIOC_DQBUF, &buf) == -1)
	throw NoFrameException();

    return Image(fd_,buf,buffer_[buf.index].getData());
}

Controller Capture::getController()
{
    return Controller(fd_);
}
Image::Image() = default;
Image::Image(int fd, v4l2_buffer buf, void * data)
    : fd_(fd), buf_(buf), data_(data)
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
void * Image::getData()
{
    return data_;
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
