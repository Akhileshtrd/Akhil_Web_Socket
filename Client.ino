

#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <Hash.h>

const char* ssid = "*********";           
const char* password = "********";    

WebSocketsClient webSocket;

#define _LED_TX 4   // R5 LD1
#define _LED_RX 5   // R6 LD2
#define _LED_NETWORK 14
#define _LED  2     // Built In LED
void setup() {
  pinMode(_LED_TX, OUTPUT);
  pinMode(_LED_RX, OUTPUT);
  pinMode(_LED_NETWORK, OUTPUT);
  pinMode(_LED, OUTPUT);
  WiFi.mode(WIFI_STA);
  Serial.begin(9600);
  delay(10);
  WiFi.begin(ssid, password);
  digitalWrite(_LED, HIGH);

  webSocket.begin("192.168.11.4", 81, "/");
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
  digitalWrite(_LED_TX, LOW);
  digitalWrite(_LED_RX, LOW);

  
  if (Serial.available() > 0) {
    char c[] = {(char)Serial.read()}; 
    webSocket.sendTXT(c, sizeof(c));  
  }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length){

  switch(type){

      case WStype_ERROR:
          break;
      case WStype_DISCONNECTED:
        digitalWrite(_LED, HIGH);
          break;
      case WStype_CONNECTED:
        digitalWrite(_LED, LOW);
          break;
      case WStype_TEXT:
            for(int i = 0; i < length; i++)Serial.write((char) payload[i]); 
           // for(int i = 0; i < length; i++)Serial.println((char) payload[i]);
          break;
      case WStype_BIN:
          break;
      case WStype_FRAGMENT_TEXT_START:
          break;
      case WStype_FRAGMENT_BIN_START:
          break;
      case WStype_FRAGMENT:
          break;
      case WStype_FRAGMENT_FIN:
          break;
      case WStype_PING:
          break;
      case WStype_PONG:
          break;
    }
}
