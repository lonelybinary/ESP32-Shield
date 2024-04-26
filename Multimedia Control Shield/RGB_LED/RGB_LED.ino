/*
    Lonely Binary Multimedia ESP32 Shield
    RGB WS2812 Sample Code

    The two RGB LEDs on the Lonely Binary Multimedia ESP32 Shield are WS2812 LEDs.
    The WS2812 has a built-in integrated control circuit that allows each LED to be controlled individually with single digital pin. It's often referred to as a NeoPixel.

    Required Library:
    FastLED by Daniel Garcia
*/

#include <Arduino.h>
#include <FastLED.h>

#define RGB_PIN 32
#define NUM_LEDS 2

CRGB leds[NUM_LEDS];

void setup()
{

    Serial.begin(115200);

    FastLED.addLeds<NEOPIXEL, RGB_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(50);

}

void loop()
{

    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i].red = random(0, 255);
        leds[i].green = random(0, 255);
        leds[i].blue = random(0, 255);
    }

    FastLED.show();
    delay(200);
}
