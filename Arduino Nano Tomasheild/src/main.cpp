#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define OLED parameters (128x64 display)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  // Initialize OLED display (Address 0x3C is standard for most 128x64 modules)
  // If nothing appears on screen, try changing 0x3C to 0x3D
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed. Check wiring!"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();

  // Draw some test text
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);          // Start at top-left corner
  display.println(F("OLED Test Successful!"));

  display.setCursor(0, 20);
  display.setTextSize(2);             // Larger text
  display.println(F("Nano Ready"));

  // Show the display buffer on the screen
  display.display();
}

void loop() {
  // Nothing to do here for a simple static test
}