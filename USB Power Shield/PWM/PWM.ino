/*

    Lonely Binary USB Power ESP32 Shield
    PWM USB power intensive control Sample Code

    PWM (Pulse Width Modulation) is a technique used to control the power delivered to electrical devices and is particularly useful in applications like motor control, LED dimming, and signal generation. The ESP32 microcontroller supports PWM on many of its GPIO pins, making it highly versatile for various applications.

    JP1: Power Source Jumper
    By default, devices connected via USB draw power from the DC jack, with a maximum USB load limit of 2A. The ESP32 is powered through its onboard USB port. You can link the DC jack to the ESP32's 5V input by soldering the jumper JP1 on the back of the board. Once this is done, you can power both the USB load and the ESP32 either through the DC jack or the USB port on the ESP32. Ensure that the power supply is consistently 5V.

    CAUTION:
    Ensure the power supply can provide adequate current for both the ESP32 and the connected load to prevent the ESP32 from crashing or malfunctioning.

*/

#include <Arduino.h>

#define SWITCH 13

/* PWM settings */
const int freq = 5000;
const int channel = 0;
const int resolution = 8;

void pwm(int dutyCycle)
{
    ledcWrite(channel, dutyCycle);
    Serial.println("PWM Duty Cycle: " + String(dutyCycle));
}

void switch_on()
{
    // 100% duty cycle
    pwm(255);
    Serial.println("Switch ON");
}

void switch_off()
{
    // 0% duty cycle
    pwm(0);
    Serial.println("Switch OFF");
}   

void pwm_loop_test()
{

    for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
    {
        pwm(dutyCycle);
        delay(30);
    }

    for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
    {
        pwm(dutyCycle);
        delay(30);
    }
}

void setup(void)
{
    Serial.begin(115200);
    pinMode(SWITCH, OUTPUT);

    ledcSetup(channel, freq, resolution);
    ledcAttachPin(SWITCH, channel);

    pwm_loop_test();
}

void loop(void)
{
    switch_on();
    delay(5000);

    switch_off();
    delay(5000);
}
