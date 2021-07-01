#include <Wire.h>
#include <ADXL345.h>
#include <SimpleDHT.h>
#include <XBee.h>
#include <SoftwareSerial.h>
int pinDHT22 = 2;
SimpleDHT22 dht22(pinDHT22);

XBee xbee = XBee();
ADXL345 adxl;

uint8_t payload[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t a[20];
union u_tag {
 uint8_t b[4];
 float fval;
} u;

XBeeAddress64 addr64 = XBeeAddress64(0x000000000000FFFF);
ZBTxRequest zbTx = ZBTxRequest(addr64, a, sizeof(a));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

void setup() {
Serial.begin(9600);
xbee.begin(Serial);
delay(500);
adxl.powerOn();

}

void loop() {

Serial.println("=================================");
Serial.println("Sensor values...");
//Serial.println("values of X , Y , Z: ");    
float temperature = 0;
float humidity = 0;
int x,y,z; 
int err = SimpleDHTErrSuccess;
if ((err = dht22.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
Serial.print("Read DHT22 failed, err="); Serial.println(err);delay(2000);
return;
}
//Serial.println("Sample DHT22...");
Serial.print(temperature);
Serial.print(" *C, ");
Serial.print(humidity); 
Serial.println(" RH%");
 
adxl.readXYZ(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z
double xyz[3];
double ax,ay,az;
adxl.getAcceleration(xyz);
  ax = xyz[0];
  ay = xyz[1];
  az = xyz[2];
Serial.print("X="); Serial.print(ax); Serial.println(" g");
Serial.print("Y="); Serial.print(ay); Serial.println(" g");
Serial.print("Z="); Serial.print(az); Serial.println(" g");



float t = temperature;
float h = humidity;

   if (!isnan(t) && !isnan(h) && !isnan(ax) && !isnan(ay) && !isnan(az)) {
                   
                       u.fval = t;
                       for (int i=0;i<4;i++){
                       payload[i]=u.b[i];

                     {
                         a[0]= payload[3];
                         a[1]= payload[2];
                         a[2]= payload[1];
                         a[3]= payload[0];}}
                           
                    
                        u.fval = h;
                        for (int i=0;i<4;i++){
                        payload[i+4]=u.b[i];
                      
                        { a[4]= payload[7];
                          a[5]= payload[6];
                          a[6]= payload[5];
                          a[7]= payload[4];}}

                        u.fval = ax;
                        for (int i=0;i<4;i++){
                        payload[i+8]=u.b[i];
                        { a[8]= payload[11];
                          a[9]= payload[10];
                          a[10]= payload[9];
                          a[11]= payload[8];}}
                        
                        u.fval = ay;
                        for (int i=0;i<4;i++){
                        payload[i+12]=u.b[i];
                        { a[12]= payload[15];
                          a[13]= payload[14];
                          a[14]= payload[13];
                          a[15]= payload[12];}}
                       
                        u.fval = az;
                        for (int i=0;i<4;i++){
                        payload[i+16]=u.b[i];
                        { a[16]= payload[19];
                          a[17]= payload[18];
                          a[18]= payload[17];
                          a[19]= payload[16];}}}
                        
                    Serial.println(a[0],HEX);
                    Serial.println(a[1],HEX);
                    Serial.println(a[2],HEX);
                    Serial.println(a[3],HEX);
                    Serial.println(a[4],HEX);
                    Serial.println(a[5],HEX);
                    Serial.println(a[6],HEX);
                    Serial.println(a[7],HEX);
                    Serial.println(a[8],HEX);
                    Serial.println(a[9],HEX);
                    Serial.println(a[10],HEX);
                    Serial.println(a[11],HEX);
                    Serial.println(a[12],HEX);
                    Serial.println(a[13],HEX);
                    Serial.println(a[14],HEX);
                    Serial.println(a[15],HEX);
                    Serial.println(a[16],HEX);
                    Serial.println(a[17],HEX);
                    Serial.println(a[18],HEX);
                    Serial.println(a[19],HEX);



xbee.send(zbTx);
delay(5000);
}                  
