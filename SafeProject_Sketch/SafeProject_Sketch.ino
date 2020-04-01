/*
  $$$$$$$$\                        $$\        $$$$$$\             $$$$$$\
  $$  _____|                       $$ |      $$  __$$\           $$  __$$\
  $$ |    $$$$$$\   $$$$$$\   $$$$$$$ |      $$ /  \__| $$$$$$\  $$ /  \__|$$$$$$\
  $$$$$\ $$  __$$\ $$  __$$\ $$  __$$ |      \$$$$$$\   \____$$\ $$$$\    $$  __$$\
  $$  __|$$ /  $$ |$$ /  $$ |$$ /  $$ |       \____$$\  $$$$$$$ |$$  _|   $$$$$$$$ |
  $$ |   $$ |  $$ |$$ |  $$ |$$ |  $$ |      $$\   $$ |$$  __$$ |$$ |     $$   ____|
  $$ |   \$$$$$$  |\$$$$$$  |\$$$$$$$ |      \$$$$$$  |\$$$$$$$ |$$ |     \$$$$$$$\
  \__|    \______/  \______/  \_______|       \______/  \_______|\__|      \_______|

  By Alex Eastabrook - Converting a Digital Safe into a Food Fortress.
  Inspired by the Covid-19 crisis and too much junk food around the house.
*/

/**************************************************************************
  OLED Library by :
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
#include "Logos.h"
#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'A', '0', 'B'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 3, 4, 6, 8 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 2, 5, 7 };

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void printOpen();
void printSecure();
void printClock(uint16_t h, uint16_t m, uint16_t s);
void printArmSafe();
void printPromptTimeEntry();
void printArmSafe(int H1 , int H2, int M1, int M2) ;

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();

}

uint32_t GetTimeEntry()
{
  char Keys[4] = {'0', '0', '0', '0'};
  char Input = 0;

  while (Input != 'A')
  {
    char KeyPress = kpd.waitForKey();
    if (KeyPress == 'A')
    {
      break;
    }
    else if (KeyPress == 'B')
    {
      return 0;
    }
    else
    {
      Keys[3] =      Keys[2];
      Keys[2] =      Keys[1];
      Keys[1] =      Keys[0];
      Keys[0] =       KeyPress;
      printArmSafe(Keys[3]  - '0', Keys[2]  - '0' , Keys[1]  - '0' , Keys[0]  - '0' );

    }
  }

  uint32_t SecondsToCount = 0;

  //  Tens of Hours
  SecondsToCount += (Keys[3]  - '0') * 36000;
  //  Hours
  SecondsToCount += (Keys[2]  - '0') * 3600;
  //  Tens of Minutes
  SecondsToCount += (Keys[1]  - '0') * 600;
  //  Minutes
  SecondsToCount += (Keys[0]  - '0') * 60;

  return SecondsToCount;

}

void RelayOpen()
{
  Serial.println("Sweeeets");

}
void loop() {
  printOpen();
  char key = 0;
  while (key != 'A')
  {
    key = kpd.getKey();
    delay(50);

    if (key == 'B')
    {
      RelayOpen();
    }
  }

  printPromptTimeEntry();
  delay(200);
  printArmSafe();
  uint32_t SecondsForLockdown = GetTimeEntry();

  if (SecondsForLockdown > 0)
  {
    printSecure();
  }
  for (uint32_t seconds = SecondsForLockdown; seconds > 0; seconds--)
  {
    uint32_t t; uint32_t h; uint16_t m; uint32_t s;

    t = seconds;
    s = t % 60;

    t = (t - s) / 60;
    m = t % 60;

    t = (t - m) / 60;
    h = t;

    printClock(h, m, s);

    if (seconds > 3600)
    {
      seconds -= 60;
    }
    else if (seconds > 60)
    {
      seconds -= 15;
    }
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
}


void printSecure() {
  display.clearDisplay(); // Clear the display buffer
  display.drawBitmap(0, 0, Secured, 128, 32, SSD1306_WHITE);
  display.invertDisplay(true);
  display.display(); // Show the display buffer on the screen
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
    sprintf(data, "%02dH:%02dM", h, m);
    display.println(data);
  }
  else
  {
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setCursor(36, 16);            // Start at top-left corner
    //display.println(F("24H:32M"));
    sprintf(data, "%02dM:%02dS", m, s);
    display.println(data);
  }
  display.display(); // Show the display buffer on the screen
  delay(5);

}
void printPromptTimeEntry() {
  char data[20];
  display.clearDisplay(); // Clear the display buffer
  display.drawBitmap(0, 0, ArmSafe, 128, 32, SSD1306_WHITE);
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text

  //  display.fillRect(34, 0, display.width() - 34, display.height(), SSD1306_BLACK);


  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setCursor(52, 0);            // Start at top-left corner
  sprintf(data, "Lock", 0, 0);
  display.println(data);

  display.setCursor(52, 18);            // Start at top-left corner
  sprintf(data, "Time", 0, 0);
  display.println(data);

  display.invertDisplay(false);

  display.display(); // Show the display buffer on the screen
  delay(2000);        // Pause for 1/10 second
}



void printArmSafe() {
  char data[20];
  display.clearDisplay(); // Clear the display buffer
  display.drawBitmap(0, 0, ArmSafe, 128, 32, SSD1306_WHITE);
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text

  display.fillRect(34, 0, display.width() - 34, display.height(), SSD1306_BLACK);


  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setCursor(36, 10);            // Start at top-left corner
  //display.println(F("24H:32M"));
  sprintf(data, "%02dH:%02dM", 0, 0);
  display.println(data);
  display.invertDisplay(false);

  display.display(); // Show the display buffer on the screen

}






void printArmSafe(int H1 , int H2, int M1, int M2) {
  char data[20];
  display.clearDisplay(); // Clear the display buffer
  display.drawBitmap(0, 0, ArmSafe, 128, 32, SSD1306_WHITE);
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text

  display.fillRect(34, 0, display.width() - 34, display.height(), SSD1306_BLACK);


  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setCursor(36, 10);            // Start at top-left corner
  sprintf(data, "%01d%01dH:%01d%01dM", H1, H2, M1, M2);
  display.println(data);
  display.invertDisplay(false);
  display.display(); // Show the display buffer on the screen

}
