#include <hardwareserial.h>
#include "LedController.hpp"

//-----------------------------------------------------------------
// Define the pins connected to the MAX7219
#define DIN 23
#define CS  22
#define CS2 21
#define CLK 18
//Create two max7219 
LedController<1,1> LR;  //LEFT and RIGHT
LedController<1,1> UD;  //UP AND DOWN
//create counter for LR and UD
int cnt1=0;
int cnt2=0;

//-----------------------------------------------------------------
HardwareSerial MySerial(2);

#define RxPin          16
#define TxPin          17       //define для rs485
#define BAUDRATE       9600
#define SER_BUF_SIZE   1024
//----------------------------------------------------------------
#define BTNL  35               // кнопка лево
#define BTNR  34               // кнопка право
#define BTNU  33               // кнопка вверх
#define BTND  32               // кнопка вниз
#define BTNS  27               // кнопка старт
#define JOYL  26               // джойстик в лево
#define JOYR  25               // джойстик в право
#define JOYU  14               // джойстик вверх
#define JOYD  12               // джойстик вниз
#define DT   100               // задержка от дребезга
void debonce(int i);
//-----------------------------------------------------------------
#define DIRV  0                // DIREC VERT
#define STH   2                // STEP HORIZ
#define DIRH  4                // DIRECT_HORIZ
#define ENH   9                // ENABLE_HORIZ          ВЫХОДА
#define STV   10               // STEP_VERT
#define ENV   11               // ENABLE_VERT
#define PWP  15               // PWM_PUSK
#define ON    1
#define OFF   0
//-----------------------------------------------------------------
void setup() {
  gpio_Init();
  Serial.begin(9600);
  MySerial.setRxBufferSize(SER_BUF_SIZE);
  MySerial.begin(BAUDRATE, SERIAL_8N1, RxPin, TxPin);
  //------------------------------------------------------------
  LR=LedController<1,1>(DIN,CLK,CS);
  LR.setIntensity(5); /* Set the brightness to a medium values */
  LR.clearMatrix(); /* and clear the display */
 //**************************************************************/
  UD=LedController<1,1>(DIN,CLK,CS2);
  UD.setIntensity(5); /* Set the brightness to a medium values */
  UD.clearMatrix(); /* and clear the display */
}
void loop() {
    char RxData;
    while(MySerial.available())
    {
     RxData = MySerial.read();
     if (RxData == '0') {
      
    }
    if (RxData == '1') {
      
    }
    
    }
    delay(100);
    
}

void leftOneStep(){
  if(BTNL == LOW){
     debonce(DT);
     if(BTNL == LOW){
      digitalWrite(DIRH,ON);
      digitalWrite(STH,ON);
      digitalWrite(ENH,ON);
     }
  }
}

void debonce(int i){
     delay(i);
}
// Function to display a number on a 4-digit 7-segment display
void displayNumber1(int num) {
  // Extract each digit from the number
  int tenmillion = (num / 10000000) % 10;
  int million = (num / 1000000) % 10;
  int onehundredthousand = (num / 100000) % 10;     //6
  int tensthousands = (num / 10000) %10;            //5
  int thousands = (num / 1000) % 10;                //4
  int hundreds = (num / 100) % 10;                  //3
  int tens = (num / 10) % 10;                       //2
  int units = num % 10;                             //1

  // Display each digit on the 7-segment display
  LR.setDigit(0, 7, tenmillion, false);
  LR.setDigit(0, 6, million, false);
  LR.setDigit(0, 5, onehundredthousand, false);
  LR.setDigit(0, 4, tensthousands, false);
  LR.setDigit(0, 3, thousands, false);  // Most significant digit (thousands)
  LR.setDigit(0, 2, hundreds, false);
  LR.setDigit(0, 1, tens, false);
  LR.setDigit(0, 0, units, false);      // Least significant digit (units)
}

/*********************************************************************/
void displayNumber2(int num) {
  // Extract each digit from the number
  int tenmillion = (num / 10000000) % 10;
  int million = (num / 1000000) % 10;
  int onehundredthousand = (num / 100000) % 10;     //6
  int tensthousands = (num / 10000) %10;           //5
  int thousands = (num / 1000) % 10;                //4
  int hundreds = (num / 100) % 10;                  //3
  int tens = (num / 10) % 10;                       //2
  int units = num % 10;                             //1

  // Display each digit on the 7-segment display
  UD.setDigit(0, 7, tenmillion, false);
  UD.setDigit(0, 6, million, false);
  UD.setDigit(0, 5, onehundredthousand, false);
  UD.setDigit(0, 4, tensthousands, false);
  UD.setDigit(0, 3, thousands, false);  // Most significant digit (thousands)
  UD.setDigit(0, 2, hundreds, false);
  UD.setDigit(0, 1, tens, false);
  UD.setDigit(0, 0, units, false);      // Least significant digit (units)
}

void gpio_Init(){
  pinMode(DIRV,OUTPUT);
  pinMode(STH,OUTPUT);
  pinMode(DIRH,OUTPUT);
  pinMode(ENH,OUTPUT);
  pinMode(STV,OUTPUT);
  pinMode(ENV,OUTPUT);
  pinMode(PWP,OUTPUT);
  digitalWrite(DIRV,OFF);
  digitalWrite(STV,OFF);
  digitalWrite(ENV,OFF);
  digitalWrite(DIRH,OFF);
  digitalWrite(ENH,OFF);
  digitalWrite(STH,OFF);
  digitalWrite(PWP,OFF);
  //-----------------------
  pinMode(BTNL,INPUT);
  pinMode(BTNR,INPUT);
  pinMode(BTNU,INPUT);
  pinMode(BTND,INPUT);
  pinMode(BTNS,INPUT);
  pinMode(JOYL,INPUT);
  pinMode(JOYR,INPUT);
  pinMode(JOYU,INPUT);
  pinMode(JOYD,INPUT);
}