#include <FastLED.h>
#include <Control_Surface.h> // Include the Control Surface library


// ----------------------------- MIDI Interface ----------------------------- //
BluetoothMIDI_Interface midi;

//----------------------------- NEOPIXEL Interface ----------------------------- //
// Define the array of LEDs.
Array<CRGB, 25> leds {}; //25 allows for two rings and one light

//Setup some buttons...

//Pin Constants....
//----------------------------- Transport Pins ----------------------------- //
//uint playPin = 12;
//uint recordPin = 39;
//uint rewindPin = 27;
//uint fastForwardPin = 33;
uint stopPin = 32;
//----------------------------- Main Bus Pins ----------------------------- //
/**
uint optionPin = 14;
uint muteAllPin = 32;
uint upPin = 40; //Not patched
uint downPin = 35;
uint leftPin = 33;
uint rightPin = 39;

uint mainEncoderPinA = 12;
uint mainEncoderPinB = 14;
*/

//----------------------------- Transport Buttons ----------------------------- //
NoteButton stop {
  stopPin,                             // Push button on pin 5
  {MCU::STOP}, // Note C4 on MIDI channel 1
};
// Instantiate a NoteButton object
/**NoteButton record {
  recordPin,                             // Push button on pin 5
  {MCU::RECORD}, // Note C4 on MIDI channel 1
};

// Instantiate a NoteButton object
NoteButton fastForward {
  fastForwardPin,                             // Push button on pin 5
  {MCU::FAST_FWD}, // Note C4 on MIDI channel 1
};
NoteButton stop {
  stopPin,                             // Push button on pin 5
  {MCU::STOP}, // Note C4 on MIDI channel 1
};
*/

//----------------------------- Mains Bus ----------------------------- //
/**
NoteButton option {
  optionPin,                             // Push button on pin 5
  {MCU::OPTION}, // Note C4 on MIDI channel 1
};

NoteButton muteAll {
  muteAllPinPin,                             // Push button on pin 5
  {MCU::MUTE}, // Note C4 on MIDI channel 1
};

NoteButton up {
  upPin,                             // Push button on pin 5
  {MCU::UP}, // Note C4 on MIDI channel 1
};

NoteButton down {
  downPin,                             // Push button on pin 5
  {MCU::DOWN}, // Note C4 on MIDI channel 1
};

NoteButton left {
  leftPin,                             // Push button on pin 5
  {MCU::LEFT}, // Note C4 on MIDI channel 1
};

NoteButton right {
  rightPin,                             // Push button on pin 5
  {MCU::RIGHT}, // Note C4 on MIDI channel 1
};

//----------------------------- Neopixel Assignments? ----------------------------- //
//Rude solo
NoteValue rudeSolo {MCU::RUDE_SOLO};
*/
void setup() {

      // Initialize Serial for debugging
  Serial.begin(115200);
  Control_Surface.begin(); // Initialize Control Surface
}

void loop() {
  // put your main code here, to run repeatedly:
  Control_Surface.loop(); // Refresh all elements
  //if(rudeSolo.getDirty() == true) {

    //Serial.println(play.getVelocity());
    //Serial.println(record.getVelocity());

  }


