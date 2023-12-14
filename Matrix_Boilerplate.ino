// Adafruit Protomatter matrix driver 
// Boilerplate code for raspberry Pico(W)
// This include ezTime library,
//              Wifi library,
//              Scrolling message library
//
// By Gary Metheringham (C) DEC 2023
// With thanks to OldSkoolCoder for the Scrolling message
// library.

//===>   MQuick Setup   <=====//
#include <Arduino_JSON.h>
#include "Secret.h"
#include "HWSetups/1_QuickSetupMatrix.h"
#include "HWSetups/2_Scrolling_Messages.h"
#include "HWSetups/QuickSetupWIFI.h"
#include "HWSetups/QuickSetupTime.h"

//=====> Project  <=======//


void setup()
{
    Serial.begin(115200);

    // Initialize matrix...
    Matrix_Setup();

    // Attempt to connect to Wifi network:
    WIFI_Setup();

    // setup ezTime
    EZtime_Setup();

    // Get a random seed from millis(), now as wifi
    // don't always take same time to connect
    randomSeed(millis());

    // Wait for any text from setup to be read
    delay(1000);

    // Scroll any messages sent during setup (Must be constanty called)
    Scrolling = 1;
    while(Scrolling)
        performTextScrolling();
    // Ensure screen cleared ready for main program
    matrix.fillScreen(myBLACK);
    matrix.show();


    

    //========>  END OF QUICK SETUP  <==============//
    //=====>  Your Setup code goes here  <==========//



    //========> End of Your Setup code  <===========//
}

void loop()
{

}