/*
    Lonely Binary ESP32 Touch Sensor Shield

    The Lonely Binary ESP32 Touch Sensor Shield features 3 touch pads and 3 corresponding LEDs to indicate touch activation.

    The ESP32 microcontroller features capacitive touch sensing, which allows it to detect touch on specific pins without the need for additional hardware. The touch sensors detect changes in capacitance caused by a human finger or other conductive objects.

    The ESP32 includes multiple touch-capable pins. Th touch pins is mapped to normal GPIO pins.

    Touch Pin	GPIO Number
    T0	        GPIO 4
    T1	        GPIO 0
    T2	        GPIO 2
    T3	        GPIO 15
    T4	        GPIO 13
    T5	        GPIO 12
    T6	        GPIO 14
    T7	        GPIO 27
    T8	        GPIO 33
    T9	        GPIO 32

    The sensitivity of the touch sensors can be adjusted by setting a threshold value. When the capacitance on a touch pin exceeds this threshold, it is considered a touch event. at this example, we speicify a threshold value of 30.

    Pin Assignment:
    Touch Pad A -  T3 - GPIO 15
    Touch Pad B -  T2 - GPIO 2
    Touch Pad C -  T0 - GPIO 4

    LED A - GPIO 27
    LED B - GPIO 14
    LED C - GPIO 13
*/

#include <Arduino.h>

#define TOUCH_A T3 // GPIO 15
#define TOUCH_B T2 // GPIO 2
#define TOUCH_C T0 // GPIO 4

#define LED_A 27
#define LED_B 14
#define LED_C 13

void touchLed(int touchPin, int ledPin);

void setup()
{
    Serial.begin(115200);
    Serial.println("Lonely Binary ESP32 Touch Shield");

    pinMode(LED_A, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(LED_C, OUTPUT);

    digitalWrite(LED_A, LOW);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_C, LOW);
}

void loop()
{
    touchLed(TOUCH_A, LED_A);
    touchLed(TOUCH_B, LED_B);
    touchLed(TOUCH_C, LED_C);
}

void touchLed(int touchPin, int ledPin)
{
    int touchValue = touchRead(touchPin);
    if (touchValue < 30)
    {
        digitalWrite(ledPin, HIGH);
        delay(50);
    }
    else
    {
        digitalWrite(ledPin, LOW);
    }
}