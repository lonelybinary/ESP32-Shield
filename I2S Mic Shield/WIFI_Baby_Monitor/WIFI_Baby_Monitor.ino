/*

  Lonely Binary Digtial Mic ESP32 Shield

  The Lonely Binary Wireless WiFi Microphone Shield is an advanced audio solution featuring the INMP441 I2S digital microphone. This high-fidelity microphone module captures crystal-clear audio, making it an excellent choice for DIY enthusiasts looking to construct devices such as baby monitors or custom WiFi microphone systems.

  Designed for seamless integration with WiFi-enabled devices, the shield utilizes the INMP441’s superior sensitivity and high signal-to-noise ratio to deliver pristine sound quality. The microphone operates with I2S digital output, which ensures lossless audio transmission and easy interfacing with processors and microcontrollers.

  Ideal for a range of applications, from home surveillance to personal audio systems, this shield provides developers with the tools to create professional-grade audio devices. Its straightforward setup and robust performance make it a versatile and valuable component for any project requiring reliable and high-quality sound capture.
  
  Required Library:
  arduino-audio-tools by pschatzmann
  https://github.com/pschatzmann/arduino-audio-tools

  PC Client:
  Google Chrome
  VLC (Low Latency)

  Troubleshooting:
  If there is strong background noise, you may add a 10K ohm resistor to pull down pin 32 to the ground (GND). This modification should help in reducing the noise interference effectively.
  (pin 32) --- (10k resistor) --- GND

 */

#include <Arduino.h>
#include "AudioTools.h"

/* change to your local wifi settings */
AudioWAVServer server("lonelybinary","0434811026");

I2SStream i2sStream;   
ConverterFillLeftAndRight<int16_t> filler(RightIsEmpty); // fill both channels - or change to RightIsEmpty

void setup(){
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);


  Serial.println("starting I2S...");
  auto config = i2sStream.defaultConfig(RX_MODE);
  config.i2s_format = I2S_STD_FORMAT; 

  // change those setting, wouldn't make latency better
  // iphone, ipad not supported, only pc

  // maybe it is due to the cache, how to get ride of cache?
  config.sample_rate = 22050;  
  config.channels = 2; 
  config.bits_per_sample = 16;

  config.pin_bck = 14;
  config.pin_data = 32;
  config.pin_ws = 15;

  i2sStream.begin(config);
  Serial.println("I2S started");

  // start data sink
  server.begin(i2sStream, config, &filler);
  server.begin(i2sStream, config);
}

// Arduino loop  
void loop() {
  // Handle new connections
  server.copy();  
}