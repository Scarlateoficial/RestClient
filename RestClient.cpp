#include "RestClient.h"

RestClient :: RestClient(String server, int port){
    serverName = server;
    serverPort = port;
}

int RestClient :: begin(String ssid, String pass){
    WiFi.begin(ssid.c_str(), pass.c_str());
    Serial.println("\n[Connecting] [");
    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.println("-");
    }

    Serial.println("");                         //conexão realizada
    Serial.print("[ INFO ] Conectado a: ");
    Serial.println(ssid);
    Serial.print("[ INFO ] Endereço IP: ");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.macAddress());
    return WiFi.status();
}

String RestClient :: get(String path){
    String getBody;
    if (client.connect(serverName.c_str(), serverPort)) {
        Serial.println("[ INFO ] Conectado a API");
        //Faz uma requisição HTTP
        client.println("GET "+path+" HTTP/1.1");
        client.println("Host: "+serverName);
        client.println(Header);
        client.println();

        int timoutTimer = 10000;
        long startTimer = millis();
        boolean state = false;
        String getAll;
      
        while ((startTimer + timoutTimer) > millis()) {
            Serial.print(".");
            delay(100);      
            while (client.available()) {
                char c = client.read();
                if (c == '\n') {
                    if (getAll.length()==0) state=true;
                    getAll = "";
                }
                else if (c != '\r') getAll += String(c);
                if (state==true) getBody += String(c);
                
                startTimer = millis();
            }
            if (getBody.length()>0) break;
        }

        client.stop();
        return getBody;
    } else {
        Serial.println("[ INFO ] Erro ao se conectar com a API."); //Caso não seja possível obter uma conexao
        return "Erro";
    }
}

String RestClient :: post(String path){

}

void RestClient:: set_header(String nHeader){
    Header = nHeader;
}

void RestClient:: set_server(String server, int port){
    serverName = server;
    serverPort = port;
}