#include <ESP8266WiFi.h>

#include "DHT.h"
#define DHTPIN D7
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

String temp;
String humi;

const char* ssid     = "kerkorn";
const char* password = "0838393616";

const char* host = "maker.ifttt.com"; // only google.com not https://google.com

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  dht.begin();
}

void loop() {
  delay(5000);

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClientSecure client;
  const int httpPort = 443; // 80 is for HTTP / 443 is for HTTPS!

  client.setInsecure(); // this is the magical line that makes everything work

  if (!client.connect(host, httpPort)) { //works!
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/trigger/DHT_Big_Data/with/key/dDd9vXk2pUHvLWjupXrpNH";
  
  float humidity = dht.readHumidity(); // ดึงค่าความชื้น
  float temperature = dht.readTemperature(); // ดึงค่าอุณหภูมิ
  temp = "TEMP:" + String(temperature, 2);
  humi = "HUMI:" + String(humidity, 2);
  
  url += "?value1=" + temp + "&value2=" + humi;

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println();
  Serial.println("closing connection");
}
