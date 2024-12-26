#ifndef BUTTONASSIGNMENTS_H
#define BUTTONASSIGNMENTS_H

//This file holds the button assignments for our esp32. Here is the pinout...

// For more info, check out this site...
// https://lastminuteengineers.com/esp32-pinout-reference/

/**   Here are the ESP32 Assignments that are constructed below...
*                EN      23 joyButton
*        joyX    36*     22 Sck
*        joyY    39*     1  -- If you use these, you cannot flash...
*        Pot1    34*     3  -- If you use these, you cannot flash...
*        Pot2    35*     21 Sda
*        mute2   32      19 buttonY
*        solo1   33      18 buttonB
*        rReady2 25      5$ ledPin
*        mute1   26      17 buttonA
*        solo2   27      16 buttonX
*        rReady1 14      4 pot3
*          Enc1B 12#     2^ 
*          Enc1A 13      15 pot4
*                Grnd    Grnd
*                Vin     3v3
*      *= Input Only #= Must be low during boot 
*     $=Must be high during boot ^= Linked to onboard led
*
*
*/

//Constants:
//Banks...
//Mute .... 
const int mute1 = 26;
const int mute2 = 32;

// Solo
const int solo1 = 33;
const int solo2 = 27;

const int rReady1 = 14;
const int rReady2 = 25;

//Potentiometers?
const int pot1 = 34;
const int pot2 = 35;

//Encoders
const int Enc1A = 13;
const int Enc1B = 12;

//Leds
const uint8_t ledBrightness = 10;
const uint8_t ledPin = 5;

//Joystick
const int joyX = 36;
const int joyY = 39;
const int joyButton = 23;


#endif