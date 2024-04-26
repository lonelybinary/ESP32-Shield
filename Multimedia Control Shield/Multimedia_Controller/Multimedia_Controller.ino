/**
    Lonely Binary Multimedia ESP32 Shield
    Bluetooth Media Control Sample Code

    Functions:
    Mechanical Key A: Click to go to the Previous Track.
    Mechanical Key B: Click to go to the Next Track.
    Rotary Encoder Click: Single click to Play/Pause.
    Rotary Encoder Double Click: Double click to Mute/Unmute.
    Rotary Encoder Long Press: Hold down to Lock the Screen.
    Rotary Encoder Turn Clockwise: Rotate clockwise to Increase Volume.
    Rotary Encoder Turn Counterclockwise: Rotate counterclockwise to Decrease Volume.

    Required Library:
    ESP32Encoder by Kevin Harrington
    OneButton by Matthias Hertel
    FastLED by Daniel Garcia
    ESP32-BLE-Keyboard
    https://github.com/T-vK/ESP32-BLE-Keyboard

 */
#include <Arduino.h>
#include <BleKeyboard.h>
#include <ESP32Encoder.h>
#include <OneButton.h>
#include <FastLED.h>

// Mechanical Keys
#define BTNA_PIN 34
#define BTNB_PIN 35

// Rotary Encoder
#define CLK 27
#define DT 33
#define SW 36

// RGB LED
#define RGB_PIN 32
#define NUM_LEDS 2
#define INCREASE true
#define DECREASE false

CRGB leds[NUM_LEDS];

ESP32Encoder encoder;

BleKeyboard bleKeyboard("ESP32 Multimedia Shield", "LONELY BINARY", 100);

// true - active low, false - active high
OneButton button(SW, true);
OneButton btna(BTNA_PIN, false);
OneButton btnb(BTNB_PIN, false);

// Rotary Encoder
int64_t oldPosition = 0;
int64_t newPosition = 0;
int64_t defaultPosition = 0;

// RGB millis() instead of delay()
unsigned long previousMillis = 0;  
const long interval = 1000;
int brightness = 100;    

void rgb_show(CRGB led0, CRGB led1)
{
  leds[0] = led0;
  leds[1] = led1;
  FastLED.show();
}

void rgb_random() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    
    CRGB randomColor = CRGB(random(255), random(255), random(255));
    rgb_show(randomColor, randomColor);

    previousMillis = currentMillis;   
  }
}

void click_a()
{
  rgb_show(CRGB::Blue, CRGB::Blue);
  if (bleKeyboard.isConnected())
  {
    bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
    Serial.println("Previous Track");
  }
  delay(200);
  rgb_show(CRGB::Black, CRGB::Black);
}

void click_b()
{
  rgb_show(CRGB::Green, CRGB::Green);
  if (bleKeyboard.isConnected())
  {
    bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
    Serial.println("Next Track");
  }
  delay(200);
  rgb_show(CRGB::Black, CRGB::Black);
}

void click()
{
  rgb_show(CRGB::Red, CRGB::Red);
  if (bleKeyboard.isConnected())
  {
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
    Serial.println("Play/Pause");
  }
  delay(200);
  rgb_show(CRGB::Black, CRGB::Black);
}

void doubleclick()
{
  rgb_show(CRGB::Yellow, CRGB::Yellow);
  if (bleKeyboard.isConnected())
  {
    bleKeyboard.write(KEY_MEDIA_MUTE);
    Serial.println("Mute/Unmute");
  }
  delay(200);
  rgb_show(CRGB::Black, CRGB::Black);
}

void longPress()
{ 
  rgb_show(CRGB::White, CRGB::White);
  if (bleKeyboard.isConnected())
  { 
    // Macbook Control + Command + Q
    Serial.println("Locking Screen...");
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_GUI); 
    bleKeyboard.press('q');
    bleKeyboard.releaseAll(); // Releases all keys
    delay(1000); // Delay to prevent repeated commands
  }
  delay(200);
  rgb_show(CRGB::Black, CRGB::Black);
}

// Increase and Decrease Brightness
void rgb_brightness(bool operation)
{
  if (operation)
  {
    brightness = brightness + 10;
  }
  else
  {
    brightness = brightness - 10;
  }

  if (brightness > 255)
  {
    brightness = 255;
  }
  else if (brightness < 0)
  {
    brightness = 0;
  }
  Serial.println("Set RGB LED brightness : " + String(brightness));
  FastLED.setBrightness(brightness);
  FastLED.show();
}

void setup()
{
  Serial.begin(115200);
  bleKeyboard.begin();

  encoder.attachHalfQuad(DT, CLK);
  encoder.setCount(defaultPosition);

  button.attachClick(click);
  button.attachDoubleClick(doubleclick);
  button.attachDuringLongPress(longPress);

  btna.attachClick(click_a);
  btnb.attachClick(click_b);

  FastLED.addLeds<NEOPIXEL, RGB_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
}

void loop()
{

  

  rgb_random();

  button.tick();

  btna.tick();
  btnb.tick();

  // Volume Up and Volume Down
  if (bleKeyboard.isConnected())
  {
    newPosition = encoder.getCount() / 2;

    if (newPosition > oldPosition)
    {
      bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
      rgb_brightness(INCREASE);
      delay(10);
    }
    else if (newPosition < oldPosition)
    {
      bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
      rgb_brightness(DECREASE);
      delay(10);
    }
    else
    {
      // Do nothing
    }

    oldPosition = newPosition;
  }
}