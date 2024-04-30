/*
    Lonely Binary ESP32 I2S Audio Shield

    The Lonely Binary ESP32 I2S Audio Shield is equipped with the MAX98357A DAC IC, which supports a 32-bit resolution to deliver CD-quality audio. This shield features a built-in 3 Watt Class D audio amplifier capable of driving large headphones or external speakers efficiently.

    The ESP32 microcontroller interfaces with the MAX98357A using the I²S (Inter-IC Sound) protocol, which requires three specific pins: DOUT, BCLK, and LRC, for accurate audio data transmission:

    BCLK (Bit Clock): This clock signal provides a timing reference, dictating the rate at which audio data bits are transmitted. It ensures that each bit of the audio data can be precisely timed and read by the receiver.
    LRC (Left/Right Clock): Also known as LRCLK or Word Select, this clock toggles at a frequency lower than the BCLK. It serves to indicate which audio channel (left or right) the data corresponds to, allowing the DAC to differentiate between left and right audio channels effectively.
    DOUT (Data OUT): This line transmits the actual audio data bits. The data is synchronized with the BCLK pulses, and the LRC state signals which channel's data is being sent at any given time.
    
    This shield is ideal for any project requiring high-quality audio output, such as DIY audio players, sound-enabled IoT devices, and interactive art installations, where clarity and sound fidelity are crucial.

    We can host music at local pc by using the following command:
    python3 -m http.server 8000
    This will start the server on the default port, which is 8000.

    Required Libraries:
    ESP32-audioI2S
    https://github.com/schreibfaul1/ESP32-audioI2S
*/
#include "Arduino.h"
#include "WiFiMulti.h"
#include "Audio.h"

#define I2S_DOUT 26
#define I2S_BCLK 27
#define I2S_LRC 14

Audio audio;
WiFiMulti wifiMulti;

//replace this with your wifi ssid and password
String ssid = "SSID";
String password = "PASSWORD";

void setup()
{

    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    wifiMulti.addAP(ssid.c_str(), password.c_str());
    wifiMulti.run();
    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.disconnect(true);
        wifiMulti.run();
    }

    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(21);

    // host local mp3 online by using python
    audio.connecttohost("http://192.168.0.71:8000/music.mp3");
}

void loop()
{
    audio.loop();
    if (Serial.available())
    {
        audio.stopSong();
        String r = Serial.readString();
        r.trim();
        if (r.length() > 5)
            audio.connecttohost(r.c_str());
        log_i("free heap=%i", ESP.getFreeHeap());
    }
}
