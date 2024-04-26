/*
    Lonely Binary Multimedia ESP32 Shield
    Mechanical Key Sample Code

    The most challenging aspect in basic examples is handling button debounce. The unsightly delay method can block the code. Instead, consider using the millis function or employing the OneButton library. The OneButton library manages button debounce effectively and supports the detection of various events, such as single, double, and multiple clicks, as well as prolonged presses. This functionality allows you to repurpose the same button for multiple actions.

    Required Library:
    OneButton by Matthias Hertel
*/

#include <Arduino.h>
#include <OneButton.h>

#define BTN1_PIN 34
#define BTN2_PIN 35


// true - active low, false - active high
OneButton button1(BTN1_PIN, false);
OneButton button2(BTN2_PIN, false);

void click1() {
  Serial.println("Button 1 click.");
}

void doubleclick1() {
  Serial.println("Button 1 doubleclick.");
}

void longPressStart1() {
  Serial.println("Button 1 longPress start");
}

void longPress1() {
  Serial.println("Button 1 longPress...");
}

void longPressStop1() {
  Serial.println("Button 1 longPress stop");
}

void click2() {
  Serial.println("Button 2 click.");
}

void doubleclick2() {
  Serial.println("Button 2 doubleclick.");
}

void longPressStart2() {
  Serial.println("Button 2 longPress start");
}

void longPress2() {
  Serial.println("Button 2 longPress...");
}

void longPressStop2() {
  Serial.println("Button 2 longPress stop");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting TwoButtons...");

  button1.attachClick(click1);
  button1.attachDoubleClick(doubleclick1);
  button1.attachLongPressStart(longPressStart1);
  button1.attachLongPressStop(longPressStop1);
  button1.attachDuringLongPress(longPress1);

  button2.attachClick(click2);
  button2.attachDoubleClick(doubleclick2);
  button2.attachLongPressStart(longPressStart2);
  button2.attachLongPressStop(longPressStop2);
  button2.attachDuringLongPress(longPress2);

}

void loop() {
  button1.tick();
  button2.tick();

  delay(10);
}


