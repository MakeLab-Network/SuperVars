void superVarsSetup() { // the single thing you need to put in setup.
  int numVarsInPage = numOfVarsInEachColumn * numOfColoumnsInVarLayout;
  totalVarPagesNum = (MetaInt::numMints / numVarsInPage) + 1;
  btConfigPanelSetup();
  prepareVariableLayout();
  sendPanelLayout();
}

void btConfigPanelSetup() { // TODO: get baud rate and grid size in params
  BT_SERIAL.begin(9600); //Change baud rate as required!
  BT_SERIAL.println("*.kwl"); // what is this??? do we need this in loop?
  BT_SERIAL.println(clearPanelCmd);
  char out[100];
  sprintf(out, "set_grid_size(%d,%d)", gridSizeX, gridSizeY);
  BT_SERIAL.println(out);
}

void superVarsLoop() { // the single thing you need to put in the main loop
  handleBtInput();
  if (millis() > sendBtPanelTime) { // if the time is right, send the panel layout to the phone
    sendPanelLayout();
    sendBtPanelTime = millis() + sendBtPanelIntervalMS; // set the timer again.
  }
}

void prepareVariableLayout() {
  int varLayoutStringIndex = 0;
  // TODO: start index and end index according to page index
  int numVarsInPage = numOfVarsInEachColumn * numOfColoumnsInVarLayout;
  for (int i = varPageIndex * numVarsInPage; i < MetaInt::numMints && i < (varPageIndex + 1) * numVarsInPage; i++) { // iterate over all configurable variables
    // for the first 5 vars, put the text in column 0 and rows 3,4,5,6,7, for the next 5 vars, column 8 and rows 3,4,5,6,7
    int textPosX = i < numOfVarsInEachColumn ? varTextBoxBasePosX : varTextBoxBasePosX + distanceBetweenVarTextBoxX;
    int textPosY = varTextBoxBasePosY + ((i % numOfVarsInEachColumn) * distanceBetweenVarTextBoxY);
    int sendBoxPosX = i < numOfVarsInEachColumn ? varSendBoxBasePosX : varSendBoxBasePosX + distanceBetweenVarSendBoxX;
    int sendBoxPosY = varSendBoxBasePosY + ((i % numOfVarsInEachColumn) * distanceBetweenVarSendBoxY);
    int textLen = sprintf(varLayout + varLayoutStringIndex, "add_text(%d,%d,large,L,%s,245,240,245,)\nadd_send_box(%d,%d,3,%d,SUPER_VARS_VAR_INPUT_MAGIC_CHAR%d:,$)\n",
                          textPosX, textPosY, MetaInt::mints[i]->description,
                          sendBoxPosX, sendBoxPosY, *MetaInt::mints[i]->ptr, i);
    varLayoutStringIndex += textLen;
  }
  varLayout[varLayoutStringIndex] = '\0'; // EOF
}

void sendPanelLayout() {
  char finalPanel[1000];
  sprintf(pageIndexText, pageIndexText, varPageIndex, totalVarPagesNum); // update page index text according to the actual page index.
  sprintf(finalPanel, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n*\n", clearPanelCmd, mainTitle, navigationButtons, pageIndexText, varLayout, panelNotes, runCommand);
  BT_SERIAL.print(finalPanel);
}

void handleBtInput() {
  if (BT_SERIAL.available()) {
    data_in = BT_SERIAL.read(); // Get next character
    if (data_in == SUPER_VARS_VAR_INPUT_MAGIC_CHAR) { // this is a variable update message
      int varIndex = BT_SERIAL.parseInt(); // which var was updated?
      data_in = BT_SERIAL.read(); // Get next character
      if (data_in == ':') { // expecting separator between var_index and var_value
        int varValue = BT_SERIAL.parseInt(); // the new var value // TODO: check return value, did we really get an int
        data_in = BT_SERIAL.read(); // Get next character
        if (data_in == '$') { // expecting EOL as part of the format
          // got a valid message, update the var
          if (varIndex >= 0 && varIndex < MetaInt::numMints) {
            *MetaInt::mints[varIndex]->ptr = varValue; // update the correct variable value
            Serial.print("updated var: ");
            Serial.print(MetaInt::mints[varIndex]->description);
            Serial.print(" new value: ");
            Serial.println(*MetaInt::mints[varIndex]->ptr);
          }
        }
      }
    }
    if (data_in == SUPER_VARS_BUTTONS_MAGIC_CHAR) { // A Button was pressed
      // TODO: check which button and handle it
      data_in = BT_SERIAL.read(); // Get next character
      switch (data_in) {
        case PAGE_INDEX_RIGHT_BUTTON_MAGIC: {
            varPageIndex = varPageIndex < totalVarPagesNum ? varPageIndex + 1 : 1;
            break;
          }
        case PAGE_INDEX_LEFT_BUTTON_MAGIC: {
            varPageIndex = varPageIndex > 1 ? varPageIndex - 1 : totalVarPagesNum;
            break;
          }
      }
    }
  }
}
