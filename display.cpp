
#include <Display/DisplayInterfaces/DisplayInterfaceSSD1306.hpp> // Include the display interface you'd like to use
#include <Control_Surface.h> // Include the Control Surface library
#include <display.h>
#include <Wire.h>
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
//NoteValue rudeSolo {MCU::RUDE_SOLO};

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
//BitmapDisplay<> rudeSoloDisp {
  //display, rudeSolo, XBM::solo_7, {56, 0}, WHITE};
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


void initializeDisplay(){
  Wire.begin(); // Initialize I2C communication
  display.begin(); // Initialize the display
}

void updateDisplay(){
  display.display(); // Update the display
}

