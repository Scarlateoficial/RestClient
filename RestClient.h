#include <Arduino.h>
#include <WiFi.h>

#ifndef RESTCLIENT_H
#define RESTCLIENT_H

class RestClient{
    public:
        RestClient(String server, int port);
        set_header(String nHeader);
        set_server(String server, int port)
        get(String path);
        post(String path);
    private:
        String serverName, serverPath, Header = "";
        int serverPort;
};

#endif