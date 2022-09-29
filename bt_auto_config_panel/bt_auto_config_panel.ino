/*
 *  ------ Guy Ostfeld
 * The motivation in this project is to create a library (or a snippet of simple to use code) that will make an arduino project easy to configure using
 * the "bluetooth electronics" android app
 * using the feature of remote code (in the app), I wish for the arduino to create automatically a configuration dashboard, 
 * with the desired variables and send it to the phone via bt.
 * 
 * e.g of usage:
 * CONFIGURABLE_INT(speed, 1500) // this macro should declare a var named speed, init it to 1500, and add it to the remote panel
 * setup_config_panel(); // in setup - is this really needed?
 * loop_config_panel(); // in loop - create the config panel code and send it to the phone every sec, also check for bt input, parse it and alter the vars accordingly.
 */



// the following is copied from the "bluetooth electronics" remote panel auto generated code.

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

void setup() {

  Serial.begin(9600); //Change baud rate as required!

///////////// Build panel in app

Serial.println("*.kwl");
Serial.println("clear_panel()");
Serial.println("set_grid_size(16,8)");
Serial.println("add_text(3,1,xlarge,L,My Robot - Configuration Page,190,147,245,)");
Serial.println("add_text(12,1,xlarge,L,1/5,245,240,150,)");
Serial.println("add_text(0,3,large,L,right motor  base speed,245,240,245,)");
Serial.println("add_text(8,3,large,L,blink interval,245,240,245,)");
Serial.println("add_text(0,4,large,L,Var2,245,240,245,)");
Serial.println("add_text(0,5,large,L,Var3,245,240,245,)");
Serial.println("add_text(0,6,large,L,Var4,245,240,245,)");
Serial.println("add_text(0,7,large,L,Var5,245,240,245,)");
Serial.println("add_text(8,4,large,L,Var7,245,240,245,)");
Serial.println("add_text(8,5,large,L,Var8,245,240,245,)");
Serial.println("add_text(8,6,large,L,Var9,245,240,245,)");
Serial.println("add_text(8,7,large,L,Var10,245,240,245,)");
Serial.println("add_button(2,1,5,R,r)");
Serial.println("add_button(1,1,4,L,l)");
Serial.println("add_send_box(13,4,3,,,)");
Serial.println("add_send_box(13,3,3,,,)");
Serial.println("add_send_box(5,4,3,,,)");
Serial.println("add_send_box(5,5,3,,,)");
Serial.println("add_send_box(5,6,3,,,)");
Serial.println("add_send_box(5,7,3,,,)");
Serial.println("add_send_box(13,5,3,,,)");
Serial.println("add_send_box(13,6,3,,,)");
Serial.println("add_send_box(13,7,3,,,)");
Serial.println("add_send_box(5,3,3,1500,@1:,$)");
Serial.println("set_panel_notes(-,,,)");
Serial.println("run()");
Serial.println("*");

}

void loop() {

  /////////////   Receive and Process Data

  if (Serial.available()){
    data_in=Serial.read();  //Get next character 

    if(data_in=='R'){ //Button Pressed
      //<--- Insert button pressed code here 
    }
    if(data_in=='r'){ // Button Released 
      //<--- Insert button released code here 
    }

    if(data_in=='L'){ //Button Pressed
      //<--- Insert button pressed code here 
    }
    if(data_in=='l'){ // Button Released 
      //<--- Insert button released code here 
    }

    // Receive Data from Terminal Send Box
      // Requires a start character for auto code to be generated 

    // Receive Data from Terminal Send Box
      // Requires a start character for auto code to be generated 

    // Receive Data from Terminal Send Box
      // Requires a start character for auto code to be generated 

    // Receive Data from Terminal Send Box
      // Requires a start character for auto code to be generated 

    // Receive Data from Terminal Send Box
      // Requires a start character for auto code to be generated 

    // Receive Data from Terminal Send Box
      // Requires a start character for auto code to be generated 

    // Receive Data from Terminal Send Box
      // Requires a start character for auto code to be generated 

    // Receive Data from Terminal Send Box
      // Requires a start character for auto code to be generated 

    // Receive Data from Terminal Send Box
      // Requires a start character for auto code to be generated 

    // Receive Data from Terminal Send Box
      // Unable to create auto code for start text longer than one character 

  }

  /////////////  Send Data to Android device

  unsigned long t=millis();
  if ((t-last_time)>update_interval){
    last_time=t;

  }

}
