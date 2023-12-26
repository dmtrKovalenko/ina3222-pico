# from st7735 import TFT
from ST7735S import LCD_1inch8
import machine

print("Hello, World!")

lcd = LCD_1inch8()

TEMT = machine.ADC(26)
temt = int(TEMT.read_u16()/2)

lcd.backlight(temt)

lcd.fill(lcd.WHITE)
lcd.rect(0, 24, 160, 15, lcd.WHITE)
lcd.line(79, 39, 79, 128, lcd.WHITE)
lcd.line(0, 86, 160, 86, lcd.WHITE)

# spi = SPI(1, baudrate=20000000, sck=Pin(10), mosi=Pin(11), miso=Pin(12))
# tft = TFT(spi, 7, 8, 9)

# Print "Hello, World!" in white color
# tft.text((0, 0), "Hello World!", TFT.PURPLE, sysfont, 2, nowrap=True)
