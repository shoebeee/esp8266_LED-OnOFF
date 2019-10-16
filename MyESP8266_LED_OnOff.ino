//Shoeb
//Al Masum
#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include<FS.h>

ESP8266WebServer server;

const char* MySsid="esp8266";
const char* MyPass="12345678";
#define LED 2

IPAddress ip(192,168,10,2);
IPAddress gateway(192,168,10,1);
IPAddress subnet(255,255,255,0);

void on_f(){
char on_page[]=R"RAW(
<html>
<h1>LED ON </h1>
</html>
)RAW";
Serial.println("LED ON");
digitalWrite(LED, HIGH);
server.send(200,"text/html",on_page);
//delay(2000);
}

void off_f(){
char off_page[]=R"RAW(
<html>
<h1>LED OFF </h1>
</html>
)RAW";
Serial.println("LED OFF");
digitalWrite(LED, LOW);
server.send(200,"text/html",off_page);
//delay(2000);
}

void WiFi_AP(){
WiFi.mode(WIFI_AP_STA);
WiFi.softAPConfig(ip,gateway,subnet);
WiFi.softAP(MySsid,MyPass);

Serial.println(" ");
Serial.println("Wifi AP Started...SSID: ");//+MySsid+"; Pass: "+MyPass);
}
  
void setup() {
pinMode(LED,OUTPUT);
digitalWrite(LED,LOW);

  Serial.begin(115200);
  Serial.println("Serial Started");

   //WiFi.mode(WIFI_STA);
   
  //Initializing File System

WiFi.mode(WIFI_AP_STA);
delay(5000);
    WiFi_AP();
Serial.println(WiFi.localIP());

//server.on("/",homepage);
server.on("/on",on_f);
server.on("/off",off_f);

server.begin();  
Serial.println("webserver started");

WiFi_AP();

}
void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();

}
