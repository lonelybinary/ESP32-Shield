/*
  LONELY BINARY
  ESP32 0.96 TFT SHIELD DEMO CODE

  Library: 
  TFT-ESPI by Bodmer
  Github: https://github.com/Bodmer/TFT_eSPI/

  You have to modify "User_Setup.h" in the TFT_eSPI folder to the following:

  #define ST7735_DRIVER 

  #define TFT_HEIGHT 160
  #define TFT_WIDTH  80
  #define ST7735_GREENTAB160x80

  #define TFT_MOSI 23
  #define TFT_SCLK 18 
  #define TFT_CS   15  
  #define TFT_DC    2  
  #define TFT_RST  -1  

  #define LOAD_FONT2
  #define SMOOTH_FONT

*/

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>



#define BTN 39
#define WIDTH 160
#define HEIGHT 80

TFT_eSPI tft = TFT_eSPI();

int x = 0;
int y = 0;

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
  return isPressed(500, 700);
}

bool rightPressed()
{
  return isPressed(750, 900);
}

bool downPressed()
{
  return isPressed(1600, 2000);
}

bool upPressed()
{
  return isPressed(1000, 1300);
}

bool centerPressed()
{
  return isPressed(4095, 4095);
}

void showPosition()
{

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  int offset = 2;
  tft.setCursor(x + 2, y + 2);
  String message = "(X:" + String(x) + ",Y:" + String(y) + ")";
  tft.print(message.c_str());

  tft.drawLine(x, 0, x, HEIGHT, TFT_RED);
  tft.drawLine(0, y, WIDTH, y, TFT_RED);

  tft.setTextColor(TFT_BLACK, TFT_GREENYELLOW);
  tft.drawString("LONELY BINARY", x + 5, y - 20, 2);
}

void showLogo() {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.drawString("LONELY BINARY", x, y, 2);
}


void setup(void)
{ 
  Serial.begin(115200);
  pinMode(BTN, INPUT);
  
  tft.init();
  tft.setRotation(1);

  tft.fillScreen(TFT_RED);
  delay(1000);
  tft.fillScreen(TFT_GREEN);
  delay(1000);
  tft.fillScreen(TFT_BLUE);
  delay(1000);

}


void loop()
{

  if (leftPressed())
  {
    x = x - 1;
    showPosition();
  }
  if (rightPressed())
  {
    x = x + 1;
    showPosition();
  }
  if (upPressed())
  {
    y = y - 1;
    showPosition();
  }
  if (downPressed())
  {
    y = y + 1;
    showPosition();
  }
  if (centerPressed())
  {
    showLogo();
  }

  delay(10);
}
