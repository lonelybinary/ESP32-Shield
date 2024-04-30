/*
    Lonely Binary 3-Bit VGA Shield
    Demo Code

    The Lonely Binary VGA ESP32 Shield utilizes the ESP32's I²S peripheral, originally designed for audio, to output VGA video with precise timing for RGB color data synchronization. 
    
    Two models are available: the 3-Bit VGA Shield, which uses 5 digital GPIO pins and less memory, making it suitable for text output and projects requiring additional device connections; and the 14-Bit VGA Shield, which uses 16 GPIO pins and more memory, ideal for graphics-intensive applications and vivid color displays but with fewer available GPIOs. 
    
    These shields are versatile for various applications, from educational tools to digital signage, especially when VGA output is needed on larger screens.

    Required Libraries:
    ESP32Lib by bitluni

    Boards:
    ESP32 Dev Module

    CAUTION:
    The large resolutions may cause the ESP32 to crash.
    The recommended resolution is MODE320x240.
    You may need to remove the shield before uploading the code.

*/

#include <Arduino.h>
#include <ESP32Lib.h>
#include <Ressources/Font8x8.h>

//pin configuration
const int redPin = 14;
const int greenPin = 19;
const int bluePin = 27;
const int hsyncPin = 32;
const int vsyncPin = 33;

const int width = 320;
const int height = 240;
const int font_width = 8;
const int font_height = 8;

int x = 0;
int y = 0;
int line_number = -4;

//VGA Device
VGA3Bit vga;

void setup() {
  //initializing vga at the specified pins
  vga.init(vga.MODE320x240, redPin, greenPin, bluePin, hsyncPin, vsyncPin);

  //set the font
  vga.setFont(Font8x8);

  //Red Background
  vga.clear(vga.RGB(255, 0, 0));

  //White Text, Red Background
  vga.setTextColor(vga.RGB(255, 255, 255), vga.RGB(255, 0, 0));

  String brand = "LONELY BINARY";
  x = (width - brand.length() * font_width) / 2;
  y = (height) / 2 + font_height * line_number;
  vga.setCursor(x, y);
  vga.println(brand.c_str());

  String product = "ESP32 VGA SHIELD";
  line_number = line_number + 2;
  x = (width - product.length() * font_width) / 2;
  y = (height) / 2 + font_height * line_number;
  vga.setCursor(x, y);
  vga.println(product.c_str());

  String model = "3-Bit Mode";
  line_number = line_number + 2;
  x = (width - model.length() * font_width) / 2;
  y = (height) / 2 + font_height * line_number;
  vga.setCursor(x, y);
  vga.println(model.c_str());

  String url = "www.lonelybinary.com";
  line_number = line_number + 6;
  x = (width - url.length() * font_width) / 2;
  y = (height) / 2 + font_height * line_number;
  vga.setCursor(x, y);
  vga.println(url.c_str());
}

void loop() {
}