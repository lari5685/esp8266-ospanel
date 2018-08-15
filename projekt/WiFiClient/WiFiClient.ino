#include <ESP8266WiFi.h>

const char* ssid     = "D-Link-3-8";
const char* password = "639906710";

const char* host = "192.168.0.106";

int r1=16,r2=5,r3=4,r4=0;


void setup() {
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
  delay(1000);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/data/";
  url += "input.php";
  /*url += "?button=";
  url += "rele_4_on";*/

  ///test/index.php?button=rele_1_on

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  String line;
  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    line = client.readStringUntil('\r');
    Serial.println(line);
  }
  Serial.println(line[1]);
  Serial.println(line[2]);
  Serial.println(line[3]);
  Serial.println(line[4]);
  if(line[1] == '0') {digitalWrite(r1, HIGH);}
  else {digitalWrite(r1, LOW);}
  if(line[2] == '0') {digitalWrite(r2, HIGH);}
  else {digitalWrite(r2, LOW);}
  if(line[3] == '0') {digitalWrite(r3, HIGH);}
  else {digitalWrite(r3, LOW);}
  if(line[4] == '0') {digitalWrite(r4, HIGH);}
  else {digitalWrite(r4, LOW);}
  Serial.println();
  Serial.println("closing connection");

}

