#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "VIVOFIBRA-5E51";
const char* password =  "H7qzUud8GD";

long long balance;
long long currentBalance;
HTTPClient http;

void iniciaHTTP(){
  String serverPath = "https://api-rinkeby.etherscan.io/api?module=account&action=balance&address=0xAE2CeD8E05931EE4017Ec81a34C7537Bd89ACe1B&tag=latest&apikey=DCFFPVIFMHX99SJ1XZTH5Q8AYJ77MA9Y17";
  http.begin(serverPath);
}

void conectWifi(){
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando WiFi..");
  }
  Serial.println("Wifi conectado com sucesso!");
}


void blinkLed(){
  digitalWrite(2, HIGH); // Liga o LED
  delay(5000); // Espera 1 segundo
  digitalWrite(2, LOW); // Desliga o LED
}
 
void setup() {
 // Inicializa o pino D2 como saída
 pinMode(2, OUTPUT);
 Serial.begin(115200);
 WiFi.begin(ssid, password);
 conectWifi();
 iniciaHTTP();
}
 
void loop() {
  if(WiFi.status()== WL_CONNECTED){

      StaticJsonDocument<256> doc;


    
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();

        DeserializationError err = deserializeJson(doc, payload);
        if (err) {
          Serial.print(F("deserializeJson() failed with code "));
          Serial.println(err.f_str());
        }

        Serial.println("PAYLOAD: ");
        Serial.println(payload);


        currentBalance = atoll(doc["result"]);

        if (currentBalance > balance){
            balance = currentBalance;
            blinkLed();
        }
 
        
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
      delay(1000);
    }
    else {
      Serial.println("WiFi desconectado, tentando reconectar...");
      conectWifi();
    }
  }
