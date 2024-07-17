/*
    Lonely Binary IR Remote Shield with Remote

    Simple IR Receive

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
#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>

void setup() {
    Serial.begin(115200);
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
    Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
}

void loop() {
    /*
     * Check if received data is available and if yes, try to decode it.
     * Decoded result is in the IrReceiver.decodedIRData structure.
     *
     * E.g. command is in IrReceiver.decodedIRData.command
     * address is in command is in IrReceiver.decodedIRData.address
     * and up to 32 bit raw data in IrReceiver.decodedIRData.decodedRawData
     */
    if (IrReceiver.decode()) {

        /*
         * Print a summary of received data
         */
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
            // We have an unknown protocol here, print extended info
            IrReceiver.printIRResultRawFormatted(&Serial, true);
            IrReceiver.resume(); // Do it here, to preserve raw data for printing with printIRResultRawFormatted()
        } else {
            IrReceiver.resume(); // Early enable receiving of the next IR frame
            IrReceiver.printIRResultShort(&Serial);
            IrReceiver.printIRSendUsage(&Serial);
        }
        Serial.println();

        /*
         * Finally, check the received data and perform actions according to the received command
         */
        if (IrReceiver.decodedIRData.command == 0x10) {
            // do something
        } else if (IrReceiver.decodedIRData.command == 0x11) {
            // do something else
        }
    }
}