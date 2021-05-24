#include "mbed.h"
#include "display.h"
#include "MAX44009.h"

#include "ntp-client/NTPClient.h"
#include "time.h"
#include "statusLed.h"
#include "wifi.h"

#define CET (+2)

static const PinName SDA_PIN = PB_14;
static const PinName SCL_PIN = PB_13;
static const int I2C_ADDRESS = 0xC0;

static const char* NTP_SERVER = "0.be.pool.ntp.org";
static const int NTP_PORT = 123;

I2C i2c(SDA_PIN, SCL_PIN);

Display display(&i2c, I2C_ADDRESS, I2C_ADDRESS + 2);
MAX44009 sensor(&i2c, 0x94);

Wifi wifi;
NTPClient* ntp;

EventQueue queue(32 * EVENTS_EVENT_SIZE);

StatusLed led(PC_0);

void updateTime() {
    time_t timestamp = time(NULL);
    struct tm* ptm;
    ptm = gmtime(&timestamp);
    display.print(((ptm->tm_hour+CET) * 100) + ptm->tm_min);
}

void getNTPTime() {
    time_t timestamp = ntp->get_timestamp();
    if (timestamp < 0) {
        printf("An error occurred when getting the time. Code: %ld\r\n", timestamp);
    } else {
        printf("Current time is %s\r\n", ctime(&timestamp));
        set_time(timestamp);
    }
}

void updateBrightness() {
    double lux = sensor.getLUXReading();
    display.setBrightness( max(min(lux / 100, 1.0), 0.01));
}

void setupNTP() {
    ntp = new NTPClient(wifi.getNet());
    ntp->set_server(NTP_SERVER, NTP_PORT);
    getNTPTime();
}

int main()
{
    printf("*** Smart Clock ***\r\n");
    display.clear();
    wifi.connect();
    setupNTP();

    queue.call_every(500ms, &led, &StatusLed::toggle);
    queue.call_every(100ms, updateBrightness);
    queue.call_every(100ms, updateTime);
    queue.call_every(33min, getNTPTime);

    queue.dispatch_forever();
}