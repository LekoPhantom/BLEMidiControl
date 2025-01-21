#include <PinAssignments.h>
//#include <FastLED.h>

#include <Control_Surface.h> // Include the Control Surface library
//#include <Display/DisplayInterfaces/DisplayInterfaceSSD1306.hpp> // Include the display interface you'd like to use

#include <display.h>
#include <lights.h>

// ----------------------------- MIDI Interface ----------------------------- //
BluetoothMIDI_Interface midi;

//----------------------------------Output ---------------------------------- //

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

//Add a buffer to store the bank characters...
char buffer [33];

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

NoteValue mute3 {MCU::MUTE_3};

// --------------------------------- Setup ---------------------------------- //

void setup() {

    // Initialize Serial for debugging
  Serial.begin(115200);

  initializeLeds();
  
  RelativeCCSender::setMode(relativeCCmode::MACKIE_CONTROL_RELATIVE);
  
  Control_Surface.begin(); // Initialize Control Surface
  initializeDisplay();
}

// ---------------------------------- Loop ---------------------------------- //

void loop() {
  Control_Surface.loop(); // Refresh all elements
  updateDisplay(); // Update the display
  updateLeds();
}
