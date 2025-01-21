
/**
*   This file lays out the objects and associated logic with the Operator Interaction. 
*   Anything the operator touches will be here with the exception of the objects that are handled by external processors.
*/

//----------------------------------Instatiate the Midi Output Elements---------------------------------- //

//If you would like to use an element that is displayed, you can add that to the display.cpp file.

#include <Control_Surface.h> // Include the Control Surface library
#include <PinAssignments.h>

CCRotaryEncoder enc {
  {Enc1A,Enc1B},                                // pins
  MCU::JOG_WHEEL, // address
  5,                       // multiplier
  4,                                     // pulses per click
};

//Instantiate the banks...

Bank<4> bank(1); // A bank with 2 channels, and 4 bank settings

// Selector to change banks
IncrementDecrementSelector<4> selector {bank, {26, 36}};



Bankable::NoteButton mute_switches[] {
  {{bank, BankType::ChangeAddress}, mute1 , {MCU::MUTE_1}},
};

// Solo
Bankable::NoteButton solo_switches[] { 
  {{bank, BankType::ChangeAddress}, solo1, {MCU::SOLO_1}},
  
};

Bankable::NoteButton rec_switches[] {
  {{bank, BankType::ChangeAddress}, rReady1, {MCU::REC_RDY_1}},
};
//Potentiometers?
using  PBSmartPot = Bankable::PBSmartPotentiometer<4>;

// Instantiate a CCPotentiometer object
PBSmartPot potentiometer1 {
  {bank, BankType::ChangeChannel},      // Bank configuration
  34,                                   // Analog pin connected to potentiometer
   Channel_1, // Channel volume of channel 1
};

// Instantiate a CCPotentiometer object
PBSmartPot potentiometer2 {
  {bank, BankType::ChangeChannel},      // Bank configuration
  35,                                   // Analog pin connected to potentiometer
   Channel_2,                           // Channel volume of channel 1
};