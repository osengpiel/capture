#include "Controller.hpp"

Controller::Controller(int& fd)
{
    // Check whether the given file descriptor is valid.
    if(fcntl(fd, F_GETFL) == -1)
	throw ControllerException("Bad file descriptor.");

    fd_ = fd;
}

Controller::Controller(Controller && other)
{
   fd_ = other.fd_; 
}

Controller::~Controller() {}

// The move operator, which simply keeps the file descriptor.
Controller & Controller::operator=(Controller && other)
{
    fd_ = other.fd_;
    return *this;
}

inline
int Controller::intRequest(int controller) const
{
    // Request the value of the given camera property and returns it as an
    // integer.
    v4l2_control control = {0};
    control.id = controller;
    if(ioctl(fd_, VIDIOC_G_CTRL, &control) == -1)
	throw ControllerException("Unable to get controller value.");

    return control.value;
}

inline
bool Controller::boolRequest(int controller) const
{
    // Request the value of the given camera property and returns it as an
    // boolean. TODO Find a way to smartly and elegant remove the duplicity of
    // the code (whithout any magic)
    v4l2_control control = {0};
    control.id = controller;
    if(ioctl(fd_, VIDIOC_G_CTRL, &control) == -1)
	throw ControllerException("Unable to get controller value.");

    return control.value;
}

inline
void Controller::intChange(int controller, int value)
{
    v4l2_queryctrl queryctrl = {0};
    v4l2_control control = {0};

    // Check whether the operation is supported.
    queryctrl.id = controller;
    if(ioctl(fd_, VIDIOC_QUERYCTRL, &queryctrl) == -1)
	throw ControllerException("Controller not supported");

    control.id = controller;
    control.value = value;

    // Set the new value.
    if(ioctl(fd_, VIDIOC_S_CTRL, &control))
	throw ControllerException("Controller value was not changed.");
}

inline
void Controller::boolChange(int controller, bool value)
{
    v4l2_queryctrl queryctrl = {0};
    v4l2_control control = {0};

    // Check whether the operation is supported.
    queryctrl.id = controller;
    if(ioctl(fd_, VIDIOC_QUERYCTRL, &queryctrl) == -1)
	throw ControllerException("Controller not supported");

    control.id = controller;
    control.value = value;

    // Set the new value.
    if(ioctl(fd_, VIDIOC_S_CTRL, &control))
	throw ControllerException("Controller value was not changed.");
}

int Controller::getBrightness() const
{
    return intRequest(V4L2_CID_BRIGHTNESS);
}

int Controller::getContrast() const
{
    return intRequest(V4L2_CID_CONTRAST);
}

int Controller::getSaturation() const
{
    return intRequest(V4L2_CID_SATURATION);
}

int Controller::getHue() const
{
    return intRequest(V4L2_CID_HUE);
}

int Controller::getSharpness() const
{
    return intRequest(V4L2_CID_SHARPNESS);
} 

int Controller::getGain() const
{
    return intRequest(V4L2_CID_GAIN);
}

int Controller::getWhiteBalanceTemperature() const
{
    return intRequest(V4L2_CID_WHITE_BALANCE_TEMPERATURE);
}

int Controller::getFocusAbsolute() const
{
    return intRequest(V4L2_CID_FOCUS_ABSOLUTE);
}

int Controller::getFocusRelative() const
{
    return intRequest(V4L2_CID_FOCUS_RELATIVE);
}

int Controller::getExposureAbsolute() const
{
    return intRequest(V4L2_CID_EXPOSURE_ABSOLUTE);
}

bool Controller::isExposureAutoPriorityOn() const
{
    return boolRequest(V4L2_CID_EXPOSURE_AUTO_PRIORITY);
}

bool Controller::isAutoGainOn() const
{
    return boolRequest(V4L2_CID_AUTOGAIN);
}

bool Controller::isAutoWhiteBalanceOn() const
{
    return boolRequest(V4L2_CID_AUTO_WHITE_BALANCE);
}

bool Controller::isFocusAutoOn() const
{
    return boolRequest(V4L2_CID_FOCUS_AUTO);
}

bool Controller::isExposureAutoOn() const
{
    return boolRequest(V4L2_CID_EXPOSURE_AUTO);
}

void Controller::setBrigthness(int value)
{
    intChange(V4L2_CID_BRIGHTNESS ,value);
}

void Controller::setContrast(int value)
{
    intChange(V4L2_CID_CONTRAST ,value);
}

void Controller::setSaturation(int value)
{
    intChange(V4L2_CID_SATURATION ,value);
}

void Controller::setHue(int value)
{
    intChange(V4L2_CID_HUE ,value);
}

void Controller::setSharpness(int value)
{
    intChange(V4L2_CID_SHARPNESS ,value);
}

void Controller::setGain(int value)
{
    intChange(V4L2_CID_GAIN ,value);
}

void Controller::toggleAutoGainOn(bool value)
{
    intChange(V4L2_CID_AUTOGAIN ,value);
}

void Controller::toggleAutoWhiteBalanceOn(bool value)
{
    boolChange(V4L2_CID_AUTO_WHITE_BALANCE ,value);
}

void Controller::setWhiteBalanceTemperature(int value)
{
    intChange(V4L2_CID_WHITE_BALANCE_TEMPERATURE ,value);
}

void Controller::setFocusAbsolute(int value)
{
    intChange(V4L2_CID_FOCUS_ABSOLUTE ,value);
}

void Controller::setFocusRelative(int value)
{
    intChange(V4L2_CID_FOCUS_RELATIVE ,value);
}

void Controller::toggleFocusAuto(bool value)
{
    boolChange(V4L2_CID_FOCUS_AUTO ,value);
}
void Controller::toggleExposureAuto(bool value)
{
    boolChange(V4L2_CID_EXPOSURE_AUTO ,value);
}

void Controller::setExposureAbsolute(int value)
{
    intChange(V4L2_CID_EXPOSURE_ABSOLUTE ,value);
}

void Controller::toggleExposureAutoPriority(bool value)
{
    boolChange(V4L2_CID_EXPOSURE_AUTO_PRIORITY ,value);
}
