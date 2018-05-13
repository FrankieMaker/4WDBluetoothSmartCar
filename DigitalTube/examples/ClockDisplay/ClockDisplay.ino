//Demo for 4-Digit Display or 4-Digit Display(D4056B) by Catalex
//Hardware: A 4-Digit Display or 4-Digit Display(D4056B) 
//Board: Catduino or Arduino UNO R3,Arduino Mega2560...
//IDE:   Arduino-1.0
//Function: Display the time on the digital tube.
//Store: http://www.aliexpress.com/store/1199788
//      http://dx.com
/*********************************************************************/
#include <TimerOne.h>
#include "TM1637.h"
#define ON 1
#define OFF 0

int8_t TimeDisp[] = {0x00,0x00,0x00,0x00};
unsigned char ClockPoint = 1;
unsigned char Update;
unsigned char halfsecond = 0;
unsigned char second;
unsigned char minute = 0;
unsigned char hour = 12;


#define CLK A5//connect CLK of the 4-Digit Display to A5 of Arduino and can be changed to other ports    
#define DIO A4//
TM1637 display(CLK,DIO);

void setup()
{
  display.set();
  display.init();
  Timer1.initialize(500000);//timing for 500ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR  
}
void loop()
{
  if(Update == ON)
  {
    TimeUpdate();
    display.display(TimeDisp);
  }
  
}
void TimingISR()
{
  halfsecond ++;
  Update = ON;
  if(halfsecond == 2){
    second ++;
    if(second == 60)
    {
      minute ++;
      if(minute == 60)
      {
        hour ++;
        if(hour == 24)hour = 0;
        minute = 0;
      }
      second = 0;
    }
    halfsecond = 0;  
  }
 // Serial.println(second);
  ClockPoint = (~ClockPoint) & 0x01;
}
void TimeUpdate(void)
{
  if(ClockPoint)display.point(POINT_ON);
  else display.point(POINT_OFF); 
  TimeDisp[0] = hour / 10;
  TimeDisp[1] = hour % 10;
  TimeDisp[2] = minute / 10;
  TimeDisp[3] = minute % 10;
  Update = OFF;
}
