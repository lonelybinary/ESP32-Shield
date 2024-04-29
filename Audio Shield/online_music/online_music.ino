/*
    Lonely Binary ESP32 Audio Shield

    The Lonely Binary Audio Shield utilizes the ESP32's DAC2 channel on GPIO26 to perform digital-to-analog audio conversion. The ESP32 features an 8-bit DAC, allowing it to output audio at 256 distinct voltage levels. This setup produces audio quality comparable to that of standard radio broadcasts due to the limited range of sound levels it can reproduce.

    For users seeking higher audio fidelity, the Lonely Binary I2S Shield is a superior alternative. It is equipped with a dedicated 32-bit DAC, offering a significantly broader range of sound levels for enhanced audio performance. This allows for much finer detail in the audio output, making it ideal for high-quality audio applications.This version includes additional explanations about the capabilities and limitations of the 8-bit DAC, as well as the advantages of upgrading to the 32-bit DAC with the I2S Shield.

    We can host music at local pc by using the following command:
    python3 -m http.server
    This will start the server on the default port, which is 8000.

    Required Libraries:
    ESP32-audioI2S
    https://github.com/schreibfaul1/ESP32-audioI2S
*/

#include "Arduino.h"
#include "WiFiMulti.h"
#include "Audio.h"

Audio audio(true, I2S_DAC_CHANNEL_BOTH_EN);
WiFiMulti wifiMulti;

// replace with your wireless ssid and password
String ssid =     "WIFI_SSID";
String password = "WIFI_PASSWORD";

void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}

void setup() {
   Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    wifiMulti.addAP(ssid.c_str(), password.c_str());
    wifiMulti.run();
    if(WiFi.status() != WL_CONNECTED){
        WiFi.disconnect(true);
        wifiMulti.run();
    }

    audio.setVolume(21); // 0...21

    audio.connecttohost("http://192.168.0.71:8000/music.mp3"); // Localhost simple music file
}

void loop()
{
    audio.loop();
}

