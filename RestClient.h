#include <Arduino.h>
#include <WiFi.h>

#ifndef RESTCLIENT_H
#define RESTCLIENT_H

class RestClient{
    public:
        RestClient(String server, int port);
        void begin(String ssid, String pass);
        void set_header(String nHeader);
        void set_server(String server, int port);
        String get(String path);
        String post(String path);
    private:
        String serverName, serverPath, Header = "", ssid, pass;
        int serverPort;
        WiFiClient client;
};

#endif