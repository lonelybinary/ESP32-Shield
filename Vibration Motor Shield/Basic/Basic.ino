
/*

    Lonely Binary Vibrating Motor ESP32 Shield
    Simple Demo Code

*/

#include <Arduino.h>

// Active High
#define MOTOR_PIN 13

void setup() {
    Serial.begin(115200);
    while(!Serial);
    Serial.println("Lonely Binary Vibrating Motor Demo Code");

    pinMode(MOTOR_PIN,OUTPUT);
}

void loop() {
    digitalWrite(MOTOR_PIN, !digitalRead(MOTOR_PIN)); // toggle
    delay(1000);
}