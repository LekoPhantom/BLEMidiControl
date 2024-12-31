#BLE Midi Control...

Here is the Mackie Control List...

https://tttapa.github.io/Control-Surface/Doxygen/de/d44/group__MCU__Notes.html


To choose which 8 channels a Mackie Control surface controls, use the "BANK LEFT" and "BANK RIGHT" buttons, which allow you to navigate through "banks" of eight channels at a time; essentially, pressing these buttons lets you switch between sets of 8 channels you can control with the faders and knobs on the surface. 

This is a wonderful i2c tutorial. 
https://randomnerdtutorials.com/esp32-i2c-communication-arduino-ide/#1
I may be able to run four lcds

I am looking to be clear about the logic section, so I am going to map it out here...

----------------

Each channel strip is going to contain the following io 

Controls...       |  Pins (input) | Displays  |
------------------| --------------| --------  |
Mute              |               | Neo [0]   |-----|
Solo              |               | Neo [1]   |     |-- Array 0 - Buttons
Record Ready      |               | Neo [2]   |     |
Select            |               | Neo [3]   |-----|

Balance           |               | Ring      | ----|-- Array 1 - Ring
Fader             |               | Screen (1st half) |--- Pins 21 and 22
---------------------------------------------

Mains

Encoder - Jog
Joystick - Zoom
Main Fader - Main volume
AXBY buttons - Navigation?
Transport buttons
Mute
Stereo Out display (two rings?) |-- Array 2 + 3


QUestions...
VU meters, how do we switch between balance and vu?
How do we use banks without pins (for the led feedback?)
Rude Solo?
Scribble strips?
Track Color?







