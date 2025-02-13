#include <PinAssignments.h>

#include <Control_Surface.h> // Include the Control Surface library

//Include the headers for functions and constants that are broken out...
#include <display.h>
#include <lights.h>
#include <OI.h>
#include <RX.h>


// ----------------------------- MIDI Interface ----------------------------- //
BluetoothMIDI_Interface midi;

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
