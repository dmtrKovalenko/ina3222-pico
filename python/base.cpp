// #include <Adafruit_ST7735.h>
// #include <Arduino.h>
// #include <INA3221.h>
// #include <Wire.h>
//
// #define SERIAL_SPEED 115200 // serial baud rate
// #define PRINT_DEC_POINTS 3  // decimal points to print
//
// // Set I2C address to 0x41 (A0 pin -> VCC)
// INA3221 ina_0(INA3221_ADDR40_GND);
// INA3221 ina_1(INA3221_ADDR41_VCC);
//
// void current_measure_init() {
//   ina_0.begin(&Wire);
//   ina_0.reset();
//   ina_0.setShuntRes(10, 10, 10);
//
//   ina_1.begin(&Wire);
//   ina_1.reset();
//   ina_1.setShuntRes(10, 10, 10);
// }
//
// void setup() {
//   Wire.begin();
//   Serial.begin(SERIAL_SPEED);
//   current_measure_init();
//
//   while (!Serial) {
//     delay(1);
//   }
//   // Set shunt resistors to 10 mOhm for all channels
// }
//
// int channel_number(ina3221_ch_t channel) {
//   switch (channel) {
//   case INA3221_CH1:
//     return 1;
//   case INA3221_CH2:
//     return 2;
//   case INA3221_CH3:
//     return 3;
//   case INA3221_CH_NUM:
//     return -1;
//   }
// }
//
// void display_info(ina3221_ch_t channel) {
//   float current = ina_0.getCurrent(channel);
//   float voltage = ina_0.getVoltage(channel);
//   int channel_num = channel_number(channel);
//
//   Serial.print("Channel ");
//   Serial.print(channel_num);
//   Serial.print(": ");
//
//   Serial.print(current, PRINT_DEC_POINTS);
//   Serial.print("mA ");
//   Serial.print(voltage, PRINT_DEC_POINTS);
//   Serial.println("V");
// }
//
// void loop() {
//   Serial.print("Now:");
//   Serial.println(millis());
//
//   display_info(INA3221_CH1);
//   display_info(INA3221_CH2);
//   display_info(INA3221_CH3);
//
//   Serial.println("--------------");
//
//   delay(1000);
// }
/**************************************************************************
  This is a library for several Adafruit displays based on ST77* drivers.

  Works with the Adafruit 1.8" TFT Breakout w/SD card
    ----> http://www.adafruit.com/products/358
  The 1.8" TFT shield
    ----> https://www.adafruit.com/product/802
  The 1.44" TFT breakout
    ----> https://www.adafruit.com/product/2088
  The 1.14" TFT breakout
  ----> https://www.adafruit.com/product/4383
  The 1.3" TFT breakout
  ----> https://www.adafruit.com/product/4313
  The 1.54" TFT breakout
    ----> https://www.adafruit.com/product/3787
  The 1.69" TFT breakout
    ----> https://www.adafruit.com/product/5206
  The 2.0" TFT breakout
    ----> https://www.adafruit.com/product/4311
  as well as Adafruit raw 1.8" TFT display
    ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams.
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional).

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 **************************************************************************/

// Load the Libraries
#include <Adafruit_GFX.h>    // Adafruit LCD Graphics library
#include <Adafruit_ST7735.h> // ST7735 LCD Display library
#include <SPI.h>             // Arduino SPI and I2C library

// pin definition for the 1.8", 128x160 ST7735 LCD Display on Raspberry Pico
// These can be connected to any GP Pin not in use
#define TFT_CS 9
#define TFT_RST 12
#define TFT_DC 8

// Used for SPI connectivity
#define TFT_SCK 10
#define TFT_MOSI 11
// #define TFT_MISO         // not used with this display

// Setup the ST7735 LCD Display and variables
Adafruit_ST7735 tft =
    Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST);

int textxoffset = 5; // move 5 pixels across to avoid the box
int textyoffset = 7; // move 7 pixels down to avoid the box

int tft_line1 = 0;
int tft_line4 = 39;
int tft_line5 = 52;
int tft_line6 = 65;
int tft_line7 = 78;
int tft_line8 = 91;

void setup() {
  // put your setup code here, to run once:
  tft.initR(INITR_BLACKTAB);    // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK); // Fill the screen with Black
  tft.setTextSize(1); // Set the initial text size to 1
  tft.setCursor(textxoffset + 0, textyoffset + 0); // Initial Text Location

  // Draw the 1.8" LED display layout using 24 bit colour (limitation of the
  // ST7735S library) tft.drawRect(0, 0, 159, 128, ST7735_CYAN);       // Draw a
  // Rectangle  x,y, across, down for the Colour Values
  tft.drawRoundRect(0, 0, 83, 31, 10,
                    ST7735_CYAN); // Draw a Rectangle  x,y, across, down with
                                  // corner & Colour Values
  tft.drawRoundRect(0, 35, 160, 93, 10,
                    ST7735_CYAN); // Draw a Rectangle  x,y, across, down with
                                  // corner & Colour Values
  tft.drawLine(
      80, 65, 80, 110,
      ST7735_CYAN); // Draw a mid-line  x1,y1, x2, y2 for the Colour Values

  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
  tft.setTextSize(1); // Set the text size to 1
  tft.setCursor(textxoffset + 54, textyoffset + tft_line1 + 1);
  tft.print("Test");
}

void loop() {
  // put your main code here, to run repeatedly:
}


