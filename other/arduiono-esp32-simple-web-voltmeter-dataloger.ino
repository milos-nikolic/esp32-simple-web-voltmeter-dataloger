#include "WiFi.h"
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"

#include <WiFiClient.h>
#include <WiFiAP.h>

#include <driver/adc.h>

#define CONFIG_FREERTOS_HZ 1000


#include <ArduinoJson.h>

#define B1_PIN_ADC ADC1_CHANNEL_0
#define B2_PIN_ADC ADC1_CHANNEL_3
#define B3_PIN_ADC ADC1_CHANNEL_6
#define B4_PIN_ADC ADC1_CHANNEL_7

// Set these to your desired credentials.
const char *ssid = "yourAP";
const char *password = "yourPassword";
 
AsyncWebServer server(80);
 
void setup(){
  Serial.begin(115200);
 
  if(!SPIFFS.begin())
  {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
  }

 WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });


    server.on("/canvasjs.min.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/canvasjs.min.js", "application/javascript");
  });


    server.on("/jquery.mobile.min.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/jquery.mobile.min.css", "text/css");
  });


    server.on("/jquery-3.4.1.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/jquery-3.4.1.js", "application/javascript");
  });


    server.on("/sample", HTTP_GET, [](AsyncWebServerRequest *request){
    String test;
  
    StaticJsonDocument<1000> doc;

    doc["ADC1_CHANNEL_0"] = adc1_get_raw(B1_PIN_ADC);
    doc["ADC1_CHANNEL_3"] = adc1_get_raw(B2_PIN_ADC);
    doc["ADC1_CHANNEL_6"] = adc1_get_raw(B3_PIN_ADC);
    doc["ADC1_CHANNEL_7"] = adc1_get_raw(B4_PIN_ADC);


    String output;
    serializeJson(doc, test);
    request->send(200, "text/plain", test);

  });


  adc1_config_width(ADC_WIDTH_12Bit);

  adc1_config_channel_atten(B1_PIN_ADC, ADC_ATTEN_11db); // Pin 36
  adc1_config_channel_atten(B2_PIN_ADC, ADC_ATTEN_11db); // Pin 39
  adc1_config_channel_atten(B3_PIN_ADC, ADC_ATTEN_11db); // Pin 34
  adc1_config_channel_atten(B4_PIN_ADC, ADC_ATTEN_11db); // Pin 35

  server.begin();
}
 
void loop()
{
//IDF_Analog_Tester();
  
}




void IDF_Analog_Tester()
{
  adc1_config_width(ADC_WIDTH_12Bit);

  adc1_config_channel_atten(B1_PIN_ADC, ADC_ATTEN_11db); // Pin 36
  adc1_config_channel_atten(B2_PIN_ADC, ADC_ATTEN_11db); // Pin 39
  adc1_config_channel_atten(B3_PIN_ADC, ADC_ATTEN_11db); // Pin 34
  adc1_config_channel_atten(B4_PIN_ADC, ADC_ATTEN_11db); // Pin 35

  while (true)
  {
    Serial.printf("36:%04d 39:%04d 34:%04d 35:%04d\n\r",
                  adc1_get_raw(B1_PIN_ADC),
                  adc1_get_raw(B2_PIN_ADC),
                  adc1_get_raw(B3_PIN_ADC),
                  adc1_get_raw(B4_PIN_ADC));

    delay(50);
  }
}
