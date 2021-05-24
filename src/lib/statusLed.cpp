#include "statusLed.h"

StatusLed::StatusLed(PinName pin): led(pin) {
    led = 0;
}

void StatusLed::toggle() {
    led = !led;
}