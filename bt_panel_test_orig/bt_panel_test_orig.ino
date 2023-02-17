//  Auto Generated Code for Arduino IDE
//  Created using keuwlsofts Bluetooth Electronics App
//  www.keuwl.com

//  Steps: 
//  1) Upload code and power your Arduino project 
//  2) Run Bluetooth Electronics App and connect to your device 
//  3) Press the reset button on your Arduino 

//  This auto generated code template is only a suggestion to get you started.
//  It is incomplete and will need modification specific to your project.

int update_interval=100; // time interval in ms for updating panel indicators 
unsigned long last_time=0; // time of last update
char data_in; // data received from serial link
#include <SoftwareSerial.h>
SoftwareSerial BT_SERIAL(D2, D3); // rx tx

void setup() {

  BT_SERIAL.begin(9600); //Change baud rate as required!

///////////// Build panel in app
delay(1000);
BT_SERIAL.println("*.kwl");
//BT_SERIAL.println("clear_panel()");
//BT_SERIAL.println("set_grid_size(16,8)");
//BT_SERIAL.println("add_text(7,1,xlarge,C,This panel was auto generated from the arduino!,83,240,92,)");
//BT_SERIAL.println("add_button(5,2,27,R,r)");
//BT_SERIAL.println("add_button(8,2,27,R,r)");
//BT_SERIAL.println("add_button(7,4,9,S,s)");
//BT_SERIAL.println("add_button(8,6,24,Z,z)");
//BT_SERIAL.println("add_button(6,6,24,Z,z)");
//BT_SERIAL.println("add_button(5,5,24,Z,z)");
//BT_SERIAL.println("add_button(9,5,24,Z,z)");
//BT_SERIAL.println("add_button(7,6,24,Z,z)");
//BT_SERIAL.println("set_panel_notes(-,,,)");
//BT_SERIAL.println("run()");
//BT_SERIAL.println("*");

}

void loop() {

  /////////////   Receive and Process Data

  if (BT_SERIAL.available()){
    data_in=BT_SERIAL.read();  //Get next character 

    if(data_in=='R'){ //Button Pressed
      //<--- Insert button pressed code here 
    }
    if(data_in=='r'){ // Button Released 
      //<--- Insert button released code here 
    }

    if(data_in=='R'){ //Button Pressed
      //<--- Insert button pressed code here 
    }
    if(data_in=='r'){ // Button Released 
      //<--- Insert button released code here 
    }

    if(data_in=='S'){ //Button Pressed
      //<--- Insert button pressed code here 
    }
    if(data_in=='s'){ // Button Released 
      //<--- Insert button released code here 
    }

    if(data_in=='Z'){ //Button Pressed
      //<--- Insert button pressed code here 
    }
    if(data_in=='z'){ // Button Released 
      //<--- Insert button released code here 
    }

    if(data_in=='Z'){ //Button Pressed
      //<--- Insert button pressed code here 
    }
    if(data_in=='z'){ // Button Released 
      //<--- Insert button released code here 
    }

    if(data_in=='Z'){ //Button Pressed
      //<--- Insert button pressed code here 
    }
    if(data_in=='z'){ // Button Released 
      //<--- Insert button released code here 
    }

    if(data_in=='Z'){ //Button Pressed
      //<--- Insert button pressed code here 
    }
    if(data_in=='z'){ // Button Released 
      //<--- Insert button released code here 
    }

    if(data_in=='Z'){ //Button Pressed
      //<--- Insert button pressed code here 
    }
    if(data_in=='z'){ // Button Released 
      //<--- Insert button released code here 
    }

  }

  /////////////  Send Data to Android device

  unsigned long t=millis();
  if ((t-last_time)>update_interval){
    last_time=t;

  }

}
