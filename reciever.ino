#include <XBee.h>
#include <string.h>
XBee xbee = XBee();
ZBRxResponse zbRx = ZBRxResponse();

void setup()
{
  Serial.begin(9600);
  xbee.begin(Serial);
}

void loop()
{
  xbee.readPacket();
   if (xbee.getResponse().isAvailable()) {
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
      xbee.getResponse().getZBRxResponse(zbRx);{
       //for (int i = 0; i < zbRx.getDataLength(); i++){ 
          // zbRx.getData(i),HEX;
        if (zbRx.getData()<=10 ){
         Serial.print("0");}
             
         Serial.print(zbRx.getData(0),HEX);
         Serial.print(zbRx.getData(1),HEX);
         Serial.print(zbRx.getData(2),HEX);
         Serial.println(zbRx.getData(3),HEX);
         Serial.print(zbRx.getData(4),HEX);
         Serial.print(zbRx.getData(5),HEX);
         Serial.print(zbRx.getData(6),HEX);
         Serial.println(zbRx.getData(7),HEX);
         Serial.print(zbRx.getData(8),HEX);
         Serial.print(zbRx.getData(9),HEX);
         Serial.print(zbRx.getData(10),HEX);
         Serial.println(zbRx.getData(11),HEX);
         Serial.print(zbRx.getData(12),HEX);
         Serial.print(zbRx.getData(13),HEX);
         Serial.print(zbRx.getData(14),HEX);
         Serial.println(zbRx.getData(15),HEX);
         Serial.print(zbRx.getData(16),HEX);
         Serial.print(zbRx.getData(17),HEX);
         Serial.print(zbRx.getData(18),HEX);
         Serial.print(zbRx.getData(19),HEX);
         Serial.print('\n');
         }
         delay(60000);}   }} 

    

    
    



