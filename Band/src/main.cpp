#include <Arduino.h>
#include "AudioTools.h"
#include "AudioLibs/AudioA2DP.h"

A2DPStream btin;

void setup() {
  Serial.begin(9600);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);

  auto cfgA2DP = btin.defaultConfig(RX_MODE);
  cfgA2DP.name = "Vocalise";
  cfgA2DP.auto_reconnect = true;
  btin.begin(cfgA2DP);
  Serial.println("Connected");
}

void loop() {

}