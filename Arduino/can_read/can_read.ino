
#include <SPI.h>
#include <mcp2515.h>
#include "functions.h"


struct can_frame canMsg;
MCP2515 mcp2515(53);  //depends on the baord: uno or mega!

int angle = 0;
String angle_s;


uint16_t combineBytes(byte high, byte low) {
   return (static_cast<uint16_t>(high) << 8) | low; }


void setup() {
   Serial.begin(115200);

   mcp2515.reset();
   mcp2515.setBitrate(CAN_500KBPS);  //Important for com!
   mcp2515.setNormalMode();

   //Serial.println("------- CAN Read ----------");
   //Serial.println("ID  DLC   DATA");
}

void loop() {
   if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
     //Serial.print(canMsg.can_id, DEC); // print ID
     //Serial.print(" ");
    //  Serial.print(canMsg.can_dlc, HEX); // print DLC
    //  Serial.print("   ");
    //  for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
    //    Serial.print(canMsg.data[i],BIN);
    //    Serial.print(" ");
    //  }

     angle_s = canMsg.data[0] + canMsg.data[1];
     byte data = canMsg.data[1];
     String data_string = intToBinaryString(data);


     String highByte_string =intToBinaryString(canMsg.data[1]);
     String lowByte_string =intToBinaryString(canMsg.data[0]);

     float angle = binaryBytesToInt(highByte_string, lowByte_string);

      // print ID
      Serial.print(canMsg.can_id, DEC); 
      Serial.print(" ");

      //print the angle in monitor 
      Serial.print("  Angle: ");
      Serial.print(angle);
      //Serial.write(angle);
      Serial.print("  ");

      //raw Byte data
      Serial.print(highByte_string + lowByte_string);
      Serial.println();

      //send data to Matlab
      //writeToMatlab(angle);
   }
}
