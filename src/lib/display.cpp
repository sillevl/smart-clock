#include "display.h"
#include <math.h>

constexpr uint8_t Display::channelMap[4][8];
constexpr uint8_t Display::segmentMap[10];


Display::Display(I2C* i2c, int address_1, int address_2): 
    drivers {TLC59116(i2c, address_1), TLC59116(i2c, address_2) } {
    enableAll();
}

void Display::run() {
    for(int character = 0; character < NUMBER_OF_CHARACTERS; character++) {
        setSegment(character, character);
    }
}

void Display::print(int number) {
    for(int character = 0; character < NUMBER_OF_CHARACTERS; character++) {
        uint8_t index = NUMBER_OF_CHARACTERS - 1 - character;
        uint8_t value = (number / (int) pow(10.0, (double) character)) % 10;
        setSegment(index, value);
    }
}

void Display::clear() {
    setAllChannels(0.0);
}

void Display::setSegment(int index, int value) {
    uint8_t driverIndex = index >> 1;
    for(int segment = 0; segment < NUMBER_OF_SEGMENTS; segment++) {
        float brightness = (segmentMap[value] & (0b10000000 >> segment)) ? 1.0 : 0.0;
        uint8_t channel = channelMap[index][segment];

        drivers[driverIndex].setChannel(channel, brightness);
    }
}

void Display::enableAll(){
    for(int i = 0; i < NUMBER_OF_DRIVERS; i++) {
        drivers[i].enable();
    }
}

void Display::setAllChannels(float brightness) {
    for(int channel = 0; channel < NUMBER_OF_CHANNELS_PER_DRIVER; channel++) {
        for(int i = 0; i < NUMBER_OF_DRIVERS; i++) {
            drivers[i].setChannel(channel, brightness);
        }
    }
}