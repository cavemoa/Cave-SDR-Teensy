
/*  Simple sketch to plot an 511 Bin FFT on SerialPlot
    
    Author: Jonathan Davies
    Date: 14/09/21
    Version: 1.0

    Simple 2 tone mixed signal into 1024 FFT to demonstrate plotting on SerialPlot on Teensy Audio
    Uses SerialPlot to graph it on the output https://bitbucket.org/hyOzd/serialplot/src/default/
    In the plot tab of SerialPlot set the buffer size to 512, then open the serial port the 
    Teensy is connected to.  his plots the 512 bins, 0 - 511 giving 43Hz resolution, 
    Updates at approx 86 times a second according to Teesnsy audio design tool
*/

#include <Arduino.h>          // Required by PlatformIO
#include <Audio.h>


// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=103,187
AudioSynthToneSweep   tonesweep;          //xy=105,295
AudioMixer4              mixer1;         //xy=265,234
AudioOutputI2S           i2s1;           //xy=501,229
AudioAnalyzeFFT1024      myFFT;      //xy=512,309
AudioConnection          patchCord1(sine1, 0, mixer1, 0);
AudioConnection          patchCord2(tonesweep, 0, mixer1, 1);
AudioConnection          patchCord3(mixer1, 0, i2s1, 0);
AudioConnection          patchCord4(mixer1, 0, i2s1, 1);
AudioConnection          patchCord5(mixer1, myFFT);
AudioControlSGTL5000     sgtl5000_1;     //xy=321,432
// GUItool: end automatically generated code

// elapsedMillis blinkTime;

void setup() {
  Serial.begin(115200);

  AudioMemory(10);
  AudioNoInterrupts();

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  myFFT.windowFunction(AudioWindowHanning1024);
  
  AudioInterrupts();

  sine1.frequency(2500);
  sine1.amplitude(0.15);

  float t_ampx = 0.8;
  int t_lox = 10;
  int t_hix = 22000;
// Length of time for the sweep in seconds
  float t_timex = 10;
  if(!tonesweep.play(t_ampx,t_lox,t_hix,t_timex)) {
    Serial.println("AudioSynthToneSweep - begin failed");
    while(1);
  }

  mixer1.gain(0, 1);
  mixer1.gain(1, 1);

  delay(200);
}

void loop() {
  if (myFFT.available()) {
    for (int i = 0; i < 511; i++)
    {
      Serial.println(myFFT.read(i) * 1000, 1);
    }
    Serial.println();
    delay(50);//Delay if using SerialPlot for Visual Output
  }

}