#include <ArduinoJson.h>
#include "WiFi.h"
#include <M5Stack.h>
#include <HTTPClient.h>



 
const char* ssid = "YOUR SSID HERE";
const char* password =  "YOUR WIFI PASSWORD HERE";
 
void setup() {
  M5.begin(true, false, true); 
  WiFi.begin(ssid, password);
  M5.Power.begin();

  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 0);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
     M5.Lcd.println("Connecting to WiFi....");
  }
  M5.Lcd.clear(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Connected to the WiFi network");
 
}
 
void loop() {
  M5.update();
  if (M5.BtnB.wasPressed()) {
    HTTPClient http;
 
    http.begin("https://api.cognitomagic.app/peek/XXXXX"); //Replace XXXXX with your API token
    int httpCode = http.GET();                                        
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        char json[500];
        payload.toCharArray(json, 500);
        StaticJsonDocument<1024> doc;
        deserializeJson(doc, json);
        String peekValue = doc["peek"];

        M5.Lcd.clear(BLACK);
        M5.Lcd.setTextSize(6);
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.println(peekValue);
      }
 
    else {
      M5.Lcd.println("Error");
    }
 
    http.end();
  }
  }
