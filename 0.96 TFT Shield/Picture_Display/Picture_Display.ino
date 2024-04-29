// Sketch to display images on a 160 x 128 TFT

// Renders images stored in an array in program (FLASH)
// The JPEG images are stored in header files (see jpeg1.h etc.)

// As well as the TFT_eSPI library:
// https://github.com/Bodmer/TFT_eSPI
// the sketch needs the JPEG Decoder library. This can be loaded via the Library Manager.
// or can be downloaded here:
// https://github.com/Bodmer/JPEGDecoder

/*
  LONELY BINARY
  ESP32 0.96 TFT SHIELD JPG Display DEMO CODE

  Library: 
  TFT_ESPI by Bodmer
  https://github.com/Bodmer/TFT_eSPI/
  JPEGDecoder by Bodmer
  https://github.com/Bodmer/JPEGDecoder

  The jpg needs to be converted and saved into .h header file. 
  https://tomeko.net/online_tools/file_to_hex.php?lang=en

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
#include <SPI.h>
#include <TFT_eSPI.h>
#include <JPEGDecoder.h>

#include "lonelybinary.h"
#include "cybertruck.h"
#include "model3.h"
#include "modely.h"
#include "modelx.h"
#include "models.h"

#define BTN 39

int car_index = -1;
int max_car = 4;


TFT_eSPI tft = TFT_eSPI();

// Return the minimum of two values a and b
#define minimum(a, b) (((a) < (b)) ? (a) : (b))

void renderJPEG(int xpos, int ypos)
{

    // retrieve information about the image
    uint16_t *pImg;
    uint16_t mcu_w = JpegDec.MCUWidth;
    uint16_t mcu_h = JpegDec.MCUHeight;
    uint32_t max_x = JpegDec.width;
    uint32_t max_y = JpegDec.height;

    // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
    // Typically these MCUs are 16x16 pixel blocks
    // Determine the width and height of the right and bottom edge image blocks
    uint32_t min_w = minimum(mcu_w, max_x % mcu_w);
    uint32_t min_h = minimum(mcu_h, max_y % mcu_h);

    // save the current image block size
    uint32_t win_w = mcu_w;
    uint32_t win_h = mcu_h;

    // record the current time so we can measure how long it takes to draw an image
    uint32_t drawTime = millis();

    // save the coordinate of the right and bottom edges to assist image cropping
    // to the screen size
    max_x += xpos;
    max_y += ypos;

    // read each MCU block until there are no more
    while (JpegDec.readSwappedBytes())
    {

        // save a pointer to the image block
        pImg = JpegDec.pImage;

        // calculate where the image block should be drawn on the screen
        int mcu_x = JpegDec.MCUx * mcu_w + xpos; // Calculate coordinates of top left corner of current MCU
        int mcu_y = JpegDec.MCUy * mcu_h + ypos;

        // check if the image block size needs to be changed for the right edge
        if (mcu_x + mcu_w <= max_x)
            win_w = mcu_w;
        else
            win_w = min_w;

        // check if the image block size needs to be changed for the bottom edge
        if (mcu_y + mcu_h <= max_y)
            win_h = mcu_h;
        else
            win_h = min_h;

        // copy pixels into a contiguous block
        if (win_w != mcu_w)
        {
            uint16_t *cImg;
            int p = 0;
            cImg = pImg + win_w;
            for (int h = 1; h < win_h; h++)
            {
                p += mcu_w;
                for (int w = 0; w < win_w; w++)
                {
                    *cImg = *(pImg + w + p);
                    cImg++;
                }
            }
        }

        // draw image MCU block only if it will fit on the screen
        if ((mcu_x + win_w) <= tft.width() && (mcu_y + win_h) <= tft.height())
        {
            tft.pushRect(mcu_x, mcu_y, win_w, win_h, pImg);
        }
        else if ((mcu_y + win_h) >= tft.height())
            JpegDec.abort(); // Image has run off bottom of screen so abort decoding
    }
}

void drawArrayJpeg(const uint8_t arrayname[], uint32_t array_size)
{

    int x = 0;
    int y = 0;

    JpegDec.decodeArray(arrayname, array_size);
    renderJPEG(x, y);
}

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

void setup()
{
    Serial.begin(115200);
    pinMode(BTN, INPUT);

    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    drawArrayJpeg(LonelyBinary, sizeof(LonelyBinary));
}

void showCar()
{
    if (car_index < 0)
    {
        car_index = max_car;
    }
    if (car_index > max_car)
    {
        car_index = 0;
    }
    switch (car_index)
    {
    case 0:
        drawArrayJpeg(CyberTruck, sizeof(CyberTruck));
        break;
    case 1:
        drawArrayJpeg(Model3, sizeof(Model3));
        break;
    case 2:
        drawArrayJpeg(ModelY, sizeof(ModelY));
        break;
    case 3:
        drawArrayJpeg(ModelX, sizeof(ModelX));
        break;
    case 4:
        drawArrayJpeg(ModelS, sizeof(ModelS));
        break;
    }

    delay(300); // button debounce time
}

void order()
{
    if (car_index < 0)
        return;

    String line1 = "ORDERED";
    switch (car_index)
    {
    case 0:
        line1 = "CyberTruck";
        break;
    case 1:
        line1 = "Model 3";
        break;
    case 2:
        line1 = "Model Y";
        break;
    case 3:
        line1 = "Model X";
        break;
    case 4:
        line1 = "Model S";
        break;
    }

    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_RED, TFT_YELLOW);
    tft.drawString(line1, 0, 0, 4);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("ORDERED", 0, 30, 4);
    tft.drawString("PLACED", 0, 60, 4);

    delay(300); // button debounce time
}

void info()
{
    if (car_index < 0)
        return;

    String line1 = "CyberTruck Info";
    switch (car_index)
    {
    case 0:
        line1 = "CyberTruck Info";
        break;
    case 1:
        line1 = "Model 3 Info";
        break;
    case 2:
        line1 = "Model Y Info";
        break;
    case 3:
        line1 = "Model X Info";
        break;
    case 4:
        line1 = "Model S Info";
        break;
    }

    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.drawString(line1, 0, 0, 2);

    delay(300); // button debounce time
}

void price()
{
    if (car_index < 0)
        return;

    String line1 = "Tesla Price Guide";
    String line2 = "Model";
    String line3 = "Tesla Price Guide";
    switch (car_index)
    {
    case 0:
        line1 = "CyberTruck";
        line2 = "CyberBeast All-wheel";
        line3 = "$99,999";
        break;
    case 1:
        line1 = "Model 3";
        line2 = "2024 Highland";
        line3 = "$64,769";
        break;
    case 2:
        line1 = "Model Y";
        line2 = "Rear-wheel Drive";
        line3 = "$69,899";
        break;
    case 3:
        line1 = "Model X";
        line2 = "Long Range All-wheel";
        line3 = "$86,399";
        break;
    case 4:
        line1 = "Model S";
        line2 = "Performance All-Wheel";
        line3 = "$69,459";
        break;
    }

    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(line1, 0, 0, 4);
    tft.drawString(line2, 0, 26, 2);
    tft.setTextColor(TFT_RED, TFT_YELLOW);
    tft.drawString(line3, 0, 50, 4);

    delay(300); // button debounce time
}

void loop()
{
    if (leftPressed())
    {
        car_index = car_index - 1;
        showCar();
    }

    if (rightPressed())
    {
        car_index = car_index + 1;
        showCar();
    }

    if (upPressed())
    {
        info();
    }
    if (downPressed())
    {
        price();
    }

    if (centerPressed())
    {
        order();
    }

}
