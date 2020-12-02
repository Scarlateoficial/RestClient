#include <Arduino.h>
#include <Wifi.h>

#ifndef RestClient
#define RestClient

class RestClient{
    public:
        RestClient();
        set_header();
        get();
        post();
    private:
        String serverName, serverPath, Header = "";
        int serverPort;
};

#endif