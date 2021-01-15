#include "RestClient.h"

RestClient :: RestClient(String server, int port){
    serverName = server;
    serverPort = port;
}

String RestClient :: get(String path){
    String getBody;
    if (espClient.connect(serverName.c_str(), serverPort)) {
        Serial.println("[ INFO ] Conectado a API");
        //Faz uma requisição HTTP
        espClient.println("GET "+serverPath+" HTTP/1.1");
        espClient.println("Host: "+serverName);
        espClient.println(Header);
        espClient.println();

        int timoutTimer = 10000;
        long startTimer = millis();
        boolean state = false;
        String getAll;
      
        while ((startTimer + timoutTimer) > millis()) {
            Serial.print(".");
            delay(100);      
            while (espClient.available()) {
                char c = espClient.read();
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

        espClient.stop();
        return getBody;
    } else {
        Serial.println("[ INFO ] Erro ao se conectar com a API."); //Caso não seja possível obter uma conexao
        return "Erro";
    }
}

String RestClient :: post(String path){

}

void RestClient:: st_header(String nHeader){
    Header = nHeader;
}

void RestClient:: set_server(String server, int port){
    serverName = server;
    serverPort = port;
}