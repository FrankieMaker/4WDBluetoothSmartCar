//test 1:2015.08.15
#include <car_bluetooth.h>
#include <SoftwareSerial.h>   //Software Serial Port
#include <String.h>
#include "MotorDriver.h"

#define RxD 2
#define TxD 4
CarBluetooth bluetooth(RxD, TxD);
#define CMD_INVALID     0XFF
#define CMD_FORWARD     'F'
#define CMD_RIGHT_FRONT 'R'

#define CMD_BACKWARD    'B'

#define CMD_LEFT_FRONT  'L'
#define CMD_STOP        'S'

#define SPEED_STEPS 20
uint8_t speed0 = 100;
void setup(){
	Serial.begin(9600);
  motordriver.init();
  motordriver.setSpeed(100,MOTORA);
  motordriver.setSpeed(100,MOTORB);
  bluetooth.waitPairable();
  bluetooth.waitConnected();
}
uint8_t bt_command;

#define CAR_STOP 0
#define CAR_FORWARD 1
#define CAR_BACK 2
uint8_t car_status = CAR_STOP;
uint8_t new_status = car_status;

void loop(){
  bt_command = bluetooth.readByte();
  if(bt_command != CMD_INVALID){
  controlCar(bt_command);
  }
  if(bluetooth.getStatus() == PAIRABLE) {
  	motordriver.stop();
  	bluetooth.waitConnected();
  	}
}


void controlCar(uint8_t cmd){
   switch(cmd)
  {
    case CMD_FORWARD:     motordriver.goForward();break;
  case CMD_RIGHT_FRONT: 
  //  if(car_status != CAR_STOP)new_status = CAR_FORWARD;
    motordriver.goRight();
   // delay(200); 
    break;
  case CMD_BACKWARD:    motordriver.goBackward(); break;
  case CMD_LEFT_FRONT:  
    motordriver.goLeft();
   // delay(200);
    break;
  case CMD_STOP:        motordriver.stop();break;
  default: break;
  }
  if((cmd>='0')&&(cmd<='9'))
  {
  	speed0 = cmd-0x30;
	Serial.print(speed0);
	Serial.print(">");
	speed0 = map(speed0, 0, 9, 0, 255);
	Serial.println(speed0);
	motordriver.setSpeed(speed0,MOTORA);
    motordriver.setSpeed(speed0,MOTORB);
  }
}

void speedUp(){
  if(speed0 < 236)speed0 += SPEED_STEPS;
  else speed0 = 255;
  motordriver.setSpeed(speed0,MOTORA);
  motordriver.setSpeed(speed0,MOTORB);
}

void speedDown(){
  if(speed0 > 70)speed0 -= SPEED_STEPS;
  else speed0 = 50;
   motordriver.setSpeed(speed0,MOTORA);
  motordriver.setSpeed(speed0,MOTORB);
}

