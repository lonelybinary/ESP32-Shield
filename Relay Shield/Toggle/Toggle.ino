
/*

    Lonely Binary Single Relay ESP32 Shield
    Simple Demo Code

*/

#include <Arduino.h>

// Active High
#define RELAY_PIN 13

void setup() {
    Serial.begin(115200);
    while(!Serial);
    Serial.println("Lonely Binary Relay ESP32 Shield Demo Code");

    pinMode(RELAY_PIN,OUTPUT);
    digitalWrite(RELAY_PIN,LOW); // off
}

void loop() {
    digitalWrite(RELAY_PIN, !digitalRead(RELAY_PIN)); // toggle
    Serial.println(digitalRead(RELAY_PIN)?"ON":"OFF");
    delay(3000);
}