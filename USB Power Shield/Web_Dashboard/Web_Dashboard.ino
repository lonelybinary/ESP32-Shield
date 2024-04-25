/*

    Lonely Binary USB Power ESP32 Shield
    Web Server Controller Sample Code

    Required Library:
    ESP-DASH by Ayush Sharma
    AsyncTCP by dvarrel
    ESPAsyncWebServer by lacamera
    ArduinoJson by Benoit

    Board Type: 
    ESP32 Dev Module

    JP1: Power Source Jumper
    By default, devices connected via USB draw power from the DC jack, 
    with a maximum USB load limit of 2A. The ESP32 is powered through 
    its onboard USB port. You can link the DC jack to the ESP32's 5V 
    input by soldering the jumper JP1 on the back of the board. Once 
    this is done, you can power both the USB load and the ESP32 either
     through the DC jack or the USB port on the ESP32. Ensure that 
     the power supply is consistently 5V.

    CAUTION:
    Ensure the power supply can provide adequate current for both 
    the ESP32 and the connected load to prevent the ESP32 from 
    crashing or malfunctioning.

*/

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>

/* Your WiFi Credentials */
const char *ssid = "WIFI_SSID";   // SSID
const char *password = "WIFI_PASSWORD"; // Password

/* MOSFET pin */
#define SWITCH 13

/* PWM settings */ 
const int freq = 5000;
const int channel = 0;
const int resolution = 8;

/* Start Webserver */
AsyncWebServer server(80);

/* Attach ESP-DASH to AsyncWebServer */
ESPDash dashboard(&server);

/* Dashboard Cards */
Card switch_card(&dashboard, BUTTON_CARD, "Fan Switch");
Card intensive(&dashboard, SLIDER_CARD, "Intensive", "%", 0, 100, 1);

/* Global Variables */
float intensive_value = 100; // 0-100
bool switch_state = false;   // false = off, true = on

void pwm(int dutyCycle)
{
    ledcWrite(channel, dutyCycle);
    Serial.println("PWM Duty Cycle: " + String(dutyCycle));
}

void switch_on()
{
    // 100% duty cycle
    pwm(map(intensive_value, 0, 100, 0, 255));
    Serial.println("Switch ON");
}

void switch_off()
{
    // 0% duty cycle
    pwm(0);
    Serial.println("Switch OFF");
}

void switch_card_callback(int value)
{
    Serial.println("Switch Button Callback Triggered: " + String((value == 1) ? "true" : "false"));

    /* update global switch_state */
    switch_state = (value == 1) ? true : false;

    if (switch_state)
    {
        // ON
        switch_on();
    }
    else
    { // OFF
        switch_off();
    }

    switch_card.update(value);
    dashboard.sendUpdates();
}

void intensive_callback(int value)
{
    Serial.println("Intensive Slider Callback Triggered: " + String(value));

    /* update global intensive_value */
    intensive_value = value;

    if (switch_state) switch_on();

    intensive.update(value);
    dashboard.sendUpdates();
}

void setup()
{
    Serial.begin(115200);

    /* pwm setup */
    ledcSetup(channel, freq, resolution);
    ledcAttachPin(SWITCH, channel);

    /* Connect WiFi */
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.printf("WiFi Failed!\n");
        return;
    }
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    /* Start AsyncWebServer */
    server.begin();

    /* Set to default values */
    intensive.update(intensive_value);
    switch_card.update(switch_state);
    dashboard.sendUpdates();
    switch_off();

    /* Attach callback functions */
    switch_card.attachCallback(switch_card_callback);
    intensive.attachCallback(intensive_callback);
}

void loop()
{
}