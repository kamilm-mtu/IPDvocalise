#include <Arduino.h>
#include "BluetoothA2DPSink.h"

BluetoothA2DPSink a2dp_sink;

void read_data_stream(const uint8_t *data, uint32_t length) {
    int16_t *values = (int16_t*) data;
    for (int j=0; j<length/2; j+=2){
      // print the 2 channel values
      Serial.print(values[j]);
      Serial.print(",");
      Serial.println(values[j+1]);
    }
}

void setup() {
  Serial.begin(115200);
  // output to callback and no I2S 
  a2dp_sink.set_stream_reader(read_data_stream, false);
  // connect to MyMusic with no automatic reconnect
  a2dp_sink.start("MyMusic", false);  
}


void loop() {
  delay(1000);
}