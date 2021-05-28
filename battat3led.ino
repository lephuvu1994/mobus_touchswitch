#include <ESP8266WiFi.h>
#include <WiFiManager.h>


int ModbusTCP_port = 503;                           //cong Modbus
int bitstatus01 =0;
int bitstatus02 =0;

int bitstatus21 =0;
int bitstatus22 =0;

int bitstatus41 =0;
int bitstatus42 =0;
//////// Required for Modbus TCP / IP /// Requerido para Modbus TCP/IP /////////
#define maxInputRegister 20                           //dau vao max
#define maxHoldingRegister 20                         //max giu lai
 
#define MB_FC_NONE 0
#define MB_FC_READ_REGISTERS 3 //implemented
#define MB_FC_WRITE_REGISTER 6 //implemented
#define MB_FC_WRITE_MULTIPLE_REGISTERS 16 //implemented
//
// MODBUS Error Codes
//
#define MB_EC_NONE 0
#define MB_EC_ILLEGAL_FUNCTION 1
#define MB_EC_ILLEGAL_DATA_ADDRESS 2
#define MB_EC_ILLEGAL_DATA_VALUE 3
#define MB_EC_SLAVE_DEVICE_FAILURE 4
//
// MODBUS MBAP offsets
//
#define MB_TCP_TID 0
#define MB_TCP_PID 2
#define MB_TCP_LEN 4
#define MB_TCP_UID 6
#define MB_TCP_FUNC 7
#define MB_TCP_REGISTER_START 8
#define MB_TCP_REGISTER_NUMBER 10
 
byte ByteArray[260];
unsigned int MBHoldingRegister[maxHoldingRegister];
 
//////////////////////////////////////////////////////////////////////////
 
WiFiServer MBServer(ModbusTCP_port);

void battatcung13(void);
void battatcung12(void);
void battatcung14(void);
void setup() {
 WiFiManager wifiManager;
  //có thểreset các cài đặt cũ bằng cách gọi hàm:
  if(digitalRead(5)==0){
    wifiManager.resetSettings();
  }
  //Cài đặt callback, khi kết nối với wifi cũ thất bại, thiết bị sẽ gọi hàm callback
  //và khởi động chế độ AP với SSID được cài tự động là "ESP+chipID"
  wifiManager.setAPCallback(configModeCallback);
  if (!wifiManager.autoConnect("esp8266_wifi"))
  {                     
    ESP.reset();                    // //Nếu kết nối thất bại, thử kết nối lại bằng cách reset thiết bị
    delay(1000);
  }
 pinMode(14, OUTPUT);
 pinMode(12, OUTPUT);
 pinMode(13, OUTPUT);
 
 pinMode(0, INPUT);
 pinMode(2, INPUT);
 pinMode(4, INPUT);
 Serial.begin(9600);
 delay(1000);
 MBServer.begin();
 Serial.println("Connected ");
 Serial.print("ESP8266 Slave Modbus TCP/IP ");
 Serial.print(WiFi.localIP());
 Serial.print(":");
 Serial.println(String(ModbusTCP_port));
 Serial.println("Modbus TCP/IP Online");
 //MBHoldingRegister[1] = bitstatus;
 attachInterrupt(digitalPinToInterrupt(0), battatcung13, CHANGE);
 attachInterrupt(digitalPinToInterrupt(2), battatcung12, CHANGE);
 attachInterrupt(digitalPinToInterrupt(4), battatcung14, CHANGE);
}
 
