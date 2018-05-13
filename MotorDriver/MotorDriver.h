#ifndef __MOTORDRIVER_H__
#define __MOTORDRIVER_H__
#include <Arduino.h>
/******Pins definitions*************/

/**************Motor ID**********************/
#define MOTORA 			0
#define MOTORB 			1

#define MOTOR_POSITION_LEFT  0
#define MOTOR_POSITION_RIGHT 1
#define MOTOR_CLOCKWISE      0
#define MOTOR_ANTICLOCKWISE  1

#define USE_DC_MOTOR		0

struct MotorStruct
{
	int8_t speed;
	uint8_t direction;
	uint8_t position;
};
/**Class for Motor Shield**/
class MotorDriver
{
	MotorStruct motorA;
	MotorStruct motorB;
	uint8_t MOTORSHIELD_IN1,MOTORSHIELD_IN2,MOTORSHIELD_IN3,MOTORSHIELD_IN4;
	uint8_t SPEEDPIN_A,SPEEDPIN_B;
public:
	void init(uint8_t BIN1=8, uint8_t BIN2=11,uint8_t PWMB=9,uint8_t AIN1=12,uint8_t AIN2=13,uint8_t PWMA=10);
	void configure(uint8_t position, uint8_t motorID);
	void setSpeed(int8_t speed, uint8_t motorID);
	void setDirection(uint8_t direction, uint8_t motorID);
	void rotate(uint8_t direction, uint8_t motor_position);
	void rotateWithID(uint8_t direction, uint8_t motorID);
	void goForward();
	void goBackward();
	void goLeft();
	void goRight();
	void stop();
	void stop(uint8_t motorID);
};
extern MotorDriver motordriver;

#endif
