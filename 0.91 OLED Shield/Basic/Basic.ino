/*

Lonely Binary
0.91 OLED Shield for ESP32
Sample Code

Required Library:
U8G2 by oliver 

Board Type:
ESP32 Dev Module

*/
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#define BTN 39

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

bool isPressed(int min, int max)
{
  int value = analogRead(BTN);
  if ((value <= max) && (value >= min))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool leftPressed()
{
  return isPressed(500,700);
}

bool rightPressed()
{
  return isPressed(750,900);
}

bool downPressed()
{
  return isPressed(1600,2000);
}

bool upPressed()
{
  return isPressed(1000,1300);
}

bool centerPressed()
{
  return isPressed(4095,4095);
}

void setup(void)
{
  pinMode(BTN, INPUT);

  u8g2.begin();
  u8g2.clearBuffer();
  // Font List: https://github.com/olikraus/u8g2/wiki/fntlistallplain
  u8g2.setFont(u8g2_font_courR12_tf); 
  u8g2.drawStr(0, 14, "LONELY BINARY");
  u8g2.drawStr(0, 32, " 0.91\" OLED");
  u8g2.sendBuffer();  
}

void loop(void)
{
  String message ="";
  if (leftPressed()) message = "LEFT";
  if (rightPressed()) message = "RIGHT";
  if (upPressed()) message = "UP";
  if (downPressed()) message = "DOWN";
  if (centerPressed()) message = "CENTER";

  if (message != "") {
    u8g2.clearBuffer(); 
    u8g2.setFont(u8g2_font_logisoso24_tf);
    u8g2.drawStr(0, 30, message.c_str()); 
    u8g2.sendBuffer(); 
  }

  delay(200);
}
