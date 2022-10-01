/*
    ------ Guy Ostfeld
   The motivation in this project is to create a library (or a snippet of simple to use code) that will make an arduino project easy to configure using
   the "bluetooth electronics" android app
   using the feature of remote code (in the app), I wish for the arduino to create automatically a configuration dashboard,
   with the desired variables and send it to the phone via bt.
   note that this might be memory heavy since we are using a large amount of strings, preferably use arduino mega/esp8266/esp32.

   e.g of usage:
   CONFIGURABLE_INT(speed, 1500) // this macro should declare a var named speed, init it to 1500, and add it to the remote panel
   setup_config_panel(); // in setup - is this really needed?
   loop_config_panel(); // in loop - create the config panel code and send it to the phone every sec, also check for bt input, parse it and alter the vars accordingly.


   in the future, maybe add an option to save and load config to EEPROM.
*/

// ---------------------------------------------------------------------------------------------------
// The real magic section... using the macro CONFIGURABLE_INT to declare a variable (instead of int x), the macro first declares the int as the user intended and also
// creates an instance of the class MetaInt that saves a pointer to the variable and it's "description" which defaults to it's name.
// also store this MetaInt in a global static array MetaInt::mints for future use

#define CONCAT_(x,y) x##y // these two macros are needed to ensure transpilation, used later for creating unique names for instances of the class.
#define CONCAT(x,y) CONCAT_(x,y)
// use this to declare every variable that you want to be able to configure (e.g do "CONFIGURABLE_INT(baseSpeed, 1200)" instead of "int baseSpeed = 1200;")
// 2 steps to this macro, first declare and initialize the variable for the user, then create a class that saves the name and a pointer to that variable.
#define CONFIGURABLE_INT(var_name, value) int var_name = value; MetaInt CONCAT(MINT_, var_name) = MetaInt(&var_name, #var_name)

class MetaInt {
  public:
    static MetaInt* mints[1000]; // save all MetaInts created, use this later in the config panel.
    static int numMints;
    int* ptr;
    char* description;

    MetaInt(int* my_ptr, char* my_description) {
      ptr = my_ptr;
      description = my_description;
      mints[numMints] = this; // save this MetaInt in the global static array for future reference.

      // Increase every time MetaInt is created to keep count.
      MetaInt::numMints++;
    }
};

// still needs to initialize static variables
int MetaInt::numMints = 0;
MetaInt* MetaInt::mints[1000];

// ---------------------------------------------------------------------------------------------------

// --- Configurable variables area - save here all the variables in the code that you wish to be able to config
// currently supports only int type
// TODO: move this to another tab
CONFIGURABLE_INT(gridSizeX, 16);
CONFIGURABLE_INT(gridSizeY, 8);
CONFIGURABLE_INT(numOfVarsInEachColumn, 5);
CONFIGURABLE_INT(varTextBoxBasePosX, 0);
CONFIGURABLE_INT(varTextBoxBasePosY, 3);
CONFIGURABLE_INT(varSendBoxBasePosX, 5);
CONFIGURABLE_INT(varSendBoxBasePosY, 3);
CONFIGURABLE_INT(distanceBetweenVarTextBoxX, 8);
CONFIGURABLE_INT(distanceBetweenVarTextBoxY, 1);
CONFIGURABLE_INT(distanceBetweenVarSendBoxX, 8);
CONFIGURABLE_INT(distanceBetweenVarSendBoxY, 1);

// -----------------------------------------------------


void configPanelAddIntVar(int* varP, char* varName, int value) {
  Serial.println(varName);
  Serial.println(value);
}


#define BT_SERIAL Serial // TODO: probably use software serial later

char* mainTitle = "add_text(8,0,xlarge,C,BT Config Example - Configuration Page,190,147,245,)"; // TODO: change the "BT Config Example" with configurable program name.
char* navigationButtons = "add_button(2,1,5,R,r)\nadd_button(1,1,4,L,l)"; // TODO: change output
char* pageIndexText = "add_text(7,1,xlarge,L,1/5,245,240,150,)"; // TODO: change the numbers (1/5) according to the actual page index.
char varLayout[2000]; // this is the automatic part
char* panelNotes = "set_panel_notes(-,,,)";
char* runCommand = "run()";
char* clearPanelCmd = "clear_panel()";



void btConfigPanelSetup() { // TODO: get baud rate and grid size in params
  BT_SERIAL.begin(9600); //Change baud rate as required!
  BT_SERIAL.println("*.kwl"); // what is this??? do we need this in loop?
  BT_SERIAL.println(clearPanelCmd);
  char out[100];
  sprintf(out, "set_grid_size(%d,%d)", gridSizeX, gridSizeY);
  BT_SERIAL.println(out);
}

