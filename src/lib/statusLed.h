#pragma once

#include "mbed.h"

class StatusLed {
    public:
    StatusLed(PinName pin);

    void toggle();

    private:
    DigitalOut led;
};