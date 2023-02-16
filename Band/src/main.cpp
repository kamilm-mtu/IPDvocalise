#include <Arduino.h>
#include "AudioTools.h"
#include "AudioLibs/AudioA2DP.h"
#include "AudioLibs/AudioRealFFT.h"

const uint8_t channels = 2;
const uint16_t sample_rate = 44100;

A2DPStream btin;
AudioRealFFT fft;
StreamCopy copier(fft, btin);

void writeDataStream(const uint8_t *data, uint32_t length) {
  fft.write(data, length);
}

void fftResult(AudioFFTBase &fft) {
  float diff;
  auto result = fft.result();
  if (result.magnitude>100){
    Serial.print(result.frequency);
    Serial.print(" ");
    Serial.print(result.magnitude);
    Serial.print(" => ");
    Serial.print(result.frequencyAsNote(diff));
    Serial.print("diff:");
    Serial.println(diff);
  }
}

void setup() {
  Serial.begin(9600);
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);

  auto cfgA2DP = btin.defaultConfig(RX_MODE);
  cfgA2DP.name = "Vocalise";
  cfgA2DP.auto_reconnect = true;
  btin.begin(cfgA2DP);

  auto tcfg = fft.defaultConfig();
  tcfg.length = 4096;
  tcfg.channels = channels;
  tcfg.sample_rate = sample_rate;
  tcfg.bits_per_sample = 16;
  tcfg.callback = &fftResult;
  fft.begin(tcfg);
}

void loop() {
  copier.copy();
}