void sendPanelLayout() {
  char finalPanel[1000];
  sprintf(finalPanel, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n*\n", clearPanelCmd, mainTitle, navigationButtons, pageIndexText, varLayout, panelNotes, runCommand);
  BT_SERIAL.print(finalPanel);
}

void prepareVariableLayout() {
  int varLayoutStringIndex = 0;
  // TODO: start index and end index according to page index
  for (int i = 0; i < MetaInt::numMints && i < numOfVarsInEachColumn * 2; i++) { // iterate over all configurable variables
    // for the first 5 vars, put the text in column 0 and rows 3,4,5,6,7, for the next 5 vars, column 8 and rows 3,4,5,6,7
    int textPosX = i < numOfVarsInEachColumn ? varTextBoxBasePosX : varTextBoxBasePosX + distanceBetweenVarTextBoxX;
    int textPosY = varTextBoxBasePosY + ((i % numOfVarsInEachColumn) * distanceBetweenVarTextBoxY);
    int sendBoxPosX = i < numOfVarsInEachColumn ? varSendBoxBasePosX : varSendBoxBasePosX + distanceBetweenVarSendBoxX;
    int sendBoxPosY = varSendBoxBasePosY + ((i % numOfVarsInEachColumn) * distanceBetweenVarSendBoxY);
    int textLen = sprintf(varLayout + varLayoutStringIndex, "add_text(%d,%d,large,L,%s,245,240,245,)\nadd_send_box(%d,%d,3,%d,@%d:,$)\n",
                          textPosX, textPosY, MetaInt::mints[i]->description,
                          sendBoxPosX, sendBoxPosY, *MetaInt::mints[i]->ptr, i);
    varLayoutStringIndex += textLen;
  }
  varLayout[varLayoutStringIndex] = '\0'; // EOF
}



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

int update_interval = 100; // time interval in ms for updating panel indicators
unsigned long last_time = 0; // time of last update
char data_in; // data received from BT_SERIAL link



void setup() {

  btConfigPanelSetup(); // WIP
  prepareVariableLayout();
  sendPanelLayout(); // WIP
  //  for (int i = 0; i < MetaInt::numMints; i++) { // print all configurable variables (test)
  //    Serial.print(i);
  //    Serial.print(" - var_name: ");
  //    Serial.println(MetaInt::mints[i]->description);
  //    Serial.print("   value: ");
  //    Serial.println(*MetaInt::mints[i]->ptr);
  //  }






  ///////////// Build panel in app
  /*
    BT_SERIAL.println("*.kwl");
    BT_SERIAL.println("clear_panel()");
    BT_SERIAL.println("set_grid_size(16,8)");

    BT_SERIAL.println("add_text(3,1,xlarge,L,My Robot - Configuration Page,190,147,245,)");
    BT_SERIAL.println("add_text(12,1,xlarge,L,1/5,245,240,150,)");
    BT_SERIAL.println("add_text(0,3,large,L,right motor  base speed,245,240,245,)");
    BT_SERIAL.println("add_text(8,3,large,L,blink interval,245,240,245,)");
    BT_SERIAL.println("add_text(0,4,large,L,Var2,245,240,245,)");
    BT_SERIAL.println("add_text(0,5,large,L,Var3,245,240,245,)");
    BT_SERIAL.println("add_text(0,6,large,L,Var4,245,240,245,)");
    BT_SERIAL.println("add_text(0,7,large,L,Var5,245,240,245,)");
    BT_SERIAL.println("add_text(8,4,large,L,Var7,245,240,245,)");
    BT_SERIAL.println("add_text(8,5,large,L,Var8,245,240,245,)");
    BT_SERIAL.println("add_text(8,6,large,L,Var9,245,240,245,)");
    BT_SERIAL.println("add_text(8,7,large,L,Var10,245,240,245,)");
    BT_SERIAL.println("add_button(2,1,5,R,r)");
    BT_SERIAL.println("add_button(1,1,4,L,l)");
    BT_SERIAL.println("add_send_box(13,4,3,,,)");
    BT_SERIAL.println("add_send_box(13,3,3,,,)");
    BT_SERIAL.println("add_send_box(5,4,3,,,)");
    BT_SERIAL.println("add_send_box(5,5,3,,,)");
    BT_SERIAL.println("add_send_box(5,6,3,,,)");
    BT_SERIAL.println("add_send_box(5,7,3,,,)");
    BT_SERIAL.println("add_send_box(13,5,3,,,)");
    BT_SERIAL.println("add_send_box(13,6,3,,,)");
    BT_SERIAL.println("add_send_box(13,7,3,,,)");
    BT_SERIAL.println("add_send_box(5,3,3,1500,@1:,$)");
    BT_SERIAL.println("set_panel_notes(-,,,)");
    BT_SERIAL.println("run()");
    BT_SERIAL.println("*");
  */
}

void loop() {

  /////////////   Receive and Process Data
  /*
    if (BT_SERIAL.available()) {
      data_in = BT_SERIAL.read(); //Get next character

      if (data_in == 'R') { //Button Pressed
        //<--- Insert button pressed code here
      }
      if (data_in == 'r') { // Button Released
        //<--- Insert button released code here
      }

      if (data_in == 'L') { //Button Pressed
        //<--- Insert button pressed code here
      }
      if (data_in == 'l') { // Button Released
        //<--- Insert button released code here
      }
    }*/

  /////////////  Send Data to Android device

  unsigned long t = millis();
  if ((t - last_time) > update_interval) {
    last_time = t;

  }
  delay(1);
}
