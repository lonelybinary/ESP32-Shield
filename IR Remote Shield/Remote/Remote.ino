/*
    Lonely Binary IR Remote Shield with Remote

    Enhance your Arduino projects with the versatile Lonely Binary Infrared IR Shield with Remote. This advanced shield empowers your devices to both receive and transmit IR signals, offering seamless integration with a wide range of home appliances. Whether you're looking to control your TV, air conditioner, or any other IR-enabled device, this shield provides a robust solution for duplicating and managing remote signals effortlessly.

    The Lonely Binary Infrared IR Shield includes an elegant remote featuring a sleek, user-friendly design that complements any setup. Its simplicity ensures easy operation and integration into your existing projects without hassle. Ideal for hobbyists and professionals alike, this shield opens up endless possibilities for automation and remote control applications.

    Pins Assignment:
    RECEIVE GPIO 0
    SEND  GPIO 4  

    Library:
    Infrared4Arduino
    https://github.com/bengtmartensson/Infrared4Arduino

*/
#include <Arduino.h>
#include <IRremote.hpp>
#include "PinDefinitionsAndMore.h"

#define DEBBOUNCE_DELAY 100
#define ENABLE_DEBUG false

void command();

void setup()
{
    Serial.begin(115200);

    // Wait for the serial connection to be established
    delay(5000);
    Serial.println("Lonely Binary IR Remote Shiled Demo Code");

    IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
    printActiveIRProtocols(&Serial);
}


void loop()
{

    if (IrReceiver.decode())
    {
        if (IrReceiver.decodedIRData.protocol != UNKNOWN)
        {
            IrReceiver.resume(); // Early enable receiving of the next IR frame

            if (ENABLE_DEBUG) IrReceiver.printIRResultShort(&Serial);

            command();

        }
    }
}

void command()
{   
    if (IrReceiver.decodedIRData.decodedRawData == 0x0) return;
    switch (IrReceiver.decodedIRData.command)
    {
    case 0xC:
        Serial.println("Power");
        break;
    case 0xF:
        Serial.println("Input");
        break;
    case 0xD:
        Serial.println("Mute");
        break;
    case 0x42:
        Serial.println("Up");
        break;
    case 0x46:
        Serial.println("Enter");
        break;
    case 0x43:
        Serial.println("Down");
        break;
    case 0x44:
        Serial.println("Left");
        break;
    case 0x45:
        Serial.println("Right");
        break;
    case 0x78:
        Serial.println("Home");
        break;
    case 0x5B:
        Serial.println("Back");
        break;
    case 0x11:
        Serial.println("Menu");
        break;
    case 0x14:
        Serial.println("Volumn Up");
        break;
    case 0x15:
        Serial.println("Volumn Down");
        break;
    case 0x9C:
        Serial.println("Search");
        break;
    case 0xB2:
        Serial.println("Red");
        break;
    case 0xB3:
        Serial.println("Green");
        break;
    case 0xB4:
        Serial.println("Blue");
        break;
    }
    
    delay(DEBBOUNCE_DELAY);
}