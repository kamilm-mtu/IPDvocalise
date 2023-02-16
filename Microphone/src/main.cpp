#include "Arduino.h"
#include "AudioTools.h"
#include "AudioLibs/AudioA2DP.h"

const uint16_t sample_rate = 44100;
const uint8_t channels = 2;

AnalogAudioStream in;
A2DPStream btout; 
// CsvStream<int16_t> out(Serial, channels); // ASCII output
// StreamCopy copier(out, in); // Microphone -> ASCII output
ConverterAutoCenter<int16_t> center(2); // Set microphone output to 0
StreamCopy btcopier(btout, in); // Microphone -> Bluetooth output

void setup(void) {
  Serial.begin(9600);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);

  // GP34 Default Output
  auto cfgRx = in.defaultConfig(RX_MODE);
  cfgRx.sample_rate = sample_rate;
  cfgRx.channels = channels;
  in.begin(cfgRx);
  
  auto cfgA2DP = btout.defaultConfig(TX_MODE);
  cfgA2DP.name = "Vocalise";
  cfgA2DP.auto_reconnect = true;
  btout.begin(cfgA2DP);
  Serial.println("Connected");
}

void loop() {
  // copier.copy(center);
  btcopier.copy(center);
}