#include <FastLED.h>
#include <Control_Surface.h>

// Instantiate a MIDI interface to use for the Control Surface.
BluetoothMIDI_Interface midi;

// Define the array of LEDs.
Array<CRGB, 12> leds {};
// The data pin with the strip connected.
constexpr uint8_t ledpin = 5;

// Define the VU meter state
MCU::VUState vuState;

Bank<4> bank(2); // Create a new bank with two tracks per bank

// VU meters
MCU::Bankable::VU<4> vu[] {
  {bank, 1, MCU::VUDecay::Hold},
  {bank, 2, MCU::VUDecay::Hold},
};

// VPot rings
MCU::Bankable::VPotRing<4> vpot[] {
  {bank, 1},
  {bank, 2},
};

void setup() {
  // FastLED setup
  FastLED.addLeds<NEOPIXEL, ledpin>(leds.data, leds.length);
  FastLED.setCorrection(TypicalPixelString);

    // Initialize Serial for debugging
  Serial.begin(115200);

  // Control Surface setup
  Control_Surface.begin();



  // Debugging: Print the initial state
  Serial.print("Initial VU value: ");
  Serial.println(vu[1].); // Print the value for the first bank
  Serial.print("Initial overload state: ");
  Serial.println(vu[1].getOverload(1)); // Print the overload state for the first bank
  //Serial.println(vPotRing[1].get);
}

void loop() {
  Control_Surface.loop();

  // Debugging: Print the current state before updating
  Serial.print("Current VU value: ");
  Serial.println(vu[1].getValue(1)); // Print the value for the first bank
  Serial.print("Current overload state: ");
  Serial.println(vu[1].getOverload(1)); // Print the overload state for the first bank

  // Update FastLEDs based on VU meter state
  vu[1].update();
  updateLEDs();
}

void updateLEDs() {
  // Clear all LEDs
  fill_solid(leds.data, leds.length, CRGB::Black);

  // Set LEDs based on VU meter value
  for (uint8_t i = 0; i < vu[0].getValue(0); ++i) { // Use the value for the first bank
    leds[i] = CRGB::Green;
  }

  // Set overload LED
  if (vu[0].getOverload(0)) { // Use the overload state for the first bank
    leds[leds.length - 1] = CRGB::Red;
  }

  // Show the updated LED state
  FastLED.show();
}
