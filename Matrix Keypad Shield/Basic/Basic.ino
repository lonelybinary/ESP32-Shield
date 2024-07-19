
/*
    Lonely Binary ESP32 I2C Matrix KeyPad Shield

    The Lonely Binary ESP32 I2C Matrix KeyPad Shield is a 3x4 matrix keypad that can be connected to an ESP32 microcontroller via I2C. The shield is designed to be easy to use and integrate into your projects, making it ideal for hobbyists and professionals alike. With its compact size and simple interface, this shield opens up endless possibilities for automation and control applications.

    The shield uses the PCF8574 I2C I/O expander to communicate with the ESP32 microcontroller. The SDA and SCL pins are connected to GPIO21 and GPIO22 respectively.

    The INT GPIO16 is interrupt output pin. The INT pin provides a way for the PCF8574 to signal the microcontroller that an input change has occurred on any of its I/O pins. When any of the input pins change state (from high to low or low to high), the INT pin is pulled low, alerting the microcontroller to read the updated input values from the PCF8574. This allows for efficient monitoring of input changes without the need for continuous polling of the I/O pins.

    Pins Assignment:
    SDA  GPIO 21
    SCL  GPIO 22
    INT  GPIO 16

    Library:
    I2CKeyPad
    https://github.com/RobTillaart/I2CKeyPad

*/

#include <Arduino.h>
#include "I2CKeyPad.h"

#define I2C_KEYPAD_ADDRESS 0x38
#define DEBOUNCE 300
#define INT_PIN 16

I2CKeyPad keyPad(I2C_KEYPAD_ADDRESS);
char keys[] = "123A456B789C*0#DNF"; //  N = NoKey, F = Fail

void setup()
{
    Serial.begin(115200);
    pinMode(INT_PIN, INPUT_PULLUP);
    Wire.begin();
    keyPad.begin();
}

void loop()
{
    if (digitalRead(INT_PIN) == LOW)
    {
        uint8_t index = keyPad.getKey();

        if (index != I2C_KEYPAD_NOKEY)
        {
            Serial.println(keys[index]);
            switch (keys[index])
            {
            case '1':
                // Do something
                break;
            case '2':
                // Do something
                break;
            case '3':
                // Do something
                break;
            case '4':
                // Do something
                break;
            case '5':
                // Do something
                break;
            case '6':
                // Do something
                break;
            case '7':
                // Do something
                break;
            case '8':
                // Do something
                break;
            case '9':
                // Do something
                break;
            case '0':
                // Do something
                break;
            case '*':
                // Do something
                break;
            case '#':
                // Do something
                break;
            default:
                break;
            }
            delay(DEBOUNCE);
        }
    }

    delay(5);
}



    

