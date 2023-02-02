//#define c3_frequency  130.81
//#define PI 3.14159265358979323846

//BluetoothA2DPSource a2dp_source;

// The supported audio codec in ESP32 A2DP is SBC. SBC audio stream is encoded
// from PCM data normally formatted as 44.1kHz sampling rate, two-channel 16-bit sample data
//int32_t get_data_channels(Frame *frame, int32_t channel_len) {
//    static double m_time = 0.0;
//    double m_amplitude = 10000.0;  // -32,768 to 32,767
//    double m_deltaTime = 1.0 / 44100.0;
//    double m_phase = 0.0;
//    double double_Pi = PI * 2.0;
    // fill the channel data
//    for (int sample = 0; sample < channel_len; ++sample) {
//        double angle = double_Pi * c3_frequency * m_time + m_phase;
//        frame[sample].channel1 = m_amplitude * sin(angle);
//        frame[sample].channel2 = frame[sample].channel1;
//        m_time += m_deltaTime;
//    }

//    return channel_len;
//}


//void setup() {
  //a2dp_source.set_auto_reconnect(false);
//  a2dp_source.start("MyMusic", get_data_channels);  
//  a2dp_source.set_volume(30);
//}

//void loop() {
  // to prevent watchdog in release > 1.0.6
//  delay(10);
//}

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