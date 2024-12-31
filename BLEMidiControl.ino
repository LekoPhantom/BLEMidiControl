#include <ButtonAssignments.h>
#include <Wire.h>
#include <FastLED.h>
#include <Control_Surface.h> // Include the Control Surface library
#include <Display/DisplayInterfaces/DisplayInterfaceSSD1306.hpp> // Include the display interface you'd like to use

// ----------------------------- MIDI Interface ----------------------------- //
BluetoothMIDI_Interface midi;

//----------------------------- NEOPIXEL Interface ----------------------------- //
// Define the array of LEDs.
Array<CRGB, 12> leds {};


// ----------------------------- Display setup ------------------------------ //

constexpr uint8_t SCREEN_WIDTH = 128;
constexpr uint8_t SCREEN_HEIGHT = 64;
constexpr int8_t OLED_reset = -1; // Use the external RC circuit for reset

// Instantiate the display -- This line is different than the SPI.
Adafruit_SSD1306 ssd1306Display = {SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_reset};

// --------------------------- Display interface ---------------------------- //

class MySSD1306_DisplayInterface : public SSD1306_DisplayInterface {
  public:
    MySSD1306_DisplayInterface(Adafruit_SSD1306 &display)
      : SSD1306_DisplayInterface(display) {}

    void begin() override {
      // Initialize the Adafruit_SSD1306 display
      if (!disp.begin(SSD1306_SWITCHCAPVCC, 0x3C))
        FATAL_ERROR(F("SSD1306 allocation failed."), 0x1306);

      SSD1306_DisplayInterface::begin();

      disp.setTextColor(WHITE);
      disp.setTextSize(1);
    }

    void display() override {
      SSD1306_DisplayInterface::display();
    }

    void drawBackground() override {}
} display = {ssd1306Display};

// -------------------------- MIDI Input Elements --------------------------- //
// ========================================================================== //

/*
 * Define all elements that listen for MIDI messages.
 */

// Main MCU LCD screen, used to get track names
MCU::LCD<> lcd {};

// Mute
NoteValue mute[2] {
  {MCU::MUTE_1},
  {MCU::MUTE_2},
};

// Solo
NoteValue solo[2] {
  {MCU::SOLO_1},
  {MCU::SOLO_2},
  
};

//Rude solo
NoteValue rudeSolo {MCU::RUDE_SOLO};

// Record arm / ready
NoteValue recrdy[2] {
  {MCU::REC_RDY_1},
  {MCU::REC_RDY_2},
};

// VPot rings
MCU::VPotRing vpot[2] {
  {1},
  {2},
};

// VU meters - CUbasis does not yet seem to handle these
MCU::VU vu[2] {
  {1, MCU::VUDecay::Default},
  {2, MCU::VUDecay::Default},
};

// ---------------------------- Display Elements ---------------------------- //
// ========================================================================== //

// Track names
MCU::LCDDisplay lcddisps[2] {
  // track (1), position (0, 40), font size (1)
  {display, lcd, 1, 1, {0, 0}, 1, WHITE},
  {display, lcd, 2, 1, {66, 0}, 1, WHITE},
};

// Mute
BitmapDisplay<> muteDisp[2] {
  {display, mute[0], XBM::mute_10B, {14, 50}, WHITE},
  {display, mute[1], XBM::mute_10B, {14 + 64, 50}, WHITE},
};

// Solo
BitmapDisplay<> soloDisp[2] {
  {display, solo[0], XBM::solo_10B, {14, 50}, WHITE},
  {display, solo[1], XBM::solo_10B, {14 + 64, 50}, WHITE},
};

// Rude solo
BitmapDisplay<> rudeSoloDisp {
  display, rudeSolo, XBM::solo_7, {56, 0}, WHITE};
// Record arm / ready
BitmapDisplay<> recrdyDisp[2] {
  {display, recrdy[0], XBM::rec_rdy_10B, {14 + 14, 50}, WHITE},
  {display, recrdy[1], XBM::rec_rdy_10B, {14 + 14 + 64, 50}, WHITE},
};

// VPot rings

MCU::VPotDisplay<> vpotDisp[2] {
  // position (0, 10), outer radius (14) px, inner radius (12) px
  {display, vpot[0], {0, 15}, 10, 12, WHITE},
  {display, vpot[1], {64, 15}, 10, 12, WHITE},
};


// VU meters with a box
MCU::VUDisplay<> vuDisp[2] {
  // position (32+11, 60), width (16), bar height (3) px, bar spacing (1) px
  {display, vu[0], {0}, 16, 3, 1, WHITE},
  {display, vu[1], {32 + 11 + 64, 63}, 16, 3, 1, WHITE},
};




