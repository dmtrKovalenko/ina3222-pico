#include <Adafruit_GFX.h>    // Adafruit LCD Graphics library
#include <Adafruit_ST7735.h> // ST7735 LCD Display library
#include <Arduino.h>
#include <INA3221.h>
#include <SPI.h> // Arduino SPI and I2C library
#include <Wire.h>

#define SERIAL_SPEED 115200 // serial baud rate
#define PRINT_DEC_POINTS 3  // decimal points to print

// pin definition for the 1.8", 128x160 ST7735 LCD Display on Raspberry Pico
// These can be connected to any GP Pin not in use
#define TFT_CS 9
#define TFT_RST 12
#define TFT_DC 8

// Used for SPI connectivity
#define TFT_SCK 10
#define TFT_MOSI 11

// Base layout offsets
#define TEXT_X_OFFSET 5
#define LINE_SIZE 13

// Sleep configs
#define CLOCK_SYNC_INTERVAL 10 // 24 * 60
#define SLEEP_INTERVAL 120

// Set I2C address to 0x41 (A0 pin -> VCC)
INA3221 ina_0(INA3221_ADDR40_GND);
// Just an example showing that you can add multiple INA3221 devices
INA3221 ina_1(INA3221_ADDR41_VCC);

// Setup the ST7735 LCD Display and variables
Adafruit_ST7735 tft =
    Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST);

void current_measure_init() {
  ina_0.begin(&Wire);
  ina_0.reset();
  ina_0.setShuntRes(10, 10, 10);

  ina_1.begin(&Wire);
  ina_1.reset();
  ina_1.setShuntRes(10, 10, 10);
}

void setup() {
  Wire.begin();
  Serial.begin(SERIAL_SPEED);
  current_measure_init();

  // Set shunt resistors to 10 mOhm for all channels
  // put your setup code here, to run once:
  tft.initR(INITR_GREENTAB);    // initialize a ST7735S chip, green tab
  tft.fillScreen(ST7735_BLACK); // Fill the screen with Black
  tft.setTextSize(1);           // Set the initial text size to 1
}

int channel_number(ina3221_ch_t channel) {
  switch (channel) {
  case INA3221_CH1:
    return 1;
  case INA3221_CH2:
    return 2;
  case INA3221_CH3:
    return 3;
  default:
    return -1;
  }
}

// It is not possible in reality that this values are negative, so we always
// minimise them to 0 to avoid negative values on the screen
#define min_zero(x) ((x) > 0 ? (x) : 0.0)

void render_channel(int y_offset, ina3221_ch_t channel) {
  float voltage = min_zero(ina_0.getVoltage(channel));
  float current = min_zero(ina_0.getCurrent(channel));
  String channel_name = String(channel_number(channel));

  Serial.println("Channel " + channel_name + ": " + (voltage) + "V " +
                 String(current) + "mA");

  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  tft.setTextSize(1);

  tft.setCursor(TEXT_X_OFFSET, y_offset);
  tft.print("Channel " + channel_name + ": ");

  tft.setCursor(TEXT_X_OFFSET, y_offset + LINE_SIZE);
  tft.print(String(voltage) + "V " + String(current, 2) + "mA");
}

void loop() {
  render_channel(LINE_SIZE, INA3221_CH1);
  render_channel(LINE_SIZE * 4, INA3221_CH2);
  render_channel(LINE_SIZE * 7, INA3221_CH3);

  // TODO deep sleep via native non-core api
  // https://github.com/matthias-bs/arduino-pico-sleep
  sleep_ms(333);
}
