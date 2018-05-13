//Demo for Ultrasonic Sensor and 4-Digit Display module
//by Catalex
//Demo Function: Use the Ultrasonic Sensor module to detect the distance and
//               display it on the 4-digit Display module
//Store: http://www.aliexpress.com/store/1199788
//      http://dx.com
#include <Ultrasonic.h>
#include "TM1637.h"
//module--- Arduino
//VCC   --- 5V
//GND   --- GND
#define TRIGGER_PIN  5//connect Trip of the Ultrasonic Sensor moudle to D5 of Arduino 
                      //and can be changed to other ports
#define ECHO_PIN     3
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

#define CLK A5//connect CLK of the 4-Digit Display to A5 of Arduino and can be changed to other ports    
#define DIO A4//
TM1637 disp(CLK,DIO);

void setup()
  {
   disp.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  disp.init();
  }

void loop()
  {
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();

  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  disp.display((int16_t)cmMsec);//in centimeters
  delay(500);
  }
