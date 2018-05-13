#ifndef _CAR_BLUETOOTH_H
#define _CAR_BLUETOOTH_H

#include <SoftwareSerial.h>   //Software Serial Port
#include <String.h>
#include <Arduino.h>


//status macro
#define INITIALIZING 0
#define READY        1
#define INQUIRING    2
#define PAIRABLE     3
#define CONNECTING   4
#define CONNECTED    5

//Remote control code macro
#define CTRL_INVALID     0
#define CTRL_FORWARD     1
#define CTRL_RIGHT_FRONT 2
#define CTRL_RIGHT_REAR  3
#define CTRL_BACKWARD    4
#define CTRL_LEFT_REAR   5
#define CTRL_LEFT_FRONT  6
#define CTRL_STOP        7
#define CTRL_Z_ROUTE     8
#define CTRL_SPEED_UP    9
#define CTRL_SPEED_DOWN  10

//the middle one of raw code sent by the remote control teminal
#define RAW_FORWARD     1
#define RAW_RIGHT_FRONT 4
#define RAW_RIGHT_REAR  6
#define RAW_BACKWARD    2
#define RAW_LEFT_REAR   5
#define RAW_LEFT_FRONT  3

#define RAW_STOP        4//the 'O' Shape button on the left side of the software GUI
#define RAW_Z_ROUTE     5
#define RAW_SPEED_UP    1
#define RAW_SPEED_DOWN  2


//the commands that the bluetooth module get from remote control system such as andoid phone

class CarBluetooth
{
  private:
    SoftwareSerial bluetoothSerial;
	int8_t status;
	String s_connecting;
    String s_connected;
  public:
  	CarBluetooth(int rx, int tx);
	void waitConnected();
	void waitPairable();
	bool rename(String name);
	bool reset();
	void clearBuffer();
	bool writeAT(String cmd);
	bool testAT();
	int8_t readCommand();
	char readByte();
	int8_t getStatus();
	
};

#endif
