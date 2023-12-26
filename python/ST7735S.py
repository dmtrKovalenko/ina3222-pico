from machine import Pin, PWM, SPI
import framebuf
import time

BL = 12
DC = 13
RST = 17
MOSI = 7
SCK = 6
CS = 5


class LCD_1inch8(framebuf.FrameBuffer):
    def __init__(self):
        self.width = 160
        self.height = 128

        self.cs = Pin(CS, Pin.OUT)
        self.rst = Pin(RST, Pin.OUT)

        self.cs(1)
        self.spi = SPI(0)
        self.spi = SPI(0, 1000_000)
        self.spi = SPI(0, 10000_000, polarity=0, phase=0,
                       sck=Pin(SCK), mosi=Pin(MOSI), miso=None)
        self.dc = Pin(DC, Pin.OUT)
        self.dc(1)
        self.buffer = bytearray(self.height * self.width * 2)
        super().__init__(self.buffer, self.width, self.height, framebuf.RGB565)
        self.init_display()

        self.RED = 0x07E0
        self.GREEN = 0x001F
        self.BLUE = 0xF800
        self.WHITE = 0xFFFF
        self.BLACK = 0x0000
        self.YELLOW = 0xE0FF
        self.MAGENTA = 0x1FF8
        self.CYAN = 0xFF07

    def write_cmd(self, cmd):
        self.cs(1)
        self.dc(0)
        self.cs(0)
        self.spi.write(bytearray([cmd]))
        self.cs(1)

    def write_data(self, buf):
        self.cs(1)
        self.dc(1)
        self.cs(0)
        self.spi.write(bytearray([buf]))
        self.cs(1)

    def init_display(self):
        """Initialize display"""
        self.rst(1)
        self.rst(0)
        self.rst(1)

        self.write_cmd(0x36)
        self.write_data(0x70)

        self.write_cmd(0x3A)
        self.write_data(0x05)

        # ST7735R Frame Rate
        self.write_cmd(0xB1)
        self.write_data(0x01)
        self.write_data(0x2C)
        self.write_data(0x2D)

        self.write_cmd(0xB2)
        self.write_data(0x01)
        self.write_data(0x2C)
        self.write_data(0x2D)

        self.write_cmd(0xB3)
        self.write_data(0x01)
        self.write_data(0x2C)
        self.write_data(0x2D)
        self.write_data(0x01)
        self.write_data(0x2C)
        self.write_data(0x2D)

        self.write_cmd(0xB4)  # Column inversion
        self.write_data(0x07)

        # ST7735R Power Sequence
        self.write_cmd(0xC0)
        self.write_data(0xA2)
        self.write_data(0x02)
        self.write_data(0x84)
        self.write_cmd(0xC1)
        self.write_data(0xC5)

        self.write_cmd(0xC2)
        self.write_data(0x0A)
        self.write_data(0x00)

        self.write_cmd(0xC3)
        self.write_data(0x8A)
        self.write_data(0x2A)
        self.write_cmd(0xC4)
        self.write_data(0x8A)
        self.write_data(0xEE)

        self.write_cmd(0xC5)  # VCOM
        self.write_data(0x0E)

        # ST7735R Gamma Sequence
        self.write_cmd(0xe0)
        self.write_data(0x0f)
        self.write_data(0x1a)
        self.write_data(0x0f)
        self.write_data(0x18)
        self.write_data(0x2f)
        self.write_data(0x28)
        self.write_data(0x20)
        self.write_data(0x22)
        self.write_data(0x1f)
        self.write_data(0x1b)
        self.write_data(0x23)
        self.write_data(0x37)
        self.write_data(0x00)
        self.write_data(0x07)
        self.write_data(0x02)
        self.write_data(0x10)

        self.write_cmd(0xe1)
        self.write_data(0x0f)
        self.write_data(0x1b)
        self.write_data(0x0f)
        self.write_data(0x17)
        self.write_data(0x33)
        self.write_data(0x2c)
        self.write_data(0x29)
        self.write_data(0x2e)
        self.write_data(0x30)
        self.write_data(0x30)
        self.write_data(0x39)
        self.write_data(0x3f)
        self.write_data(0x00)
        self.write_data(0x07)
        self.write_data(0x03)
        self.write_data(0x10)

        self.write_cmd(0xF0)  # Enable test command
        self.write_data(0x01)

        self.write_cmd(0xF6)  # Disable ram power save mode
        self.write_data(0x00)

        # sleep out
        self.write_cmd(0x11)
        # DEV_Delay_ms(120);

        # Turn on the LCD display
        self.write_cmd(0x29)

    def show(self):
        self.write_cmd(0x2A)
        self.write_data(0x00)
        self.write_data(0x01)
        self.write_data(0x00)
        self.write_data(0xA0)

        self.write_cmd(0x2B)
        self.write_data(0x00)
        self.write_data(0x02)
        self.write_data(0x00)
        self.write_data(0x81)

        self.write_cmd(0x2C)

        self.cs(1)
        self.dc(1)
        self.cs(0)
        self.spi.write(self.buffer)
        self.cs(1)

    def backlight(self, value):
        pwm = PWM(Pin(BL))
        pwm.freq(1000)
        pwm.duty_u16(value)  # max 65535
