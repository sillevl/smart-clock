#include "mbed.h"
#include "display.h"
#include "MAX44009.h"

static const PinName SDA_PIN = PB_14;
static const PinName SCL_PIN = PB_13;
static const int I2C_ADDRESS = 0xC0;

I2C i2c(SDA_PIN, SCL_PIN);


// Blinking rate in milliseconds
#define BLINKING_RATE     1000ms

Display display(&i2c, I2C_ADDRESS, I2C_ADDRESS + 2);
MAX44009 sensor(&i2c, 0x94);


int main()
{
    printf("*** Smart Clock ***\r\n");

    // Initialise the digital pin LED1 as an output
    DigitalOut led(PC_0);
    display.clear();

    while (true) {
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
        display.print(1337);
        // sensor.getLUXReading();
    }
}