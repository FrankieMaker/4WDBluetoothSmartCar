//  Demo function:The application method to drive the stepper motor.
//  Hareware:Stepper motor - 24BYJ48,Seeed's Motor Shield v2.0
//  Author:Frankie.Chu
//  Date:20 November, 2012
#define MOTOR_CLOCKWISE      0
#define MOTOR_ANTICLOCKWISE  1
/******Pins definitions*************/
#define MOTORSHIELD_IN1	8
#define MOTORSHIELD_IN2	11
#define MOTORSHIELD_IN3	12
#define MOTORSHIELD_IN4	13
#define CTRLPIN_A		9
#define CTRLPIN_B		10

const unsigned char stepper_ctrl[]={0x27,0x36,0x1e,0x0f};
struct MotorStruct
{
	int8_t speed;
	uint8_t direction;
};
MotorStruct stepperMotor;
unsigned int number_of_steps = 200;
/**********************************************************************/
/*Function: Get the stepper motor rotate                               */
/*Parameter:-int steps,the total steps and the direction the motor rotates.*/
/*			if steps > 0,rotates anticlockwise,			   			   */
/*			if steps < 0,rotates clockwise.           				   */
/*Return:	void                      							      */
void step(int steps)
{
	int steps_left = abs(steps)*4;
	int step_number;
	int millis_delay = 60L * 1000L /number_of_steps/(stepperMotor.speed + 50);
	if (steps > 0) 
	{
		stepperMotor.direction= MOTOR_ANTICLOCKWISE;
		step_number = 0; 
	}
    else if (steps < 0) 
	{
		stepperMotor.direction= MOTOR_CLOCKWISE;
		step_number = number_of_steps;
	}
	else return;
	while(steps_left > 0) 
	{
		PORTB = stepper_ctrl[step_number%4];
		delay(millis_delay);
		if(stepperMotor.direction== MOTOR_ANTICLOCKWISE)
		{
			step_number++;
		    if (step_number == number_of_steps)
		    	step_number = 0;
		}
		else 
		{
			step_number--;
		    if (step_number == 0)
		    	step_number = number_of_steps;
		}
		steps_left --;
		
	}
}
void initialize()
{
	pinMode(MOTORSHIELD_IN1,OUTPUT);
	pinMode(MOTORSHIELD_IN2,OUTPUT);
	pinMode(MOTORSHIELD_IN3,OUTPUT);
	pinMode(MOTORSHIELD_IN4,OUTPUT);
	pinMode(CTRLPIN_A,OUTPUT);
	pinMode(CTRLPIN_B,OUTPUT);
	stop();
	stepperMotor.speed = 25;
	stepperMotor.direction = MOTOR_CLOCKWISE;
}
/*******************************************/
void stop()
{
	/*Unenble the pin, to stop the motor. */
	digitalWrite(CTRLPIN_A,LOW);
    digitalWrite(CTRLPIN_B,LOW);
}

void setup()
{
	initialize();//Initialization for the stepper motor.
}

void loop()
{
	step(200);//Stepper motors rotate anticlockwise 200 steps.
	delay(1000);
	step(-200);//Stepper motors rotate clockwise 200 steps.
	delay(1000);
}
