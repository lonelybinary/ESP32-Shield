/*

    Lonely Binary Vibrating Motor ESP32 Shield
    Using PWM to Regulate the Intensity of a Vibrating Motor
        
    PWM (Pulse Width Modulation) is a technique used to control the power delivered to electrical devices and is particularly useful in applications like motor control, LED dimming, and signal generation. The ESP32 microcontroller supports PWM on many of its GPIO pins, making it highly versatile for various applications.

*/

#include <Arduino.h>

// Active High
#define MOTOR_PIN 13

/* PWM settings */
const int freq = 5000;
const int channel = 0;
const int resolution = 8;

void pwm(int dutyCycle)
{
    ledcWrite(channel, dutyCycle);
    Serial.println("PWM Duty Cycle: " + String(dutyCycle));
}

void motor_on()
{
    // 100% duty cycle
    pwm(255);
    Serial.println("Switch ON");
}

void motor_off()
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
    pinMode(MOTOR_PIN, OUTPUT);

    ledcSetup(channel, freq, resolution);
    ledcAttachPin(MOTOR_PIN, channel);

}

void loop(void)
{
    pwm_loop_test();
    delay(2000);

    motor_on();
    delay(2000);

    motor_off();
    delay(1000);
}
