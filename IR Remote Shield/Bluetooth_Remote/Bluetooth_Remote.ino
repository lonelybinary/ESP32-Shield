/*
    Lonely Binary IR Remote Shield with Remote

    IR Receive with ESP32 Bluetooth
    Using Remote to control your macbook

    Enhance your Arduino projects with the versatile Lonely Binary Infrared IR Shield with Remote. This advanced shield empowers your devices to both receive and transmit IR signals, offering seamless integration with a wide range of home appliances. Whether you're looking to control your TV, air conditioner, or any other IR-enabled device, this shield provides a robust solution for duplicating and managing remote signals effortlessly.

    The Lonely Binary Infrared IR Shield includes an elegant remote featuring a sleek, user-friendly design that complements any setup. Its simplicity ensures easy operation and integration into your existing projects without hassle. Ideal for hobbyists and professionals alike, this shield opens up endless possibilities for automation and remote control applications.

    Pins Assignment:
    RECEIVE GPIO 0
    SEND  GPIO 4  

    Library:
    Infrared4Arduino
    https://github.com/bengtmartensson/Infrared4Arduino

    ESP32 BLE Keyboard
    https://github.com/T-vK/ESP32-BLE-Keyboard
*/

#include <Arduino.h>
#include <IRremote.hpp>
#include "PinDefinitionsAndMore.h"
#include <BleKeyboard.h>

#define DEBBOUNCE_DELAY 100
#define ENABLE_DEBUG true

#define KEY_SPACE 0x2C+0x88
#define KEY_MAC_LEFT_OPT 0x82
#define KEY_MAC_LEFT_CMD KEY_LEFT_GUI
#define KEY_MAC_LEFT_CTRL 0x80
#define KEY_MAC_FN KEY_CAPS_LOCK

BleKeyboard bleKeyboard("ESP32 Remote", "LONELY BINARY", 100);

void command();

void setup()
{
    Serial.begin(115200);

    // Wait for the serial connection to be established
    delay(5000);
    Serial.println("Lonely Binary IR Remote Shiled Demo Code");

    IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
    printActiveIRProtocols(&Serial);

    bleKeyboard.begin();
}

void loop()
{
    // IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
    if (IrReceiver.decode())
    {
        if (IrReceiver.decodedIRData.protocol != UNKNOWN)
        {
            IrReceiver.resume(); // Early enable receiving of the next IR frame

            if (ENABLE_DEBUG)
                IrReceiver.printIRResultShort(&Serial);

            command();
        }
    }

    delay(5);
}

void command()
{
    if (IrReceiver.decodedIRData.decodedRawData == 0x0)
        return;
    switch (IrReceiver.decodedIRData.command)
    {
    case 0xC:
        Serial.println("Power");
        // Macbook Control + Command + Q
        Serial.println("Locking Screen...");
        bleKeyboard.press(KEY_MAC_LEFT_CTRL);
        bleKeyboard.press(KEY_MAC_LEFT_CMD);
        bleKeyboard.press('q');
        bleKeyboard.releaseAll(); // Releases all keys
        break;
    case 0xF:
        Serial.println("Input");
        break;
    case 0xD:
        Serial.println("Mute");
        if (bleKeyboard.isConnected())
        {
            bleKeyboard.write(KEY_MEDIA_MUTE);
            Serial.println("Mute/Unmute");
        }
        break;
    case 0x42:
        Serial.println("Up");
        break;
    case 0x46:
        Serial.println("Enter");
        if (bleKeyboard.isConnected())
        {
            bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
            Serial.println("Play/Pause");
        }
        break;
    case 0x43:
        Serial.println("Down");
        break;
    case 0x44:
        Serial.println("Left");
        if (bleKeyboard.isConnected())
        {
            bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
            Serial.println("Previous Track");
        }
        break;
    case 0x45:
        Serial.println("Right");
        if (bleKeyboard.isConnected())
        {
            bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
            Serial.println("Next Track");
        }

        break;
    case 0x78:
        Serial.println("Home");
        // Macbook FN(Use Function Key) + F11
        if (bleKeyboard.isConnected())
        {
            Serial.println("Show/Hide Desktop ...");
            bleKeyboard.press(KEY_F11);
            bleKeyboard.releaseAll(); // Releases all keys
        }
        break;
    case 0x5B:
        Serial.println("Back");
        break;
    case 0x11:
        Serial.println("Menu");
        break;
    case 0x14:
        if (bleKeyboard.isConnected())
        {
            Serial.println("Volumn Up");
            bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
        }
        break;
    case 0x15:
        if (bleKeyboard.isConnected())
        {
            Serial.println("Volumn Down");
            bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
        }
        break;
    case 0x9C:
        Serial.println("Search");
        if (bleKeyboard.isConnected())
        {
        // Macbook Command + Space
        Serial.println("Spotlight Search ...");
        bleKeyboard.press(KEY_MAC_LEFT_CMD);
        bleKeyboard.press(KEY_SPACE);
        bleKeyboard.releaseAll(); // Releases all keys
        }
        break;
    case 0xB2:
        Serial.println("Red");
        if (bleKeyboard.isConnected())
        {
        // Macbook Command + Space
        Serial.println("Red App");
        bleKeyboard.press(KEY_MAC_LEFT_CMD);
        bleKeyboard.press(KEY_MAC_LEFT_OPT);
        bleKeyboard.press(KEY_MAC_LEFT_CTRL);
        bleKeyboard.press('r');
        bleKeyboard.releaseAll(); // Releases all keys
        }
        break;
    case 0xB3:
        Serial.println("Green");
        break;
    case 0xB4:
        Serial.println("Blue");
        if (bleKeyboard.isConnected())
        {
        // Macbook Command + Space
        Serial.println("Full Screen ...");
        bleKeyboard.press(KEY_MAC_FN);
        bleKeyboard.press('f');
        bleKeyboard.releaseAll(); // Releases all keys
        }
        break;
    }

    delay(DEBBOUNCE_DELAY);
}