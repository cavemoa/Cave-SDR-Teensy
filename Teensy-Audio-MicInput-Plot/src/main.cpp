/*  Simple sketch to plot the Microphone Input on SerialPlot
    
    Author: Jonathan Davies
    Date: 14/09/21
    Version: 1.0

    Coonect microphone in into 1024 FFT to demonstrate plotting on SerialPlot on Teensy Audio
    Uses SerialPlot to graph it on the output https://github.com/hyOzd/serialplot
    Details and binaries here: https://hackaday.io/project/5334-serialplot-realtime-plotting-software
    In the plot tab of SerialPlot set the buffer size to 512, then open the serial port the 
    Teensy is connected to.  his plots the 512 bins, 0 - 511 giving 43Hz resolution, 
*/

#include <Arduino.h>          // Required by PlatformIO
#include <Audio.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=180,111
AudioFilterStateVariable filter1;        //xy=325,101
AudioAmplifier           amp1;           //xy=470,93
AudioAnalyzeFFT1024      myFFT;      //xy=616,102
AudioConnection          patchCord1(i2s1, 0, filter1, 0);
AudioConnection          patchCord2(filter1, 2, amp1, 0);
AudioConnection          patchCord3(amp1, myFFT);
AudioControlSGTL5000     sgtl5000_1;     //xy=321,432
// GUItool: end automatically generated code

void setup() {
  Serial.begin(9600);
  AudioMemory(50);
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(63);
  sgtl5000_1.volume(0.5);


  filter1.frequency(30); // filter out DC & extremely low frequencies
  amp1.gain(32000);        // amplify sign to useful range
}

void loop() {
  if (myFFT.available()) {
    // each time new FFT data is available
    // print 511 bins to the Arduino Serial Monitor
    for (int i = 0; i < 511; i++) {
      Serial.print(myFFT.read(i)*1000);
      Serial.println(",");
    }
    // Serial.println();
    delay(50);//Delay if using SerialPlot for Visual Output
  }
}