#include "MIDI_Constants/MCU.hpp"

/**
*   This file lays out the objects and associated logic with the Operator Interaction. 
*   Anything the operator touches will be here with the exception of the objects that are handled by external processors.
*/

//----------------------------------Instatiate the Midi Output Elements---------------------------------- //

//If you would like to use an element that is displayed, you can add that to the display.cpp file.

#include <Control_Surface.h> // Include the Control Surface library
#include <PinAssignments.h>



//----------------------------------Instatiate the Banks---------------------------------- //
Bank<4> bank(1); // A bank with 2 channels, and 4 bank settings

// Selector to change banks
IncrementDecrementSelector<4> selector {bank, {incPPin, incMinPin}};



Bankable::NoteButton mute_switches[] {
  {{bank, BankType::ChangeAddress}, mute1Pin , {MCU::MUTE_1}},
};

// Solo
Bankable::NoteButton solo_switches[] { 
  {{bank, BankType::ChangeAddress}, solo1Pin, {MCU::SOLO_1}},
  
};

Bankable::NoteButton rec_switches[] {
  {{bank, BankType::ChangeAddress}, rReady1Pin, {MCU::REC_RDY_1}},
};

Bankable::NoteButton select_switches[] {
  {{bank, BankType::ChangeAddress}, rReady1Pin, {MCU::REC_RDY_1}},
};
//Potentiometers?
using  PBSmartPot = Bankable::PBSmartPotentiometer<4>;

// Instantiate a CCPotentiometer object
PBSmartPot ChanFader {
  {bank, BankType::ChangeChannel},      // Bank configuration
  chan1FaderPin,                                   // Analog pin connected to potentiometer
   Channel_1, // Channel volume of channel 1
};

//----------------------------------Instatiate the Mains---------------------------------- //

// Instantiate a CCButton object
CCButton marker {
  markerPin, //Pin
  {MCU::MARKER}, //MCU Controller (You can use general MIDICC or raw value as well...)
};

CCButton record {
  recordPin, //Pin
  {MCU::RECORD},//MCU Controller (You can use general MIDICC or raw value as well...)
};

CCButton play {
  playPin, //Pin
  {MCU::PLAY},//MCU Controller (You can use general MIDICC or raw value as well...)
};

CCButton option {
  optionPin, //Pin
  {MCU::OPTION},//MCU Controller (You can use general MIDICC or raw value as well...)
};

CCButton up {
  upPin, //Pin
  {MCU::UP},//MCU Controller (You can use general MIDICC or raw value as well...)
};

CCButton down {
  downPin, //Pin
  {MCU::DOWN},//MCU Controller (You can use general MIDICC or raw value as well...)
};

CCButton stop {
  stopPin, //Pin
  {MCU::STOP},//MCU Controller (You can use general MIDICC or raw value as well...)
};

//JogWheel
CCRotaryEncoder enc {
  {jogPinA,jogPinB}, // pins
  MCU::JOG_WHEEL, // address
  5,              // multiplier
  4,              // pulses per click
};
// Instantiate a PBPotentiometer object
PBPotentiometer mainFader {
  mainFaderPin,        // Analog pin connected to potentiometer
  {MCU::MASTER_VOLUME}, // Main Volume
};

// Joystick? 

