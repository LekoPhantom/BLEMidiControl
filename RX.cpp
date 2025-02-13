#include <RX.h>
#include <FastLED.h>
#include <Wire.h>

#include <PinAssignments.h>

void initializeRX(){
Wire.begin(1);
Wire.onReceive(receiveEvent);
}

void receiveEvent(int howMany, HARDWARE_Serial &serial)
{
int b = Wire.read();
//serial.println(b);
//let's try to map our value...
//map(value, fromLow, fromHigh, toLow, toHigh)
int mappedBrightness = map(b,0,255,0,ledMaxBirghtness);
//serial.println("The Mapped Brightness is...");
//serial.println(mappedBrightness);
//FastLED.setBrightness(mappedBrightness);

}