#include "wifi.h"

Wifi::Wifi() {

}

void Wifi::connect() {
    net = NetworkInterface::get_default_instance();

    if (!net) {
        printf("Error! No network interface found.\r\n");
    }

    if (net->wifiInterface()) {
        scan();
    }
    printf("Connecting to the network...\r\n");

    nsapi_size_or_error_t result = net->connect();
    if (result != 0) {
        printf("Error! _net->connect() returned: %d\r\n", result);
        return;
    }

    print_network_info();
}

void Wifi::print_network_info() {
    SocketAddress a;
    net->get_ip_address(&a);
    printf("IP address: %s\r\n", a.get_ip_address() ? a.get_ip_address() : "None");
    net->get_netmask(&a);
    printf("Netmask: %s\r\n", a.get_ip_address() ? a.get_ip_address() : "None");
    net->get_gateway(&a);
    printf("Gateway: %s\r\n", a.get_ip_address() ? a.get_ip_address() : "None");
}

void Wifi::scan() {
    WiFiInterface *wifi = net->wifiInterface();

    WiFiAccessPoint ap[MAX_NUMBER_OF_ACCESS_POINTS];

    /* scan call returns number of access points found */
    int result = wifi->scan(ap, MAX_NUMBER_OF_ACCESS_POINTS);

    if (result <= 0) {
        printf("WiFiInterface::scan() failed with return value: %d\r\n", result);
        return;
    }

    printf("%d networks available:\r\n", result);

    for (int i = 0; i < result; i++) {
        printf("Network: %s secured: %s BSSID: %hhX:%hhX:%hhX:%hhx:%hhx:%hhx RSSI: %hhd Ch: %hhd\r\n",
                ap[i].get_ssid(), get_security_string(ap[i].get_security()),
                ap[i].get_bssid()[0], ap[i].get_bssid()[1], ap[i].get_bssid()[2],
                ap[i].get_bssid()[3], ap[i].get_bssid()[4], ap[i].get_bssid()[5],
                ap[i].get_rssi(), ap[i].get_channel());
    }
    printf("\r\n");
}

NetworkInterface* Wifi::getNet() {
    return this->net;
}

const char* Wifi::get_security_string(nsapi_security_t sec)
{
    switch (sec) {
        case NSAPI_SECURITY_NONE:
            return "None";
        case NSAPI_SECURITY_WEP:
            return "WEP";
        case NSAPI_SECURITY_WPA:
            return "WPA";
        case NSAPI_SECURITY_WPA2:
            return "WPA2";
        case NSAPI_SECURITY_WPA_WPA2:
            return "WPA/WPA2";
        case NSAPI_SECURITY_UNKNOWN:
        default:
            return "Unknown";
    }
}