/* 
*   Please consider this code as a basis for evolution, this is not a clean or final code.
*   And is not careful as strong code.
*   For these reasons the code can be optimized and made robust, but that's not 
*   the purpose of this video.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VFD_in 8
#define VFD_clk 9
#define VFD_stb 10 //Data can be input when this signal goes low.  When it goes high, command processing is performed.
#define VFD_oe 11 // Normal running at HIGH value

//IMPORTANT: The most significant bit (MSB) is sent first, therefore the creation of binary values ​​is reversed!
//Of course, we can reverse both sending functions!

void uPD16431_init(void){
  unsigned char i;
  delay(300); //power_up delay
  //
  digitalWrite(VFD_stb, HIGH);
  cmd_with_stb(0b10000000); // 
  delay(10);
}
void cmd_with_stb(unsigned char a){
  // send with stb
  unsigned char data = 170; //value to transmit, binary 10101010
  unsigned char mask = 0b00000001; //our bitmask
  data=a;
  digitalWrite(VFD_stb, HIGH);
  delayMicroseconds(4);//This delay here is very important!!!
  //This send the strobe signal
  //Note: The first byte input at in after the STB go LOW is interpreted as a command!!!
  digitalWrite(VFD_stb, LOW);
  delayMicroseconds(2);//This delay here is very important!!!
         for (mask = 0b00000001; mask > 0; mask <<= 1) { //iterate through bit mask
          digitalWrite(VFD_clk, LOW);
          delayMicroseconds(1);
                   if (data & mask){ // if bitwise AND resolves to true
                      digitalWrite(VFD_in, HIGH);
                   }
                   else{ //if bitwise and resolves to false
                     digitalWrite(VFD_in, LOW);
                   }
          delayMicroseconds(1);         
          digitalWrite(VFD_clk, HIGH);
          delayMicroseconds(1);
         }
   delayMicroseconds(2);      
   digitalWrite(VFD_stb, LOW);
}
void cmd_without_stb(unsigned char a){
  // send without stb
  unsigned char data = 170; //value to transmit, binary 10101010
  unsigned char mask = 1; //our bitmask
  data=a;
  //This don't send the strobe signal, to be used in burst data send
   for (mask = 0b00000001; mask>0; mask <<= 1) { //iterate through bit mask
     digitalWrite(VFD_clk, LOW);
     delayMicroseconds(3);
     if (data & mask){ // if bitwise AND resolves to true
        digitalWrite(VFD_in, HIGH);
     }
     else{ //if bitwise and resolves to false
       digitalWrite(VFD_in, LOW);
     }
    delayMicroseconds(3);
    digitalWrite(VFD_clk, HIGH);
    delayMicroseconds(3);
   }
}
void sendBlock(){
  for(uint8_t i = 0; i < 3; i++){
    all_off();
    switch (i){
      case 0:  cmd_with_stb(0b00100001); break;
      case 1:  cmd_with_stb(0b00110001); break;
      case 2:  cmd_with_stb(0b00101001); break;
      case 3:  cmd_with_stb(0b00111001); break;
    } 
  cmd_without_stb(0b11111111);//0
  cmd_without_stb(0b11111111);//1
  cmd_without_stb(0b11111111);//2
  cmd_without_stb(0b11111111);//3
  cmd_without_stb(0b11111111);//4
  cmd_without_stb(0b11111111);//5
  cmd_without_stb(0b11111111);//6
  digitalWrite(VFD_stb, HIGH);
  delay(1000);
  }
}
void all_off(){
  //I make use of a block indicater more one digit from 0:7, like 0 0:7, 1 0:7...m 0:7
  // direction: LSB...MSB
  cmd_with_stb(0b00100001); // Block 00
  delayMicroseconds(1);
  cmd_without_stb(0b00000000);//0
  cmd_without_stb(0b00000000);//1
  cmd_without_stb(0b00000000);//2
  cmd_without_stb(0b00000000);//3
  cmd_without_stb(0b00000000);//4
  cmd_without_stb(0b00000000);//5
  cmd_without_stb(0b00000000);//6
  digitalWrite(VFD_stb, HIGH);
  delayMicroseconds(1);

  cmd_with_stb(0b00110001); // Block 01
  delayMicroseconds(1);
  cmd_without_stb(0b00000000);//a
  cmd_without_stb(0b00000000);//b
  cmd_without_stb(0b00000000);//c
  cmd_without_stb(0b00000000);//d
  cmd_without_stb(0b00000000);//e
  cmd_without_stb(0b00000000);//f
  cmd_without_stb(0b00000000);//g 
  digitalWrite(VFD_stb, HIGH);
  delayMicroseconds(1);

  cmd_with_stb(0b00101001); // Block 10
  delayMicroseconds(1);
  cmd_without_stb(0b00000000);//h PTY
  cmd_without_stb(0b00000000);//i
  cmd_without_stb(0b00000000);//j
  cmd_without_stb(0b00000000);//k
  cmd_without_stb(0b00000000);//l
  cmd_without_stb(0b00000000);//m
  cmd_without_stb(0b00000000);
  digitalWrite(VFD_stb, HIGH);
  delayMicroseconds(1);

  cmd_with_stb(0b00111001); // Block 11
  delayMicroseconds(1);
  cmd_without_stb(0b00000000);
  cmd_without_stb(0b00000000);
  cmd_without_stb(0b00000000);
  cmd_without_stb(0b00000000);
  cmd_without_stb(0b00000000);
  cmd_without_stb(0b00000000);
  cmd_without_stb(0b00000000);
  digitalWrite(VFD_stb, HIGH);
  
  cmd_with_stb(0b00100001); //Because in the command I let display status Off, here I turn it ON.
  digitalWrite(VFD_stb, HIGH);
}
void all_on(){
  // direction: LSB...MSB
  cmd_with_stb(0b00100001); // Block 00
  delayMicroseconds(2);
  cmd_without_stb(0b11111111);//0
  cmd_without_stb(0b11111111);//1
  cmd_without_stb(0b11111111);//2
  cmd_without_stb(0b11111111);//3
  cmd_without_stb(0b11111111);//4
  cmd_without_stb(0b11111111);//5
  cmd_without_stb(0b11111111);//6
  digitalWrite(VFD_stb, HIGH);
  
  cmd_with_stb(0b00110001); // Block 01
  cmd_without_stb(0b11111111);//a
  cmd_without_stb(0b11111111);//b
  cmd_without_stb(0b11111111);//c
  cmd_without_stb(0b11111111);//d
  cmd_without_stb(0b11111111);//e
  cmd_without_stb(0b11111111);//f
  cmd_without_stb(0b11111111);//g seg parts of digite at right
  digitalWrite(VFD_stb, HIGH);

  cmd_with_stb(0b00101001); // Block 10
  cmd_without_stb(0b11111111);//h PTY
  cmd_without_stb(0b11111111);//i
  cmd_without_stb(0b11111111);//j
  cmd_without_stb(0b11111111);//k
  cmd_without_stb(0b11111111);//l
  cmd_without_stb(0b11111111);//m
  cmd_without_stb(0b11111111);
  digitalWrite(VFD_stb, HIGH);

  cmd_with_stb(0b00111001); // Block 11
  cmd_without_stb(0b11111111);
  cmd_without_stb(0b11111111);
  cmd_without_stb(0b11111111);
  cmd_without_stb(0b11111111);
  cmd_without_stb(0b11111111);
  cmd_without_stb(0b11111111);
  cmd_without_stb(0b11111111);
  digitalWrite(VFD_stb, HIGH);
}
void msgHiFolks(){
  // direction: LSB...MSB
  cmd_with_stb(0b00100001); //
  delayMicroseconds(1);
  cmd_without_stb(0b00011000);//0
  cmd_without_stb(0b00100010);//1
  cmd_without_stb(0b00000100);//2
  cmd_without_stb(0b00000000);//3
  cmd_without_stb(0b00001010);//4
  cmd_without_stb(0b00000000);//5
  cmd_without_stb(0b00000000);//6
  digitalWrite(VFD_stb, HIGH);
  delayMicroseconds(1);

  cmd_with_stb(0b00110001); //
  delayMicroseconds(1);
  cmd_without_stb(0b01000000);//a
  cmd_without_stb(0b00011000);//b
  cmd_without_stb(0b01000110);//c
  cmd_without_stb(0b00001101);//d
  cmd_without_stb(0b11001000);//e
  cmd_without_stb(0b00000110);//f
  cmd_without_stb(0b00000000);//g 
  digitalWrite(VFD_stb, HIGH);
  delayMicroseconds(1);

  cmd_with_stb(0b00101001); //
  delayMicroseconds(1);
  cmd_without_stb(0b10100000);//h PTY
  cmd_without_stb(0b00010010);//i
  cmd_without_stb(0b01010110);//j
  cmd_without_stb(0b00001010);//k
  cmd_without_stb(0b01001000);//l
  cmd_without_stb(0b00000100);//m
  cmd_without_stb(0b00000000);
  digitalWrite(VFD_stb, HIGH);
  delayMicroseconds(1);

  cmd_with_stb(0b00111001); //
  delayMicroseconds(1);
  cmd_without_stb(0b00000000);
  cmd_without_stb(0b00000000);
  cmd_without_stb(0b00000000);
  cmd_without_stb(0b00000000);
  cmd_without_stb(0b00000000);
  cmd_without_stb(0b00000000);
  cmd_without_stb(0b00000000);
  digitalWrite(VFD_stb, HIGH);
  
  cmd_with_stb(0b00100001); //Because in the command I send display status equal to OFF, here I turn it ON.
  digitalWrite(VFD_stb, HIGH);
}
void readKeys(){
  // Pay attenntion to the Pin: 8. This is the pin will be used as INPUT-PULLUP comming from Arduino
  uint8_t val = 0x00;       // variable to store the read value
  uint8_t data = 0x00;
  uint8_t array[9] = {0,0,0,0,0,0,0,0};
  uint8_t mask = 0x00; //our bitmask

  digitalWrite(VFD_stb, HIGH);
  cmd_with_stb(0b10100001); //Set to read keys 
    //digitalWrite(VFD_clk, HIGH); //This line is importante because the clk go from LOW to HIGH! Reverse from write data to out.
    pinMode(8, INPUT_PULLUP);  // Important this point! Here I'm changing the direction of the pin to INPUT data.
    delayMicroseconds(2);
          for (int8_t z = 0; z <= 3; z++){
                        for (int8_t h = 8; h >0; h--) {
                            digitalWrite(VFD_clk, HIGH);  // Remember wich the read data happen when the clk go from HIGH to LOW! Reverse from write data to out.
                            delayMicroseconds(2);
                            val = digitalRead(8);
                                if (val){ // if bitwise AND resolves to true
                                  array[h] = 1;
                                }
                                else{ //if bitwise and resolves to false
                                array[h] = 0;
                                }
                          digitalWrite(VFD_clk, LOW);
                          delayMicroseconds(2);
                        } 
                Serial.print(z);
                Serial.print(" - ");
                          
                      for (uint8_t bits = 8 ; bits > 0; bits--) {
                          Serial.print(array[bits]);
                      }
                            if ((z==1) && (array[1] == 1)){
                                  
                            }
                            if ((z==1) && (array[2] == 1)){
                                
                            }
                            if ((z==1) && (array[3] == 1)){
                                
                            }
                            if ((z==1) && (array[4] == 1)){
                                
                              
                            }
                            if((z==1) && (array[5] == 1)){
                                
                            }
                            if((z==1) && (array[6] == 1)){
                              
                            }
                            if((z==1) && (array[7] == 1)){
                              //Not used yet.
                            }        
                    Serial.println();
            }  // End of "for" of "z"
        Serial.println();

  digitalWrite(VFD_stb, HIGH);
  delayMicroseconds(2);
  pinMode(8, OUTPUT);  // Important this point!  // Important this point! Here I'm changing the direction of the pin to OUTPUT data.
  delay(2); 
}
void tstSegment(){
  uint32_t segBit = 0x00000001;
  uint8_t wordLowA = 0x00;
  uint8_t wordLowB = 0x00;
  uint8_t wordLowC = 0x00;
  uint8_t wordLowD = 0x00;
  uint8_t wordHighA = 0x00;
  uint8_t wordHighB = 0x00;
  uint8_t wordHighC = 0x00;
  uint8_t wordHighD = 0x00;
  uint8_t cycle = 0;
  //
  for(uint8_t h = 0; h < 2; h++){
    segBit = 0x00000001; //Initialise variable of bit position segment.
      for(uint8_t i = 0; i < 32; i++){
        segBit = segBit << 1;
          if (h == 0){
              wordLowA = ((segBit >> 0)  & 0x000000FF);
              wordLowB = ((segBit >> 8)  & 0x000000FF);
              wordLowC = ((segBit >> 16)  & 0x000000FF);
              wordLowD = ((segBit >> 24)  & 0x000000FF);
          }
          else{
              wordHighA = ((segBit >> 0)  & 0x000000FF);
              wordHighB = ((segBit >> 8)  & 0x000000FF);
              wordHighC = ((segBit >> 16)  & 0x000000FF);
              wordHighD = ((segBit >> 24)  & 0x000000FF); //Only use 7 bytes, this is not used!
          }
        //
      for(uint8_t s = 0; s < 3; s++){ //Cycle used to set the block to be send!
        all_off();
        switch (s){
          case 0:  cmd_with_stb(0b00100001); break; //Block 00
          case 1:  cmd_with_stb(0b00110001); break; //Block 01
          case 2:  cmd_with_stb(0b00101001); break; //Block 10
          case 3:  cmd_with_stb(0b00111001); break; //Block 11
      } 
      cmd_without_stb(wordLowA);//0
      cmd_without_stb(wordLowB);//1
      cmd_without_stb(wordLowC);//2
      cmd_without_stb(wordLowD);//3
      cmd_without_stb(wordHighA);//4
      cmd_without_stb(wordHighB);//5
      cmd_without_stb(wordHighC);//6
      digitalWrite(VFD_stb, HIGH);
      // Serial.print("AL: ");
      // Serial.println(wordLowA, BIN);
      // Serial.print("BL: ");
      // Serial.println(wordLowB, BIN);
      // Serial.print("CL: ");
      // Serial.println(wordLowC, BIN);
      // Serial.print("DL: ");
      // Serial.println(wordLowD, BIN);
      // Serial.println(segBit, BIN);
      delay(250);
      }
    }
  }
}
void setup() {
  Serial.begin(115200);

  pinMode(VFD_in, OUTPUT);
  pinMode(VFD_clk, OUTPUT);
  pinMode(VFD_stb, OUTPUT);
  pinMode(VFD_oe, OUTPUT);
 
  digitalWrite(VFD_oe, LOW);
  delay(20);
  digitalWrite(VFD_oe, HIGH);
  // delay(100); //Only to protect the action of OE time!

  uPD16431_init();
}
void loop(){ 
  for(uint8_t i = 0; i < 5; i++){
      all_on();
      delay(1500);
      all_off();
      delay(1500);
    }
   sendBlock();
   delay(1000);
   all_off();
   delay(1500);
   all_off();
   delay(1000);
  //  readKeys(); //Uncommment it if want read keys!
  //  delay(500);
  msgHiFolks();
  delay(1500);
  tstSegment();
}
