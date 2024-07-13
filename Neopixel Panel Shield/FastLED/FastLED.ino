/*

    Lonely Binary Neopixel Panel Shield

    The Neopixel Panel Shield features 18 WS2812 RGB LEDs, arranged in 3 rows with 6 LEDs per row.

    The WS2812 RGB LED is a popular individually addressable LED module. Each LED can be controlled individually, allowing for complex lighting patterns and effects. Each LED contains three color channels (Red, Green, and Blue), allowing for a wide range of colors to be displayed by adjusting the brightness of each channel.

    Library: FastLED by Danel Garcia @ https://github.com/FastLED/FastLED

    Data Pin: IO17

*/

#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 18
#define DATA_PIN 17

CRGB leds[NUM_LEDS];

void solid_color(CRGB color, uint32_t delay_time);
void one_by_one(CRGB color, uint32_t delay_time);

void setup()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 
  FastLED.setBrightness(50);
}

void loop()
{
  
  solid_color(CRGB::Red, 500);   // Red for 500ms
  solid_color(CRGB::Green, 500); // Red for 500ms
  solid_color(CRGB::Blue, 500);  // Red for 500ms
  solid_color(CRGB::Black, 1000); // turn off for 1000ms

  one_by_one(CRGB::HotPink, 100); // turn on one by one
  solid_color(CRGB::Black, 1000); // turn off for 1000ms
}

void solid_color(CRGB color, uint32_t delay_time)
{
  for (int i = 0; i < NUM_LEDS; ++i)
  {
    leds[i] = color;
  }
  FastLED.show();
  delay(delay_time);
}

void one_by_one(CRGB color, uint32_t delay_time)
{
  for (int i = 0; i < NUM_LEDS; ++i)
  {

    for (int j = 0; j < NUM_LEDS; ++j)
    {
      leds[j] = CRGB::Black;
    }

    leds[i] = color;
    FastLED.show();
    delay(delay_time);
  }
}
