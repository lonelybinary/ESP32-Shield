/*

    Lonely Binary Multimedia ESP32 Shield
    Mechanical Key Sample Code

    The Lonely Binary Multimedia ESP32 Shield features two mechanical keys, each covered by a crystal shield. Beneath this cover, there is an RGB LED powered by a WS2812 IC. The mechanical keys are configured with a pull-down connection to the ground. When a key is pressed, the corresponding digital IO pin registers high.

*/

#include <Arduino.h>

#define BTNA_PIN 34
#define BTNB_PIN 35

#define DEBOUNCE 200

void setup()
{

    Serial.begin(115200);

    pinMode(BTNA_PIN, INPUT);
    pinMode(BTNB_PIN, INPUT);

}

void loop()
{

if (digitalRead(BTNA_PIN) == HIGH)
  {
    Serial.println("Button A Pressed");
    delay(DEBOUNCE);
  } 

  if (digitalRead(BTNB_PIN) == HIGH)
  {
    Serial.println("Button B Pressed");
    delay(DEBOUNCE);
  }
}
