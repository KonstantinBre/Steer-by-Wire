
#include <SPI.h>
#include <mcp2515.h>
#include "functions.h"

int counter=0;
int sensor_number;
int currentIndex;

const int buffer_length = 150;
const int columns =2;
int buffer[columns][buffer_length];
const int amount_counter = buffer_length*2;


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


      
      

      if (counter < amount_counter)
      {
         if (isEven(counter))
         {
            //even
            sensor_number = 0;
            currentIndex = counter/2;
            buffer[sensor_number][currentIndex] = angle;

         } else
         {
            //odd
            sensor_number = 1;
            currentIndex = (counter-1)/2;
            buffer[sensor_number][currentIndex] = angle;
         }

         //print the angle in monitor 
         Serial.print("  Angle ");
         Serial.print(sensor_number);
         Serial.print(" : ");
         Serial.print(angle);
         Serial.print("   ");
         Serial.print(counter);
         Serial.print("\n");

         //send data to Matlab
         //writeToMatlab(angle);
      }
      else{

         // Serial.print("Counter above 1000, starting ");

       
         // Serial.print("First buffer in range ? True=1 False =0   :");
         // Serial.print(check_all_numb_of_arr_in_range(buffer[0]));

        
         if (check_all_numb_of_arr_in_range(buffer[0]) == check_all_numb_of_arr_in_range(buffer[1]))
         {
            Serial.print("ERRRRRRRRRRRRRRRRROOOOOOOORRRRRRRRRR");
         }
         
               
         if (isEven(counter))
         {
            if (check_all_numb_of_arr_in_range(buffer[0])==true)
            {
               Serial.print("Steering wheel sensor:  ");
               Serial.print(angle);
               Serial.print("\n");
            }
            else
            {
               if (check_all_numb_of_arr_in_range(buffer[0])==false)
               {
                  Serial.print("Steering wheel sensor:  ");
                  Serial.print(angle);
                  Serial.print("\n");
               }
            } 
         }     
         
      }
      
      counter+=1;
      
   }
}

