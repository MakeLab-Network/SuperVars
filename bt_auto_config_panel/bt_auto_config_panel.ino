/*
    ------ ConfigBee (config (with) bluetooth electronics easily) - by Guy Ostfeld
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

void printMints() { // test mints
  for (int i = 0; i < MetaInt::numMints; i++) { // print all configurable variables (test)
    Serial.print(i);
    Serial.print(" - var_name: ");
    Serial.println(MetaInt::mints[i]->description);
    Serial.print("   value: ");
    Serial.println(*MetaInt::mints[i]->ptr);
  }
}

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
CONFIGURABLE_INT(sendBtPanelIntervalMS, 10000);
CONFIGURABLE_INT(numOfColoumnsInVarLayout, 2);

#define CONFIG_BEE_VAR_INPUT_MAGIC_CHAR '@'
#define CONFIG_BEE_BUTTONS_MAGIC_CHAR '!'
#define PAGE_INDEX_RIGHT_BUTTON_MAGIC 'R'
#define PAGE_INDEX_LEFT_BUTTON_MAGIC 'L'
int varPageIndex = 0;
int totalVarPagesNum = 1;
// -----------------------------------------------------

unsigned long sendBtPanelTime = 0;
char data_in; // data received from BT_SERIAL link
#define BT_SERIAL Serial // TODO: probably use software serial later


// ----------------------------------------------------- commands
char* mainTitle = "add_text(8,0,xlarge,C,ConfigBee - Configuration Page,190,147,245,)"; // TODO: change the "BT Config Example" with configurable program name.
char* navigationButtons = "add_button(2,1,5,,CONCAT(CONFIG_BEE_BUTTONS_MAGIC_CHARR,PAGE_INDEX_RIGHT_BUTTON_MAGIC))\nadd_button(1,1,4,,CONCAT(CONFIG_BEE_BUTTONS_MAGIC_CHAR,PAGE_INDEX_LEFT_BUTTON_MAGIC))";
char* pageIndexText = "add_text(7,1,xlarge,L,%d/%d,245,240,150,)"; // TODO: change the numbers (1/5) according to the actual page index.
char varLayout[2000]; // this is the automatic part
char* panelNotes = "set_panel_notes(-,,,)";
char* runCommand = "run()";
char* clearPanelCmd = "clear_panel()";

// -----------------------------------------------------





// -----------------------------------------------------






void setup() {
  configBeeSetup();
  //  printMints(); // for test
}

void loop() {
  configBeeLoop();

  delay(1);
}
