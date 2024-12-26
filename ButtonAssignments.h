#ifndef BUTTONASSIGNMENTS_H
#define BUTTONASSIGNMENTS_H

//This file holds the button assignments for our esp32. Here is the pinout...

// For more info, check out this site...
// https://lastminuteengineers.com/esp32-pinout-reference/

/**
*                EN      23
* Input Only --  36      22
* Input Only --  39      1  -- If you use these, you cannot flash...
* Input Only --  34      3  -- If you use these, you cannot flash...
* Input Only --  35      21
*                32      19
*                33      18
*                25      5  -- Must be HIGH during boot
*                26      17 
*                27      16
*                14      4
*low during boot 12      2
*                13      15
*                Grnd    Grnd
*                Vin     3v3
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