#include "DHT.h"
#define DHTPIN D7
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

String temp;
String humi;

void setup() {
  
  Serial.begin(9600);
  dht.begin();
  
}

void loop() {

  float humidity = dht.readHumidity(); // ดึงค่าความชื้น
  float temperature = dht.readTemperature(); // ดึงค่าอุณหภูมิ

  temp = "TEMP: " + String(temperature, 2);
  humi = "HUMI: " + String(humidity, 2);

  Serial.print(temp + "\t" + humi + "\n");
  delay(1000);
  
}
