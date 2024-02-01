
#include <SPI.h>
#include <mcp2515.h>
#include "functions.h"
#include <Arduino.h>

int start_val0 = -1;
int start_val1 = -1;
bool counter;
int steer_flag =-1;  
int dif_angle =10;

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
}


void loop() {
   if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {


      String highByte_string = intToBinaryString(canMsg.data[1]);
      String lowByte_string = intToBinaryString(canMsg.data[0]);
      float angle = binaryBytesToInt(highByte_string, lowByte_string);


      counter = sign_func(counter); // counter switches betwenn 0 and 1 
      

      
      
      // identifz the steer_flag
      if (steer_flag == -1)
      {
         if (counter == 0 ) 
         {
            if (start_val0 == -1)      
            {
               start_val0 = angle;
               // Serial.print("Ich war hier!!!!!!");
               
            } else if ((start_val0 + dif_angle) < angle ) 
            {
               // Serial.print("Steering Wheeeel angle: ");
               // Serial.println(angle);
               // Serial.print("Flag ist 000000000000");
               steer_flag = 0 ;
            }
         }
         if (counter == 1 ) 
         {
            if (start_val1 ==-1) 
            {
               start_val1 = angle;
               // Serial.print("Ich war hier!!!!!!");
               

            } else if ((start_val1 + dif_angle) < angle ) 
            {
               // Serial.print("Steering whell angle: ");
               // Serial.println(angle);
               // Serial.print("Flag ist 111111111111111111111");
               steer_flag = 1 ;
            }
         }
      }
      
      // Serial.print(start_val0);
      // Serial.print("\n");
      // Serial.print(start_val1);
      // Serial.print("\n");

      // work with steer_flag
      if (steer_flag == 1 || steer_flag == 0)
      {
         if (counter == 0 && steer_flag == 0 || counter == 1 && steer_flag == 1)
         {
            Serial.print("Steering wheel angle: ");
            Serial.println(angle);
         } else //if (counter == 0 && steer_flag == 1 || counter == 0 && steer_flag == 1)
         {
            Serial.print("Shaft angle: ");
            Serial.println(angle);
         }
      }
      
      
      
      



      //print the angle in monitor 
      // Serial.print("  \nAngle ");
      // Serial.print(counter);
      // Serial.print(" : ");
      // Serial.print(angle);
      // Serial.print("   ");


      //send data to Matlab
      //writeToMatlab(angle);
      

      
   }
}

