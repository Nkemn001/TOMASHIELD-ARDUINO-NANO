#include <Arduino.h>

#include <FastLED.H>

// --- Configuration ---
#define LED_PIN     4      // Change this if you wired your data line to a different GPIO pin
#define NUM_LEDS    10     // Change this to match the exact number of LEDs on your strip segment
#define BRIGHTNESS  100    // Set brightness from 0 (off) to 255 (full blast)
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB    // Most WS2812B strips use GRB order

CRGB leds[NUM_LEDS];

void setup() {
  // Initialize serial monitor for debugging
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting RGB LED Strip Test...");

  // Initialize FastLED library
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  // Test 1: Solid RED
  Serial.println("Color: Red");
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(1000);

  // Test 2: Solid GREEN
  Serial.println("Color: Green");
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(1000);

  // Test 3: Solid BLUE
  Serial.println("Color: Blue");
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(1000);

  // Test 4: Chasing effect (One pixel running down the strip)
  Serial.println("Running chase effect...");
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White; // Turn current LED white
    FastLED.show();
    delay(100);
    leds[i] = CRGB::Black; // Turn it off before moving to the next
  }
}