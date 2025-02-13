#include <PinAssignments.h>

//----------------------------- NEOPIXEL Interface ----------------------------- //
// Define the array of LEDs.
//Array<CRGB, 30> leds {};

#include <FastLED.h>
#include <Control_Surface.h> // Include the Control Surface library
#include <display.h>
#include <lights.h>


CRGB leds[totalNumberLeds];

uint8_t gHue = 0;



long maxBrightness = 60;

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
    //include the header file to use separate methods
  newRainbow();
  //rainbow();

  }
  
  
  // Show the updated LED state
  FastLED.show();
}


void rainbow() 
{
  
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, totalNumberLeds, gHue, 1);
}

void newRainbow(){
  for (int i = 0; i < totalNumberLeds; i++) {
    //leds[i] = CHSV(hue, 255, 255);
    leds[i] = CHSV(gHue + (i * 10), 255, 255);
  }

  EVERY_N_MILLISECONDS(15){
    gHue++;
  }
}

void rainbow_beat() {
  
  uint8_t beatA = beatsin8(17, 0, 255);                        // Starting hue
  uint8_t beatB = beatsin8(13, 0, 255);
  fill_rainbow(leds, totalNumberLeds, (beatA)/2, 8);            // Use FastLED's fill_rainbow routine.

} // rainbow_beat()