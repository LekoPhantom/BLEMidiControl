#include <PinAssignments.h>

//----------------------------- NEOPIXEL Interface ----------------------------- //
// Define the array of LEDs.
//Array<CRGB, 30> leds {};

#include <FastLED.h>
#include <Control_Surface.h> // Include the Control Surface library
#include <display.h>


CRGB leds[totalNumberLeds];


void initializeLeds(){
   // FastLED setup
  FastLED.addLeds<NEOPIXEL, ledPin>(leds,totalNumberLeds)
    .setCorrection(TypicalPixelString);
   
  
  FastLED.setBrightness(ledBrightness);
}

void updateLeds() {
  // Clear all LEDs
   fill_solid(leds, totalNumberLeds, CRGB::Black);

// Try to add the rude solo logic... 

if (getRudy() == true) {
  for (uint8_t i = 0; i < totalNumberLeds; ++i) { // Use the value for the first bank
    leds[i] = CRGB::Red;
  }
        // Clear the dirty flag to acknowledge the change
    //rudeSolo.clearDirty();
  } else if (getVu() != 0){
    uint8_t vuValue = getVu();
    if (vuValue == 12){
        for (uint8_t i = 0; i < vuValue; ++i) { // Use the value for the first bank
    leds[i+2] = CRGB::Red;
    }} else {
    // Set LEDs based on VU meter value
   for (uint8_t i = 0; i < vuValue; ++i) { // Use the value for the first bank
    leds[i] = CRGB::Green;
   }}
  } else {
  //rainbow_beat();

 uint8_t beatA = beatsin8(17, 0, 255);                        // Starting hue
  uint8_t beatB = beatsin8(13, 0, 255);
  fill_rainbow(leds, totalNumberLeds, (beatA+beatB)/2, 8);            // Use FastLED's fill_rainbow routine.

  }
  
  
  // Show the updated LED state
  FastLED.show();
}


void rainbow_beat() {
  
  uint8_t beatA = beatsin8(17, 0, 255);                        // Starting hue
  uint8_t beatB = beatsin8(13, 0, 255);
  fill_rainbow(leds, totalNumberLeds, (beatA+beatB)/2, 8);            // Use FastLED's fill_rainbow routine.

} // rainbow_beat()