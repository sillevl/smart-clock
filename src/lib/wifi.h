#pragma once

#include "EthernetInterface.h"

class Wifi {

    public:
    Wifi();
    void connect();
    NetworkInterface* getNet();

    private:
    void print_network_info();
    void scan();
    NetworkInterface* net;
    static constexpr size_t MAX_NUMBER_OF_ACCESS_POINTS = 10;

    static const char *get_security_string(nsapi_security_t sec);
};