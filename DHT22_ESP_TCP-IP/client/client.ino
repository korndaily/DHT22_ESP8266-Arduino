#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTPIN D7
#define DHTTYPE DHT22

#define SERVER_PORT 5000            //ค่า port ที่ต้องการเชื่อมต่อ
IPAddress server_ip = {192, 168, 1, 200};    //ค่า ip ของ Server (อย่าลืมแก้เป็น IP ของตัวเอง)

const char* ssid = "kerkorn";         //ค่าของ SSID (อย่าลืมแก้เป็น ชื่อ SSID ของตัวเอง)
const char* password = "0838393616"; //ค่าของ SSID (อย่าลืมแก้เป็น password ของตัวเอง)

WiFiServer server(SERVER_PORT); //สร้าง object server และกำหนด port ที่ต้องการเชื่อมต่อกับ server
WiFiClient client;              //สร้าง object client

DHT dht(DHTPIN, DHTTYPE);
String temp;
String humi;

void setup()
{
  Serial.begin(115200);       //เปิดใช้ Serial
  WiFi.begin(ssid, password); //เชื่อมต่อกับ AP

  while (WiFi.status() != WL_CONNECTED)  //รอการเชื่อมต่อ
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); //แสดงหมายเลข IP

  Serial.println("Connect TCP Server");
  while (!client.connect(server_ip, SERVER_PORT)) //เชื่อมต่อกับ Server
  {
    Serial.print(".");
    delay(100);
  }
  Serial.println("Success");
  ESP.wdtDisable();  //ปิด watch dog Timer
  dht.begin();
}

void loop()
{
  while (client.available())  //ตรวจเช็ตว่ามี Data ส่งมาจาก Server หรือไม่
  {
    uint8_t  data = client.read(); //อ่าน Data จาก Buffer
    Serial.write(data); //แสดงผล Data ทาง Serial
  }

  float humidity = dht.readHumidity(); // ดึงค่าความชื้น
  float temperature = dht.readTemperature(); // ดึงค่าอุณหภูมิ
  delay(1000);

  while (String(temperature) == "nan" || String(humidity) == "nan")
  {
    humidity = dht.readHumidity(); // ดึงค่าความชื้น
    temperature = dht.readTemperature(); // ดึงค่าอุณหภูมิ
    delay(500);
  }

  temp = "TEMP: " + String(temperature, 2);
  humi = "HUMI: " + String(humidity, 2);
  String SendData = temp + "\t" + humi;

  client.println(SendData);     //ส่งค่าที่ได้รับกลับไปยัง Server
  delay(1000);
}
