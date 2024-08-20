//for now this isnt crashing
#include <Arduino.h>
//#include <ESP8266WiFi.h>
#include <SocketIoClient.h>
#include <WebSocketsServer.h>
#include "wifipassword.h"
#include <ArduinoJson.h>
#include "WiFi.h"

//#include <Hash.h>

#define USER_SERIAL Serial
IPAddress local_IP(192, 168, 1, 25);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(1, 1, 1, 1); 
IPAddress secondaryDNS(1, 0, 0, 1);

    
const char* ssid = "Ralf2";
const char* pass = WIFI_PASSWORD;
int led1,led2,led3,led4,led5,led6,led7,led8;
//const char* user = 192.168.1.6
unsigned long startMillis = 0;
unsigned long startMillis2 = 0;
unsigned long startMillis3 = 0;
unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;  
String header;
int online;
SocketIoClient socketIO;
WebSocketsServer webSocket = WebSocketsServer(81);

void socket_DisConnected(const char * payload, size_t length) {
    online = 0;
    Serial.println(online);
    Serial.println("Socket.IO not working for now!");
}
void socket_Connected(const char * payload, size_t length) {
    Serial.println(online);
    online = 1;
  if(sizeof(payload) < 10 ){
    Serial.println("Socket.IO Connected!");
    DynamicJsonDocument doc(1024);
    doc[0] = led1;doc[1] = led2;doc[2] = led3;doc[3] = led4;doc[4] = led5;doc[5] = led6;doc[6] = led7;doc[7] = led8;
    char json_string[256];
    serializeJson(doc, json_string);
    if(online == 1){socketIO.emit("sendstatus",json_string, 1);}
  }
}

void socket_Recive(const char * payload, size_t length) {
  if(sizeof( payload )< 10 ){
    Serial.println(payload);
    StaticJsonDocument<600> doc;
    DeserializationError error = deserializeJson(doc, payload);
    led1 = doc["led1"];led2 = doc["led2"];led3 = doc["led3"];led4 = doc["led4"];led5 = doc["led5"];led6 = doc["led6"];led7 = doc["led7"];led8 = doc["led8"];   
    DynamicJsonDocument dot(1024);
    dot[0] = led1;dot[1] = led2;dot[2] = led3;dot[3] = led4;dot[4] = led5;dot[5] = led6;dot[6] = led7;dot[7] = led8;
    char json_string[256];
    serializeJson(dot, json_string);
    webSocket.broadcastTXT(json_string);
  }
}
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {
  
  switch(type) {
  case WStype_DISCONNECTED:{ Serial.println("disconnected");}          
  break;
  case WStype_CONNECTED:{

  IPAddress ip = webSocket.remoteIP(num);
  
  Serial.println("Connectedkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk");}       
  break;  
  case WStype_TEXT:{
    if(sizeof((char *) &payload[0]) < 10 ){
  StaticJsonDocument<600> doc;
  DeserializationError error = deserializeJson(doc, (char *) &payload[0]);
  led1 = doc[0];led2 = doc[1];led3 = doc[2];led4 = doc[3];led5 = doc[4];led6 = doc[5];led7 = doc[6];led8 = doc[7];
      DynamicJsonDocument dot(1024);
      dot[0] = led1;dot[1] = led2;dot[2] = led3;dot[3] = led4;dot[4] = led5;dot[5] = led6;dot[6] = led7;dot[7] = led8;
      char json_string[256];
      serializeJson(dot, json_string);
      webSocket.broadcastTXT(json_string);
      if(online == 1){socketIO.emit("sendstatus",json_string, 1);}
      Serial.println(led1);
    }
  }
  }      
  }

     
void setup() {   
    USER_SERIAL.begin(115200);
//    pinMode(16, OUTPUT);
//    pinMode(D1, OUTPUT);
//    pinMode(D2, OUTPUT);
//    pinMode(D3, OUTPUT);
//    pinMode(D4, OUTPUT);
//    pinMode(14, INPUT_PULLUP);
//      pinMode(12, INPUT_PULLUP);
//    pinMode(13, INPUT_PULLUP);
//    pinMode(10, INPUT_PULLUP);
//    pinMode(9, INPUT_PULLUP);
//    pinMode(8, INPUT_PULLUP);
//    pinMode(11, INPUT_PULLUP);
//    pinMode(7, INPUT_PULLUP);
      
      connectWiFi();
      
      socketIO.on("connect", socket_Connected);
      socketIO.on("disconnect", socket_DisConnected);
      socketIO.begin("192.168.1.15", 3000);
      socketIO.on("recive", socket_Recive);
    
    
}
void Ok(){
      DynamicJsonDocument doc(1024);
      doc[0] = led1;doc[1] = led2;doc[2] = led3;doc[3] = led4;doc[4] = led5;doc[5] = led6;doc[6] = led7;doc[7] = led8;
      char json_string[256];
      serializeJson(doc, json_string);
      if(online == 1){socketIO.emit("sendstatus",json_string, 1);}
      webSocket.broadcastTXT(json_string);
}
void loop() {
 
// if((digitalRead(12)==LOW)  && (millis() - startMillis2 >=500UL)){  startMillis = millis();  startMillis2 = millis(); led1= !led1;  Ok(led1,led2,led3,led4,led5,led6,led7,led8); }
// if((digitalRead(13)==LOW)  && (millis() - startMillis2 >=500UL)){  startMillis = millis();  startMillis2 = millis(); led2= !led2;  Ok(led1,led2,led3,led4,led5,led6,led7,led8); }
// if((digitalRead(10)==LOW)  && (millis() - startMillis2 >=500UL)){  startMillis = millis();  startMillis2 = millis(); led3= !led3;  Ok(led1,led2,led3,led4,led5,led6,led7,led8); }   
// if((digitalRead(9)==LOW)   && (millis() - startMillis2 >=500UL)){  startMillis = millis();  startMillis2 = millis(); led5= !led5;  Ok(led1,led2,led3,led4,led5,led6,led7,led8); }   
//  if((digitalRead(8)==LOW) &&  (millis() - startMillis >=300UL)){ led4= !led4; }   
//  if((digitalRead(7)==LOW) &&  (millis() - startMillis >=300UL)){ led6= !led6; }   
//  if((digitalRead(11)==LOW) &&  (millis() - startMillis >=300UL)){ led7= !led7; }   
  socketIO.loop();
  webSocket.loop();
if(millis() - startMillis >=1000UL){
startMillis = millis();
Serial.println(online);
DynamicJsonDocument doc(1024);
doc[0] = "x.rockingo@gmail.com";
char json_string[256];
serializeJson(doc, json_string);
DynamicJsonDocument dot(1024);
dot[0] = led1;dot[1] = led2;dot[2] = led3;dot[3] = led4;dot[4] = led5;dot[5] = led6;dot[6] = led7;dot[7] = led8;
char json_strins[256];
serializeJson(dot, json_strins);
if(online == 1){socketIO.emit("sendv",json_string, 1);
Serial.println("im being emited here in the loop");
}
webSocket.broadcastTXT(json_strins);
}
}

void connectWiFi(){
   if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    USER_SERIAL.print(".");
    delay(1000);
  }
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  USER_SERIAL.print("");
  USER_SERIAL.println("WiFi connected");
  USER_SERIAL.print("IP Address : ");
  USER_SERIAL.println(WiFi.localIP());
 
}
