#include <LiquidCrystal.h>
#include "DHT.h"
DHT dht;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String temp;
String humi;

void setup() {
  
  Serial.begin(9600);
  dht.setup(7); // data pin 7
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:

}

void loop() {
  
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity(); // ดึงค่าความชื้น
  float temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ
  
  temp = "TEMP: " + String(temperature, 2);
  humi = "HUMI: " + String(humidity, 2);

  Serial.print(temp + "\t" + humi + "\n");
  
  lcd.setCursor(0, 0); // (note: line 0 is the second row, since counting begins with 0):
  lcd.print(temp);
  lcd.setCursor(0, 1); // (note: line 1 is the second row, since counting begins with 0):
  lcd.print(humi);
  
}