//----------------------------------Output ---------------------------------- //

CCRotaryEncoder enc {
  {Enc1A,Enc1B},                                // pins
  MCU::JOG_WHEEL, // address
  5,                       // multiplier
  4,                                     // pulses per click
};

//Instantiate the banks...

Bank<4> bank(2); // A bank with 2 channels, and 4 bank settings

// Selector to change banks
IncrementDecrementSelector<4> selector {bank, {26, 36}};

//Add a buffer to store the bank characters...
char buffer [33];

Bankable::NoteButton mute_switches[] {
  {{bank, BankType::ChangeAddress}, mute1 , {MCU::MUTE_1}},
  {{bank, BankType::ChangeAddress}, mute2 , {MCU::MUTE_2}},
};

// Solo
Bankable::NoteButton solo_switches[] { 
  {{bank, BankType::ChangeAddress}, solo1, {MCU::SOLO_1}},
  {{bank, BankType::ChangeAddress}, solo2, {MCU::SOLO_2}},
  
};

Bankable::NoteButton rec_switches[] {
  {{bank, BankType::ChangeAddress}, rReady1, {MCU::REC_RDY_1}},
  {{bank, BankType::ChangeAddress}, rReady2, {MCU::REC_RDY_2}},
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



// --------------------------------- Setup ---------------------------------- //

void setup() {

   // FastLED setup
  FastLED.addLeds<NEOPIXEL, ledPin>(leds.data, leds.length);
  FastLED.setCorrection(TypicalPixelString);
  FastLED.setBrightness(ledBrightness);

    // Initialize Serial for debugging
  Serial.begin(115200);
  
  RelativeCCSender::setMode(relativeCCmode::MACKIE_CONTROL_RELATIVE);
  Wire.begin(); // Initialize I2C communication
  Control_Surface.begin(); // Initialize Control Surface
  display.begin(); // Initialize the display
  
  // Debugging: Print the initial state
  //Serial.print("Initial VU value: ");
  //Serial.println(vu[1].); // Print the value for the first bank
  //Serial.print("Initial overload state: ");
  //Serial.println(vu[1].getOverload(1)); // Print the overload state for the first bank
  //Serial.println(vpot[0].get
}

// ---------------------------------- Loop ---------------------------------- //

void loop() {
  Control_Surface.loop(); // Refresh all elements
  display.display(); // Update the display
  //Faders
  //Serial.println(mainFaders[1].getRawValue());
  Serial.println("The bank is........................................");
  Serial.println(bank.getSelection());

  // You can request the state of the smart potentiometer:
  if (potentiometer1.getState() == PBSmartPot::Lower) {
    // Turn on an LED to indicate that the potentiometer
    // value is too low to be active
  } else if (potentiometer1.getState() == PBSmartPot::Higher) {
    // Turn on an LED to indicate that the potentiometer
    // value is too high to be active
  }
// You can request the state of the smart potentiometer:
  if (potentiometer2.getState() == PBSmartPot::Lower) {
    // Turn on an LED to indicate that the potentiometer
    // value is too low to be active
  } else if (potentiometer2.getState() == PBSmartPot::Higher) {
    // Turn on an LED to indicate that the potentiometer
    // value is too high to be active
  }

  
  // Draw boxes around VU meters to visualize their positions
  for (int i = 0; i < 2; ++i) {
    ssd1306Display.drawRect((80*i), 40, 16, 12, WHITE); // Adjust the dimensions and position as needed
  }

    ssd1306Display.drawChar(0,5,'C',WHITE,BLACK,2);
     // Method 2: Using static_cast
    char ch2 = int(bank.getSelection() + 48);
  ssd1306Display.drawChar(20,5,ch2,WHITE,BLACK,2);
  ssd1306Display.display(); // Update the display
  updateLEDs();
}

void updateLEDs() {
  // Clear all LEDs
  fill_solid(leds.data, leds.length, CRGB::Black);

  
  
// Try to add the rude solo logic... NoteValue rudeSolo {MCU::RUDE_SOLO};
if (rudeSolo.getValue() == true) {
  for (uint8_t i = 0; i < 12; ++i) { // Use the value for the first bank
    leds[i] = CRGB::Red;
  }
        // Clear the dirty flag to acknowledge the change
    //rudeSolo.clearDirty();
  } else {
    // Set LEDs based on VU meter value
  for (uint8_t i = 0; i < vpot[0].getPosition(); ++i) { // Use the value for the first bank
    leds[i] = CRGB::Green;
  }
}

  // Show the updated LED state
  FastLED.show();
}
