#include <WiFi.h>
#define SERVER_PORT 5000    //กำหนด Port ใช้งาน

const char* ssid = "kerkorn";       //กำหนด SSID
const char* password = "0838393616"; //กำหนด Password

IPAddress local_IP(192, 168, 1, 200);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(1, 1, 1, 1);

WiFiServer server(SERVER_PORT); //สร้าง object server และกำหนด port

void setup()
{
  Serial.begin(115200);   //เปิดใช้ Serial
  WiFi.config(local_IP, gateway, subnet, primaryDNS);
  Serial.println("");
  Serial.println("");
  WiFi.begin(ssid, password); //เชื่อมต่อกับ AP
  while (WiFi.status() != WL_CONNECTED)  //รอการเชื่อมต่อ
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");   //แสดงข้อความเชื่อมต่อสำเร็จ
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());     //แสดงหมายเลข IP
  server.begin();             //เริ่มต้นทำงาน TCP Server
  Serial.println("Server started");       //แสดงข้อความ server เริ่มทำงาน
}

void loop()
{
  WiFiClient client = server.available();  //รอรับ การเชื่อมต่อจาก Client
  if (client)         //ตรวจเช็คว่ามี Client เชื่อมต่อเข้ามาหรือไม่
  {
    while (1)       //วนรอบตลอด
    {
      while (client.available())  //ตรวจเช็ตว่ามี Data ส่งมาจาก Client  หรือไม่
      {
        uint8_t data = client.read(); //อ่าน Data จาก Buffer
        Serial.write(data); //แสดงผล Data ทาง Serial
      }
      delay(500);
      if (server.hasClient()) //ตรวจเช็คว่ายังมี  Client เชื่อมต่ออยู่หรือไม่
      {
        delay(500);
        return;         //ถ้าไม่มีให้ออกจาก ลูป ไปเริ่มต้นรอรับ Client ใหม่
      }
    }
    delay(500);
  }
}