//================================================================================================== 
void loop() {
 
 
 // Check if a client has connected // Modbus TCP/IP
 WiFiClient client = MBServer.available();
 if (!client) {
 return;
 }
 
 
 boolean flagClientConnected = 0;
 byte byteFN = MB_FC_NONE;
 int Start;
 int WordDataLength;
 int ByteDataLength;
 int MessageLength;
 
 // Modbus TCP/IP
 while (client.connected()) {
 
 if(client.available())
 {
 flagClientConnected = 1;
 int i = 0;
 while(client.available())
 {
 ByteArray[i] = client.read();
 i++;
 }
 
 client.flush();
 
 
 
///// code here --- codigo aqui
 
 ///////// Holding Register [0] A [9] = 10 Holding Registers Escritura
 ///////// Holding Register [0] A [9] = 10 Holding Registers Writing
 /*
 MBHoldingRegister[0] = random(0,12);
 //MBHoldingRegister[1] = random(0,12);
 MBHoldingRegister[2] = random(0,12);
 MBHoldingRegister[3] = random(0,12);
 MBHoldingRegister[4] = random(0,12);
 MBHoldingRegister[5] = random(0,12);
 MBHoldingRegister[6] = random(0,12);
 MBHoldingRegister[7] = random(0,12);
 MBHoldingRegister[8] = random(0,12);
 MBHoldingRegister[9] = random(0,12);*/
 
 
 
 
 ///////// Holding Register [10] A [19] = 10 Holding Registers Lectura
 ///// Holding Register [10] A [19] = 10 Holding Registers Reading
 /*
 int Temporal[10];
 
 Temporal[0] = MBHoldingRegister[10];
 Temporal[1] = MBHoldingRegister[1];
 Temporal[2] = MBHoldingRegister[12];
 Temporal[3] = MBHoldingRegister[13];
 Temporal[4] = MBHoldingRegister[14];
 Temporal[5] = MBHoldingRegister[15];
 Temporal[6] = MBHoldingRegister[16];
 Temporal[7] = MBHoldingRegister[17];
 Temporal[8] = MBHoldingRegister[18];
 Temporal[9] = MBHoldingRegister[19];*/
 
 /// Enable Output 13
 if( MBHoldingRegister[1] !=bitstatus01)// || digitalRead(12) != bitstatus2)
 {
    digitalWrite(13, !digitalRead(13));
//    Serial.println(digitalRead(0));
    if(MBHoldingRegister[1] !=bitstatus01){
      
      bitstatus01 =  digitalRead(13);
      MBHoldingRegister[1] = bitstatus01;
      
    }
 }
 //ENAble 
  if( MBHoldingRegister[2] !=bitstatus21)// || digitalRead(12) != bitstatus2)
 {
    digitalWrite(12, !digitalRead(12));
//    Serial.println(digitalRead(0));
    if(MBHoldingRegister[2] !=bitstatus21){
      
      bitstatus21 =  digitalRead(12);
      MBHoldingRegister[2] = bitstatus21;
      
    }
 }
  if( MBHoldingRegister[3] !=bitstatus41)// || digitalRead(12) != bitstatus2)
 {
    digitalWrite(14, !digitalRead(14));
//    Serial.println(digitalRead(0));
    if(MBHoldingRegister[3] !=bitstatus41){
      
      bitstatus41 =  digitalRead(14);
      MBHoldingRegister[3] = bitstatus41;
      
    }
 }
 
//// end code - fin 
 
 
 //// rutine Modbus TCP
 byteFN = ByteArray[MB_TCP_FUNC];
 Start = word(ByteArray[MB_TCP_REGISTER_START],ByteArray[MB_TCP_REGISTER_START+1]);
 WordDataLength = word(ByteArray[MB_TCP_REGISTER_NUMBER],ByteArray[MB_TCP_REGISTER_NUMBER+1]);
 }
 
 // Handle request
 
 switch(byteFN) {
 case MB_FC_NONE:
 break;
 
 case MB_FC_READ_REGISTERS: // 03 Read Holding Registers
 ByteDataLength = WordDataLength * 2;
 ByteArray[5] = ByteDataLength + 3; //Number of bytes after this one.
 ByteArray[8] = ByteDataLength; //Number of bytes after this one (or number of bytes of data).
 for(int i = 0; i < WordDataLength; i++)
 {
 ByteArray[ 9 + i * 2] = highByte(MBHoldingRegister[Start + i]);
 ByteArray[10 + i * 2] = lowByte(MBHoldingRegister[Start + i]);
 }
 MessageLength = ByteDataLength + 9;
 client.write((const uint8_t *)ByteArray,MessageLength);
 
 byteFN = MB_FC_NONE;
 
 break;
 
 
 case MB_FC_WRITE_REGISTER: // 06 Write Holding Register
 MBHoldingRegister[Start] = word(ByteArray[MB_TCP_REGISTER_NUMBER],ByteArray[MB_TCP_REGISTER_NUMBER+1]);
 ByteArray[5] = 6; //Number of bytes after this one.
 MessageLength = 12;
 client.write((const uint8_t *)ByteArray,MessageLength);
 byteFN = MB_FC_NONE;
 break;
 
 case MB_FC_WRITE_MULTIPLE_REGISTERS: //16 Write Holding Registers
 ByteDataLength = WordDataLength * 2;
 ByteArray[5] = ByteDataLength + 3; //Number of bytes after this one.
 for(int i = 0; i < WordDataLength; i++)
 {
 MBHoldingRegister[Start + i] = word(ByteArray[ 13 + i * 2],ByteArray[14 + i * 2]);
 }
 MessageLength = 12;
 client.write((const uint8_t *)ByteArray,MessageLength); 
 byteFN = MB_FC_NONE;
 
 break;
 }
 }
}

//==========================================================================================
void ICACHE_RAM_ATTR  battatcung13(void)
{
      digitalWrite(13, !digitalRead(13));
      bitstatus02 =   digitalRead(0);
      bitstatus01 = digitalRead(13);
      MBHoldingRegister[1] =  bitstatus01;
}
void ICACHE_RAM_ATTR  battatcung12(void)
{
      digitalWrite(12, !digitalRead(12));
      bitstatus22 =   digitalRead(2);
      bitstatus21 = digitalRead(12);
      MBHoldingRegister[2] =  bitstatus21;
}
void ICACHE_RAM_ATTR  battatcung14(void)
{
      digitalWrite(14, !digitalRead(14));
      bitstatus42 =   digitalRead(4);
      bitstatus41 = digitalRead(14);
      MBHoldingRegister[3] =  bitstatus41;
}

void configModeCallback (WiFiManager *myWiFiManager)
{
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}
