#include "mbed.h"
#include "TLC59116.h"

class Display {
    public:
    Display(I2C* i2c, int address_1, int address_2);

    void run();
    void clear();
    void setSegment(int index, int value);
    void print(int number);

    void setBrightness(float brightness);

    private:

    void enableAll();
    void setAllChannels(float brightness);

    static const uint8_t NUMBER_OF_DRIVERS = 2;
    static const uint8_t NUMBER_OF_CHARACTERS = 4;
    static const uint8_t NUMBER_OF_SEGMENTS = 8;
    static const uint8_t NUMBER_OF_CHANNELS_PER_DRIVER = 16;

    static constexpr float GENERAL_BRIGHTNESS = 0.5;

    static constexpr uint8_t channelMap[4][8] = {
        { 15, 13, 11, 9, 7, 5, 3, 1 },
        { 14, 12, 10, 8, 6, 4, 2, 0 },
        { 14, 12, 10, 8, 6, 4, 2, 0 },
        { 15, 13, 11, 9, 7, 5, 3, 1 }
    };

    static constexpr uint8_t segmentMap[10] = {
        0b11111100, // 0
        0b01100000, // 1
        0b11011010, // 2
        0b11110010, // 3
        0b01100110, // 4
        0b10110110, // 5
        0b10111110, // 6
        0b11100000, // 7
        0b11111110, // 8
        0b11110110, // 9
    };

    TLC59116 drivers[NUMBER_OF_DRIVERS];
}; 