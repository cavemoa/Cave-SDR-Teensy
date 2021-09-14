/*  Simple test sketch to generate an 880hz tone on the headphones
    
    Author: Jonathan Davies
    Date: 14/09/21
    Version: 1.0

    Should work with any Teensy / Audio shield combination.
    Simply fit the Teensy tot he shield and upload the code
    Plug in a pair of earphones and you should get an 880Hz tone

*/

// MemoryAndCpuUsage
//
// This example demonstrates how to monitor CPU and memory
// usage by the audio library.  You can see the total memory
// used at any moment, and the maximum (worst case) used.
//
// The total CPU usage, and CPU usage for each object can
// be monitored.  Reset functions clear the maximums.
//
// Use the Arduino Serial Monitor to view the usage info
// and control ('F', 'S', and 'R' keys) this program.
//
// This example code is in the public domain.
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Audio.h>        // Teensy audio library by Paul Stoffregen

// GUItool: begin automatically generated code
AudioSynthWaveformSine   waveform1;          //xy=137,130
AudioOutputI2S           i2s1;           //xy=339,136
AudioConnection          patchCord1(waveform1, 0, i2s1, 0);
AudioConnection          patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000     audioShield;     //xy=147,73
// GUItool: end automatically generated code

void setup() {
  AudioMemory(15);
  audioShield.enable();
  audioShield.volume(0.5);

  waveform1.frequency(880);
  waveform1.amplitude(0.95);
}

void loop() {

}