/*

    Lonely Binary USB Power ESP32 Shield
    Basic USB power intensive control Sample Code

    JP1: Power Source Jumper
    By default, devices connected via USB draw power from the DC jack, with a maximum USB load limit of 2A. The ESP32 is powered through its onboard USB port. You can link the DC jack to the ESP32's 5V input by soldering the jumper JP1 on the back of the board. Once this is done, you can power both the USB load and the ESP32 either through the DC jack or the USB port on the ESP32. Ensure that the power supply is consistently 5V.

    CAUTION:
    Ensure the power supply can provide adequate current for both the ESP32 and the connected load to prevent the ESP32 from crashing or malfunctioning.

*/

#include <Arduino.h>

#define SWITCH 13

void switch_on()
{
    digitalWrite(SWITCH, HIGH);
    Serial.println("Switch ON");
}

void switch_off()
{
    digitalWrite(SWITCH, LOW);
    Serial.println("Switch OFF");
}

void switch_toggle()
{
    digitalWrite(SWITCH, !digitalRead(SWITCH));
    Serial.println("Switch Toggled");

}

void setup(void)
{
    Serial.begin(115200);
    pinMode(SWITCH, OUTPUT);

    switch_off();
}

void loop(void)
{
    switch_on();
    delay(5000);

    switch_off();
    delay(5000);

    switch_toggle();
    delay(5000);

    switch_toggle();
    delay(5000);
}
