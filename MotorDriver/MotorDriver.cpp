//  Author:Frankie.Chu
//  Date:20 November, 2012
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//  Modified record:
//
/*******************************************************************************/
#include "MotorDriver.h"

void MotorDriver::init(uint8_t BIN1, uint8_t BIN2,uint8_t PWMB,uint8_t AIN1,uint8_t AIN2,uint8_t PWMA)
{
    MOTORSHIELD_IN1=BIN1;
    MOTORSHIELD_IN2=BIN2;
    MOTORSHIELD_IN3=AIN1;
    MOTORSHIELD_IN4=AIN2;
    SPEEDPIN_A	=PWMB;
    SPEEDPIN_B	=PWMA;
	pinMode(MOTORSHIELD_IN1,OUTPUT);
	pinMode(MOTORSHIELD_IN2,OUTPUT);
	pinMode(MOTORSHIELD_IN3,OUTPUT);
	pinMode(MOTORSHIELD_IN4,OUTPUT);
	pinMode(SPEEDPIN_A,OUTPUT);
	pinMode(SPEEDPIN_B,OUTPUT);
	stop();
	/*Configure the motor A to control the wheel at the left side.*/
	configure(MOTOR_POSITION_LEFT,MOTORA);
	/*Configure the motor B to control the wheel at the right side.*/
	configure(MOTOR_POSITION_RIGHT,MOTORB);
	setSpeed(127,MOTORA);
	setSpeed(127,MOTORB);
	setDirection(MOTOR_ANTICLOCKWISE,MOTORA);
	setDirection(MOTOR_CLOCKWISE,MOTORB);
}
void MotorDriver::configure(uint8_t position, uint8_t motorID)
{
	if(motorID == MOTORA)motorA.position = position;
	else motorB.position = position;
}

void MotorDriver::setSpeed(int8_t speed, uint8_t motorID)
{
	if(motorID == MOTORA) motorA.speed = speed;
	else if(motorID == MOTORB) motorB.speed = speed;
}
void MotorDriver::setDirection(uint8_t direction, uint8_t motorID)
{
	if(motorID == MOTORA)motorA.direction= direction;
	else if(motorID == MOTORB)motorB.direction = direction;
}
/**********************************************************************/
/*Function: Get the motor rotate                                  	  */
/*Parameter:-uint8_t direction,Clockwise or anticlockwise;            */
/*          -uint8_t motor_position,MOTOR_POSITION_LEFT or			  */
/*			MOTOR_POSITION_RIGHT;                      				  */
/*Return:	void                      							      */
void MotorDriver::rotate(uint8_t direction, uint8_t motor_position)
{
	if(motor_position == motorA.position)
	{
		rotateWithID(direction,MOTORA);
	}
	if(motor_position == motorB.position)
	{
		rotateWithID(direction,MOTORB);
	}
}
/**********************************************************************/
/*Function: Get the motor rotate                                  	  */
/*Parameter:-uint8_t direction,Clockwise or anticlockwise;            */
/*          -uint8_t motor_position,MOTORA or MOTORB				  */
/*Return:	void                      							      */
void MotorDriver::rotateWithID(uint8_t direction, uint8_t motorID)
{
	uint8_t in1_level,in2_level;
	if(MOTOR_CLOCKWISE == direction)
	{
		in1_level = LOW;
		in2_level = HIGH;
	}
	else 
	{
		in1_level = HIGH;
		in2_level = LOW;
	}
	if(motorID == MOTORA)
	{
		analogWrite(SPEEDPIN_A,motorA.speed);
		digitalWrite(MOTORSHIELD_IN1,in1_level);
     	digitalWrite(MOTORSHIELD_IN2,in2_level);
	}
	else if(motorID == MOTORB)
	{
		analogWrite(SPEEDPIN_B,motorB.speed);
		digitalWrite(MOTORSHIELD_IN3,in1_level);
     	digitalWrite(MOTORSHIELD_IN4,in2_level);
	}
}

void MotorDriver::goForward()
{
	rotate(MOTOR_ANTICLOCKWISE,MOTOR_POSITION_LEFT);
	rotate(MOTOR_CLOCKWISE,MOTOR_POSITION_RIGHT);
}
void MotorDriver::goBackward()
{
	rotate(MOTOR_ANTICLOCKWISE,MOTOR_POSITION_RIGHT);
	rotate(MOTOR_CLOCKWISE,MOTOR_POSITION_LEFT);
}
void MotorDriver::goLeft()
{
	rotate(MOTOR_CLOCKWISE,MOTOR_POSITION_RIGHT);
	rotate(MOTOR_CLOCKWISE,MOTOR_POSITION_LEFT);
}
void MotorDriver::goRight()
{
	rotate(MOTOR_ANTICLOCKWISE,MOTOR_POSITION_RIGHT);
	rotate(MOTOR_ANTICLOCKWISE,MOTOR_POSITION_LEFT);
}

/*************************************************************/
void MotorDriver::stop()
{
	/*Unenble the pin, to stop the motor. */
	digitalWrite(SPEEDPIN_A,LOW);
    digitalWrite(SPEEDPIN_B,LOW);
}

/*************************************************************/
void MotorDriver::stop(uint8_t motorID)
{
	if(motorID == MOTORA)digitalWrite(SPEEDPIN_A,LOW);
	else if(motorID == MOTORB)digitalWrite(SPEEDPIN_B,LOW);
}

MotorDriver motordriver;
