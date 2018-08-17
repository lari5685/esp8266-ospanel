#include <ESP8266WiFi.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>
const char* ssid     = "--------";
const char* password = "--------";
const char* host = "192.168.0.104";

#define DHTPIN 2
int r1=16,r2=5,r3=4,r4=0;


  DHT dht(DHTPIN, DHT22);
void setup() {
  dht.begin();
  Serial.begin(115200);
  delay(10);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = " /data/";
  url += "input.php";
  url += "?temp=";
  url += t;
  url += h;

  ///test/index.php?button=rele_1_on

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 2000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  String line;
  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  if(line[1] == '0') {digitalWrite(r1, HIGH);}
  else {digitalWrite(r1, LOW);}
  if(line[2] == '0') {digitalWrite(r2, HIGH);}
  else {digitalWrite(r2, LOW);}
  if(line[3] == '0') {digitalWrite(r3, HIGH);}
  else {digitalWrite(r3, LOW);}
  if(line[4] == '0') {digitalWrite(r4, HIGH);}
  else {digitalWrite(r4, LOW);}

}

