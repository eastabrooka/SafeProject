/**************************************************************************
  This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

  This example is for a 128x32 pixel display using I2C to communicate
  3 pins are required to interface (two I2C and one reset).

  Adafruit invests time and resources providing this open
  source code, please support Adafruit and open-source
  hardware by purchasing products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries,
  with contributions from the open source community.
  BSD license, check license.txt for more information
  All text above, and the splash screen below must be
  included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


const unsigned char Open [] PROGMEM =
{
  // 'Open - Copy', 128x32px
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
  0xff, 0xff, 0xff, 0xf0, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
  0xff, 0xff, 0xff, 0xc0, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
  0xff, 0xff, 0xff, 0x87, 0xc3, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
  0xff, 0xff, 0xff, 0x1f, 0xf1, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xff, 0xff, 0xff, 0x3f, 0xf9, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xff, 0xff, 0xff, 0x3f, 0xf9, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xff, 0xff, 0xff, 0x3f, 0xf9, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xff, 0xff, 0xff, 0x3f, 0xf9, 0xf8, 0x3f, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xff, 0xff, 0xff, 0x3f, 0xf9, 0xf8, 0x3f, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xff, 0xff, 0xff, 0x3f, 0xf9, 0xf8, 0x3f, 0xfe, 0x3c, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xff, 0xff, 0xff, 0x3f, 0xf9, 0xf8, 0x3f, 0xfe, 0x7e, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xff, 0xff, 0xff, 0x3f, 0xf9, 0xf8, 0x3f, 0xfc, 0xff, 0x3b, 0x0f, 0xc3, 0xe8, 0x7f, 0xfe, 0x1f,
  0xff, 0xff, 0xfe, 0x3f, 0xfd, 0xf8, 0x3f, 0xfc, 0xff, 0x38, 0x47, 0x19, 0xe2, 0x3f, 0xfe, 0x1f,
  0xfe, 0x00, 0x00, 0x0f, 0xf9, 0xf8, 0x3f, 0xfc, 0xff, 0x39, 0xe7, 0x3c, 0xe7, 0xbf, 0xfe, 0x1f,
  0xfe, 0x00, 0x00, 0x07, 0xff, 0xf8, 0x3f, 0xfc, 0xff, 0x3b, 0xe7, 0x7c, 0xef, 0x9f, 0xfe, 0x1f,
  0xfc, 0x00, 0x00, 0x07, 0xff, 0xf8, 0x3f, 0xfc, 0xff, 0x3b, 0xf6, 0x00, 0xef, 0x9f, 0xfe, 0x1f,
  0xfc, 0x00, 0xe0, 0x07, 0xff, 0xf8, 0x3f, 0xfc, 0xff, 0x3b, 0xe6, 0x7f, 0xef, 0x9f, 0xfe, 0x1f,
  0xfc, 0x01, 0xf0, 0x07, 0xff, 0xf8, 0x3f, 0xfc, 0x7e, 0x7b, 0xe6, 0x7f, 0xef, 0x9f, 0xfe, 0x1f,
  0xfc, 0x01, 0xf8, 0x07, 0xff, 0xf8, 0x3f, 0xfe, 0x7e, 0x79, 0xe7, 0x3f, 0xef, 0x9f, 0xfe, 0x1f,
  0xfc, 0x01, 0xf8, 0x07, 0xff, 0xf8, 0x3f, 0xff, 0x18, 0xf8, 0xcf, 0x1c, 0xef, 0x9f, 0xfe, 0x1f,
  0xfc, 0x01, 0xf0, 0x07, 0xff, 0xf8, 0x3f, 0xff, 0x81, 0xf8, 0x1f, 0x81, 0xef, 0x9f, 0xfe, 0x1f,
  0xfc, 0x00, 0xf0, 0x07, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xfc, 0x00, 0xe0, 0x07, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xfc, 0x00, 0xe0, 0x07, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xfc, 0x00, 0xe0, 0x07, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xfc, 0x00, 0xe0, 0x07, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xfc, 0x00, 0x00, 0x07, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xfc, 0x00, 0x00, 0x07, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
  0xfe, 0x00, 0x00, 0x07, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
  0xfe, 0x00, 0x00, 0x07, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
  0xff, 0x00, 0x00, 0x0f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f
};

const unsigned char Secured [] PROGMEM =
{
  // 'Secured- Copy', 128x32px
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
  0xff, 0xf0, 0x03, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
  0xff, 0xe0, 0x00, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
  0xff, 0xc3, 0xf8, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
  0xff, 0xcf, 0xfc, 0x7f, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xff, 0xcf, 0xfe, 0x7f, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xff, 0xcf, 0xfe, 0x7f, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xff, 0xcf, 0xfe, 0x7f, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xff, 0xcf, 0xfe, 0x7f, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xff, 0xcf, 0xfe, 0x7f, 0xff, 0xf8, 0x3c, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf2, 0x1f,
  0xff, 0xcf, 0xfe, 0x7f, 0xff, 0xf8, 0x30, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf2, 0x1f,
  0xff, 0xcf, 0xfe, 0x7f, 0xff, 0xf8, 0x23, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf2, 0x1f,
  0xff, 0xcf, 0xfe, 0x7f, 0xff, 0xf8, 0x27, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf2, 0x1f,
  0xff, 0x80, 0x00, 0x3f, 0xff, 0xf8, 0x27, 0xfe, 0x0f, 0xc3, 0x9e, 0x72, 0x38, 0x3e, 0x12, 0x1f,
  0xfe, 0x00, 0x00, 0x0f, 0xff, 0xf8, 0x23, 0xfc, 0xc7, 0x19, 0x9e, 0x70, 0x33, 0x1c, 0x42, 0x1f,
  0xfc, 0x00, 0x00, 0x07, 0xff, 0xf8, 0x30, 0xf9, 0xe7, 0x3f, 0x9e, 0x71, 0xe7, 0x9c, 0xf2, 0x1f,
  0xfc, 0x00, 0x00, 0x07, 0xff, 0xf8, 0x3c, 0x39, 0xf7, 0x3f, 0x9e, 0x73, 0xe7, 0xdd, 0xf2, 0x1f,
  0xfc, 0x00, 0xe0, 0x07, 0xff, 0xf8, 0x3f, 0x18, 0x06, 0x7f, 0x9e, 0x73, 0xe0, 0x19, 0xf2, 0x1f,
  0xfc, 0x01, 0xf0, 0x07, 0xff, 0xf8, 0x3f, 0x99, 0xfe, 0x7f, 0x9e, 0x73, 0xe7, 0xf9, 0xf2, 0x1f,
  0xfc, 0x03, 0xf0, 0x07, 0xff, 0xf8, 0x3f, 0x99, 0xff, 0x7f, 0x9e, 0x73, 0xe7, 0xfd, 0xf2, 0x1f,
  0xfc, 0x03, 0xf0, 0x07, 0xff, 0xf8, 0x3f, 0x99, 0xff, 0x3d, 0x9e, 0x73, 0xe7, 0xfc, 0xf2, 0x1f,
  0xfc, 0x01, 0xf0, 0x07, 0xff, 0xf8, 0x24, 0x3c, 0xf7, 0x19, 0x88, 0x73, 0xf3, 0xdc, 0x42, 0x1f,
  0xfc, 0x00, 0xe0, 0x07, 0xff, 0xf8, 0x20, 0x7e, 0x07, 0x83, 0xc2, 0x73, 0xf8, 0x1e, 0x12, 0x1f,
  0xfc, 0x00, 0xe0, 0x07, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xfc, 0x00, 0xe0, 0x07, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xfc, 0x00, 0xe0, 0x07, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xfc, 0x00, 0xe0, 0x07, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xfc, 0x00, 0x00, 0x07, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f,
  0xfc, 0x00, 0x00, 0x07, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
  0xfc, 0x00, 0x00, 0x07, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
  0xfe, 0x00, 0x00, 0x0f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
  0xff, 0x00, 0x00, 0x3f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f
};

const unsigned char Clock [] PROGMEM =
{

  // 'Clock', 34x32px
  0xff, 0xf8, 0x07, 0xff, 0xc0, 0xff, 0xc0, 0x00, 0xff, 0xc0, 0xff, 0x00, 0x00, 0x3f, 0xc0, 0xfe,
  0x03, 0xf0, 0x1f, 0xc0, 0xfc, 0x1f, 0xfe, 0x0f, 0xc0, 0xf8, 0x3f, 0xff, 0x07, 0xc0, 0xf0, 0xff,
  0xff, 0xc3, 0xc0, 0xe1, 0xff, 0xff, 0xe1, 0xc0, 0xe1, 0xfe, 0x3f, 0xe1, 0xc0, 0xc3, 0xfe, 0x3f,
  0xf0, 0xc0, 0xc7, 0xfe, 0x3f, 0xf8, 0xc0, 0xc7, 0xfe, 0x3f, 0xf8, 0xc0, 0x87, 0xfe, 0x3f, 0xf8,
  0x40, 0x8f, 0xfe, 0x3f, 0xfc, 0x40, 0x8f, 0xfe, 0x3f, 0xfc, 0x40, 0x8f, 0xfe, 0x3f, 0xfc, 0x40,
  0x8f, 0xfe, 0x3f, 0xfc, 0x40, 0x8f, 0xfe, 0x0f, 0xfc, 0x40, 0x8f, 0xff, 0x87, 0xfc, 0x40, 0x87,
  0xff, 0xe1, 0xf8, 0x40, 0xc7, 0xff, 0xf0, 0x78, 0xc0, 0xc7, 0xff, 0xfc, 0xf8, 0xc0, 0xc3, 0xff,
  0xfe, 0xf0, 0xc0, 0xe1, 0xff, 0xff, 0xe1, 0xc0, 0xe1, 0xff, 0xff, 0xe1, 0xc0, 0xf0, 0xff, 0xff,
  0xc3, 0xc0, 0xf8, 0x3f, 0xff, 0x07, 0xc0, 0xfc, 0x1f, 0xfe, 0x0f, 0xc0, 0xfe, 0x03, 0xf0, 0x1f,
  0xc0, 0xff, 0x00, 0x00, 0x3f, 0xc0, 0xff, 0xc0, 0x00, 0xff, 0xc0, 0xff, 0xf8, 0x07, 0xff, 0xc0
};

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void printOpen();
void printSecure();
void printClock(uint16_t h, uint16_t m, uint16_t s);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.display();
  display.clearDisplay();
}

void loop() {
  printOpen();
  printSecure();
  for (int seconds = 7400; seconds > 0; seconds--)
  {
    uint32_t t; uint16_t h; uint8_t m; uint8_t s;

    t = seconds;
    s = t % 60;

    t = (t - s) / 60;
    m = t % 60;

    t = (t - m) / 60;
    h = t;

    printClock(h, m, s);
  }
}

#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2

void printOpen() {
  display.clearDisplay(); // Clear the display buffer
  display.drawBitmap(0, 0, Open, 128, 32, SSD1306_WHITE);
  display.invertDisplay(true);
  display.display(); // Show the display buffer on the screen
  delay(2000);        // Pause for 1/10 second
}

void printSecure() {
  display.clearDisplay(); // Clear the display buffer
  display.drawBitmap(0, 0, Secured, 128, 32, SSD1306_WHITE);
  display.invertDisplay(true);
  display.display(); // Show the display buffer on the screen
  delay(2000);        // Pause for 1/10 second
}

void printClock(uint16_t h, uint16_t m, uint16_t s) {
  char data[20];
  display.clearDisplay(); // Clear the display buffer
  display.drawBitmap(0, 0, Clock, 34, 32, SSD1306_WHITE);
  display.fillRect(34, 0, display.width() - 34, display.height(), SSD1306_WHITE);
  display.invertDisplay(true);
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_BLACK);        // Draw white text
  display.setCursor(36, 0);            // Start at top-left corner
  display.println(F("Time Remaining"));

  if (h > 0)
  {
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setCursor(36, 16);            // Start at top-left corner
    //display.println(F("24H:32M"));
    sprintf(data, "%dH:%dM", h, m);
    display.println(data);
  }
  else
  {
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setCursor(36, 16);            // Start at top-left corner
    //display.println(F("24H:32M"));
    sprintf(data, "%dM:%dS", m, s);
    display.println(data);
  }
  display.display(); // Show the display buffer on the screen
  delay(5);

}
