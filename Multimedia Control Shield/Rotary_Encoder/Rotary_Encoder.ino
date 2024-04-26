/*
    Lonely Binary Multimedia ESP32 Shield
    Rotary Encoder Sample Code

    A rotary encoder is an input device that converts the rotational position or motion of a shaft or axle to an analog or digital code. There are two main types of rotary encoders: absolute and incremental. The incremental type, which is commonly used with Arduino projects, outputs a signal each time the shaft rotates a certain amount, letting you track motion, direction, and position.

    Required Library:
    ESP32Encoder by Kevin Harrington
*/

#include <Arduino.h>
#include <ESP32Encoder.h>

#define CLK 27 // CLK ENCODER
#define DT 33  // DT ENCODER
#define SW 36  // Center button

ESP32Encoder encoder;

int64_t oldPosition = 0;
int64_t newPosition = 0;
int64_t defaultPosition = 0;
void setup()
{
  Serial.begin(115200);
  // Wait until Serial is ready
  while (!Serial)
    ;

  pinMode(SW, INPUT_PULLUP);
  encoder.attachHalfQuad(DT, CLK);
  encoder.setCount(defaultPosition);
}

void loop()
{
  if (digitalRead(SW) == LOW)
  {
    Serial.println("Reset Position");
    encoder.setCount(defaultPosition);
    delay(300); // Debounce
  }

  newPosition = encoder.getCount() / 2;

  if (newPosition != oldPosition)
    Serial.println(newPosition);

  oldPosition = newPosition;

  delay(10);
}