#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "POCO M3";
const char* password =  "esp32teste";
 
void setup() {
 Serial.begin(115200);
 WiFi.begin(ssid, password);
 
 while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");

}
 
void loop() {
  if(WiFi.status()== WL_CONNECTED){
      
      
       HTTPClient http;

        String serverPath = "https://api.etherscan.io/api?module=account&action=balance&address=0xae2ced8e05931ee4017ec81a34c7537bd89ace1b&tag=latest&apikey=HGRCBG8V7RMXP3SK4EA8NJBBUPIEMYV25U";
      
        // Your Domain name with URL path or IP address with path
        http.begin(serverPath);
 
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
      delay(1000);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
