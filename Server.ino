
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <Hash.h>

const char* ssid = "DG_QMS";         
const char* password = "PASSWORD"; 

IPAddress ip(192,168,11,4);
IPAddress gateway(192,168,11,1);
IPAddress subnet(255,255,255,0); 

WebSocketsServer webSocket = WebSocketsServer(81);
                           
#define _LED_TX 4
#define _LED_RX 5
#define _LED_NETWORK 14

void setup() { 
  pinMode(_LED_TX, OUTPUT);
  pinMode(_LED_RX, OUTPUT);
  pinMode(_LED_NETWORK, OUTPUT);
  digitalWrite(_LED_NETWORK, HIGH);
  Serial.begin(9600); 
  
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip,gateway,subnet);
  WiFi.softAP(ssid, password); 
  
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() { 
    webSocket.loop();
    if (Serial.available() > 0){
      char c[] = {(char)Serial.read()};
      webSocket.broadcastTXT(c, sizeof(c));
      digitalWrite(_LED_TX, HIGH);
      delay(1);
      digitalWrite(_LED_TX, LOW);
    }
  digitalWrite(_LED_TX, LOW);
  digitalWrite(_LED_RX, LOW);
   
} 

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){

  switch(type){

      case WStype_ERROR:
          break;
      case WStype_DISCONNECTED:
          break;
      case WStype_CONNECTED:
          break;
      case WStype_TEXT:
            for(int i = 0; i < length; i++) Serial.write((char) payload[i]); 
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
    
    digitalWrite(_LED_RX, HIGH);
    delay(1);
    digitalWrite(_LED_RX, LOW);
}
                 
