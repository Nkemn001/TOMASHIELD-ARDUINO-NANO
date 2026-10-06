#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Forward Declarations
void drawMJPortrait();

void setup() {
  Serial.begin(115200);

  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  
  // Draw the Portrait
  drawMJPortrait();
  
  // Render to screen
  display.display();
}

void loop() {
  // Static art display, or add dynamic effects/animations here if desired
}

// --- Artistic Function: Stylized Michael Jackson Portrait ---
void drawMJPortrait() {
  // 1. Background Frame / Vignette Border
  display.drawRect(2, 2, 124, 60, SSD1306_WHITE);
  display.drawFastHLine(4, 56, 120, SSD1306_WHITE);

  // 2. The Signature Fedora Hat
  // Hat Brim (Wide slanted line)
  display.drawLine(34, 26, 94, 22, SSD1306_WHITE);
  display.drawLine(34, 27, 94, 23, SSD1306_WHITE); // Thicker brim
  
  // Hat Crown (Filled rounded shape / trapezoid)
  display.fillRoundRect(50, 8, 28, 16, 2, SSD1306_WHITE);
  // Hat Ribbon Band
  display.fillRect(50, 20, 28, 3, SSD1306_BLACK);

  // 3. Face Silhouette & Hair Curls
  // Face outline / jaw structure
  display.fillCircle(64, 38, 12, SSD1306_WHITE);
  
  // Carve out background to shape the head/neck
  display.fillCircle(64, 35, 11, SSD1306_BLACK); // Inner shadow/depth
  
  // Signature Curls framing the face
  display.fillCircle(52, 34, 3, SSD1306_WHITE);
  display.fillCircle(50, 40, 3, SSD1306_WHITE);
  display.fillCircle(76, 34, 3, SSD1306_WHITE);
  display.fillCircle(78, 40, 3, SSD1306_WHITE);

  // 4. Iconic Jacket Collar & Shoulders
  display.fillTriangle(64, 48, 30, 56, 45, 56, SSD1306_WHITE);
  display.fillTriangle(64, 48, 83, 56, 98, 56, SSD1306_WHITE);
  
  // Inner V-Neck / Shirt
  // (Using black triangles to carve out the collar shape)
  display.fillTriangle(64, 48, 55, 56, 73, 56, SSD1306_BLACK);

  // 5. Minimalist Title / Typography at the bottom
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(38, 57);
  display.print(F("KING OF POP"));
}