#include "WiFi.h"
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"
#define CONFIG_FREERTOS_HZ 1000

const char* ssid = "RELAY842";
const char* password = "bgKN6dKNH5YVHXF7f2pr";
 
AsyncWebServer server(80);
 
void setup(){
  Serial.begin(115200);
 
  if(!SPIFFS.begin()){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
  }
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println(WiFi.localIP());
 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });


    server.on("/jquery.min.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/jquery.min.js", "application/javascript");
  });


    server.on("/jquery.mobile.min.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/jquery.mobile.min.css", "text/css");
  });


    server.on("/jquery.mobile.min.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/jquery.mobile.min.js", "application/javascript");
  });

  server.begin();
}
 
void loop(){}
