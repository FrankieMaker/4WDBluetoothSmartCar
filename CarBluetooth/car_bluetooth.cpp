#include "car_bluetooth.h"

CarBluetooth::CarBluetooth(int rx, int tx): bluetoothSerial(rx,tx){
  s_connecting = "CONNECTING";
  s_connected  = "CONNECTED";
  status = 0;
  bluetoothSerial.begin(9600);
}

void CarBluetooth::waitConnected(){
  char recvChar;
  while(status != CONNECTED){
    if(bluetoothSerial.available()){
      recvChar = bluetoothSerial.read();
	  if(recvChar == '+'){
	  	while(bluetoothSerial.available()< 10);
		String recvString;
	  	for(uint8_t i = 0; i < 10; i++){
			recvChar = bluetoothSerial.read();
			recvString += recvChar;
	  	}
		if(recvString == s_connecting) status = CONNECTING;
	  }
	  if(recvChar == 'C'){
	  	while(bluetoothSerial.available()< 8);
		String recvString;
		recvString += recvChar;
	  	for(uint8_t i = 0; i < 8; i++){
			recvChar = bluetoothSerial.read();
			recvString += recvChar;
	  	}
		if(recvString == s_connected) status = CONNECTED;
	  }	
    }
	else{
		if(testAT()) status = PAIRABLE;
		else{ 
			delay(200);
			if(testAT()) status = PAIRABLE;
			else status = CONNECTED;
		}
	} 
  }
}

void CarBluetooth::waitPairable(){
  char recvChar;
	while(status != PAIRABLE){
	  if(bluetoothSerial.available()){
		recvChar = bluetoothSerial.read();
		Serial.write(recvChar);
		if(recvChar == '+'){
		  while(bluetoothSerial.available() == 0);
		  recvChar = bluetoothSerial.read();
		  Serial.write(recvChar);
		  if(recvChar == 'R')continue;
		  else if(recvChar == 'P'){
		  	while(bluetoothSerial.available()< 7);
		    String recvString;
		    recvString += recvChar;
		    for(uint8_t i = 0; i < 7; i++){
			  recvChar = bluetoothSerial.read();
			  recvString += recvChar;
		    }
		  if(recvString == "PAIRABLE") status = PAIRABLE;
		  }
		}
	  }
	 else{
		if(testAT())status = PAIRABLE;
		else{ 
			delay(200);
			if(testAT()) status = PAIRABLE;
			else{ status = CONNECTED;break;}
		}
	} 
	}
}
bool CarBluetooth::rename(String name){
  clearBuffer();
  String renameCmd;
  renameCmd = "AT+NAME";
  renameCmd += name;
  return writeAT(renameCmd);
}

bool CarBluetooth::reset(){
  clearBuffer();
  return writeAT("AT+RESET");
 
}

/*Clear the receiver buffer of the bluetooth serial object*/
void CarBluetooth::clearBuffer(){
  char recvChar;
  while(bluetoothSerial.available())recvChar = bluetoothSerial.read();
}

/*Write AT command to bluetooth module*/
bool CarBluetooth::writeAT(String cmd){
  bluetoothSerial.println(cmd);
  delay(500);
  if(bluetoothSerial.available() > 1){
    String recvString;
	char recvChar;
	recvChar = bluetoothSerial.read();
    recvString += recvChar;
    recvChar = bluetoothSerial.read();
    recvString += recvChar;
    if(recvString == "OK")return true;
    else return false;
  }
  else return false;
}
bool CarBluetooth::testAT(){
  clearBuffer();
  return writeAT("AT");
}

/*Read command from remote control terminal such mobile phone*/
int8_t CarBluetooth::readCommand(){
  if(status != CONNECTED) return CTRL_INVALID;
  while(bluetoothSerial.available()< 3);
  char recvChar;
  int8_t cmd=0;
  while(bluetoothSerial.available()){
    recvChar = bluetoothSerial.read();
	if(recvChar == 0x30){
	  recvChar = bluetoothSerial.read();
	  switch(recvChar){
		case RAW_FORWARD:     cmd = CTRL_FORWARD; break;
		case RAW_RIGHT_FRONT: cmd = CTRL_RIGHT_FRONT; break;
		case RAW_RIGHT_REAR:  cmd = CTRL_RIGHT_REAR; break;
		case RAW_BACKWARD:    cmd = CTRL_BACKWARD; break;
		case RAW_LEFT_REAR:   cmd = CTRL_LEFT_REAR; break;
		case RAW_LEFT_FRONT:  cmd = CTRL_LEFT_FRONT; break;
		default:break;
      }
	  return cmd;
	}
	else if(recvChar == 0x50){
	  recvChar = bluetoothSerial.read();
	  switch(recvChar){
		case RAW_STOP:       cmd = CTRL_STOP; break;
		case RAW_Z_ROUTE:    cmd = CTRL_Z_ROUTE; break;
		case RAW_SPEED_UP:   cmd = CTRL_SPEED_UP; break;
		case RAW_SPEED_DOWN: cmd = CTRL_SPEED_DOWN; break;
		default:break;
	  }
	  return cmd;
	}
	else if(recvChar == '+'){//the remote control disconnect the car
	  waitPairable();
	  return CTRL_INVALID;
	}
	else return CTRL_INVALID;
  }
}
char CarBluetooth::readByte(){
  if(status != CONNECTED) return 0xff;
  if(bluetoothSerial.available())
  {
  	char recvChar;
	recvChar = bluetoothSerial.read();
  	if(recvChar == '+')//the remote control disconnect the car
	{  waitPairable();
		return 0xff;
  		}
  	else return recvChar;
  }
  else return 0xff;
}

int8_t CarBluetooth::getStatus(){
  return status;
}


