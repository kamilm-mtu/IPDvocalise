#include <Arduino.h>
#include <BluetoothA2DPSource.h>
#include <AudioTools.h>

BluetoothA2DPSource a2dp_source;

const int micPin = 35;
int micBuffer = 0;

int32_t get_sound_data(Frame *data, int32_t frameCount) {
    // generate your sound data 
    // return the effective length (in frames) of the generated sound  (which usually is identical with the requested len)
    // 1 frame is 2 channels * 2 bytes = 4 bytes
    frameCount = micBuffer;
    return frameCount;
}

void setup() {
  Serial.begin(9600);
  a2dp_source.start("MyMusic", get_sound_data);
}

void loop() {
}
