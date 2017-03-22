
/*
 * 2017/3/19  Sang Uk
 * Template for using Thing Speak Service
 */

const char* host = "api.thingspeak.com";
String url = "/update?api_key=SQ1FWF1BVOGE3PJZ";   // Your Own Key here
const int httpPort = 80;
int interval = 18000;

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid     = "LAMF";
const char* password = "......";

String working(unsigned long x) { 
  double v=double(x)/10;
  Serial.println(v);
  v=v*3.141592;
  v=100*sin(v);
  Serial.print("v : ");
  Serial.println(v);
  return(String("field1=")+String(v));
}

void delivering(String payload) { 
  WiFiClient client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpPort)) {
    Serial.print("connection failed: ");
    Serial.println(payload);
    return;
  }
  String getheader = "GET "+ String(url) +"&"+ String(payload) +" HTTP/1.1";
  client.println(getheader);
  client.println("User-Agent: ESP8266 Sang Uk");  
  client.println("Host: " + String(host));  
  client.println("Connection: close");  
  client.println();

  Serial.println(getheader);
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }
  Serial.println("Done cycle.");
}

void connect_ap() {
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\n Got WiFi, IP address: ");
  Serial.println(WiFi.localIP());  
}

void setup() {
  Serial.begin(115200);
  connect_ap();

  Serial.println("Arduino ThinkSpeak Test");
}

unsigned long mark = 0;
unsigned long x=0;
void loop() {
  if (millis() > mark ) {
     mark = millis() + interval;
     String payload = working(x);
     x=x+1;
     delivering(payload);
  }
}
