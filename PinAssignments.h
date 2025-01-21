#ifndef PINASSIGNMENTS_H
#define PINASSIGNMENTS_H

//This file holds the button assignments for our esp32. Here is the pinout...

// For more info, check out this site...
// https://lastminuteengineers.com/esp32-pinout-reference/

/**   Here are the ESP32 Assignments that are constructed below...
*                 EN      23 Solo1
*        MainFad  36*     22 Sck
*        Chan1Fad 39*     1  -- If you use these, you cannot flash...
*        JoyX     34*     3  -- If you use these, you cannot flash...
*        JoyY     35*     21 Sda
*        incMin   32      19 Mute1
*        incP     33      18 Select1
*          Up     25      5$ ledPin
*        Down     26      17 Option
*        Stop     27      16 
*        Play     14      4  Enc1A
*        Record   12#     2^ Marker
*        rReady1  13      15 Enc1B
*                 Gnd     Gnd
*                 Vin     3v3
*      *= Input Only 
*      #= Must be low during boot 
*      $=Must be high during boot 
*      ^= Linked to onboard led

*       Arduino Nano....
*               1    ...     Vin (square)
*               2    ...     GND  
*               3            28
*               GND          5v
*               5 D2      A7 26  
*               6 D3      A6 25
*               7 D4      A5 24
*               8 D5      A4 23
*               9 D6      A3 22
*               10 D7     A2 21
*               11 D8     A1 20
*               12 D9     A0 19
*               13 D10   Ref 18
*               14 D11    3.3v
*               15 D12   D13 16
*/


//Constants:
//Banks...
//Mute .... 
const int mute1Pin = 19;

// Solo
const int solo1Pin = 23;

//Record Ready
const int rReady1Pin = 13;

//Select
const int select1Pin = 18;

//Faders
const int chan1FaderPin = 39;

//Pots



//Leds
const int ledBrightness = 5;
const int ledPin = 5;
const int totalNumberLeds = 30;

//Bank Select
const int incMinPin = 32;
const int incPPin = 33;

//Mains...

//JogWheel
const int jogPinA = 4;
const int jogPinB = 15;


//buttons and faders
const int markerPin = 2;
const int recordPin = 12;
const int playPin = 14;
const int optionPin = 17;
const int upPin = 25;
const int downPin = 26;
const int stopPin = 27;
const int mainFaderPin = 36;

//Joystick
const int joyXPin = 34;
const int joyYPin = 35;
//const int joyButton = 2;

#endif