/**
    Lonely Binary Multimedia ESP32 Shield
    Bluetooth Copy Paste Shortcut Keypad Sample Code

    Functions:
    Mechanical Key A: Paste
    Mechanical Key B: Copy

    Required Library:
    FastLED by Daniel Garcia
    ESP32-BLE-Keyboard
    https://github.com/T-vK/ESP32-BLE-Keyboard

 */

#include <Arduino.h>
#include <BleKeyboard.h>
#include <FastLED.h>

#define BTNA_PIN 34
#define BTNB_PIN 35

// RGB LED
#define RGB_PIN 32
#define NUM_LEDS 2


CRGB leds[NUM_LEDS];

BleKeyboard bleKeyboard("ESP32 Multimedia Shield", "LONELY BINARY", 100);

void rgb_show(CRGB led0, CRGB led1)
{   
    static int brightness = 100;
    static int direction = 1;

    brightness = brightness + 10*direction;

    if (brightness >= 255)
    {   
        brightness = 255;
        direction=-1;
    }
    else if (brightness <= 0)
    {
        brightness = 0;
        direction=1;
    }
    FastLED.setBrightness(brightness);
    leds[0] = led0;
    leds[1] = led1;
    FastLED.show();
    delay(50);
}


void setup()
{

    Serial.begin(115200);

    pinMode(BTNA_PIN, INPUT);
    pinMode(BTNB_PIN, INPUT);

    bleKeyboard.begin();

    FastLED.addLeds<NEOPIXEL, RGB_PIN>(leds, NUM_LEDS);
}

void loop()
{

    rgb_show(CRGB::Red, CRGB::Red);

    if ((digitalRead(BTNB_PIN) == HIGH) && bleKeyboard.isConnected())
    {
        // Macbook Command + C
        Serial.println("Copy");
        bleKeyboard.press(KEY_LEFT_GUI);
        bleKeyboard.press('c');
        bleKeyboard.releaseAll();
        delay(1000);
    }

    if ((digitalRead(BTNA_PIN) == HIGH) && bleKeyboard.isConnected())
    {
        // Macbook Command + V
        Serial.println("paste");
        bleKeyboard.press(KEY_LEFT_GUI);
        bleKeyboard.press('v');
        bleKeyboard.releaseAll();
        delay(1000);
    }

}
