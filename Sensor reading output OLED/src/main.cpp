#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 5      // Digital pin connected to the DHT22 data pin
#define DHTTYPE DHT22 // Define DHT 22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000); // Give serial monitor time to open
  dht.begin();

  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  Serial.println(F("System initialized. Waiting for sensor readings..."));
}

void loop() {
  // Wait 2 seconds between measurements (DHT22 reading frequency)
  delay(2000);

  // Read humidity
  float h = dht.readHumidity();
  // Read temperature as Celsius (default)
  float t = dht.readTemperature();

  // Check if readings failed and exit early to try again
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Error: Failed to read from DHT sensor!"));
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println(F("Sensor Error!"));
    display.display();
    return;
  }

  // --- Print to Serial Monitor ---
  Serial.print(F("Humidity: "));
  Serial.print(h, 1);
  Serial.print(F("%  |  Temperature: "));
  Serial.print(t, 1);
  Serial.println(F("°C"));

  // --- Update OLED Display ---
  display.clearDisplay();

  // --- Temperature Section ---
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(F("TEMP:"));

  display.setTextSize(2); 
  display.setCursor(0, 12);
  display.print(t, 1);    
  display.print((char)247); 
  display.println(F("C"));

  // --- Humidity Section ---
  display.setTextSize(1);
  display.setCursor(0, 36);
  display.print(F("HUMIDITY:"));

  display.setTextSize(2); 
  display.setCursor(0, 48);
  display.print(h, 1);
  display.println(F("%"));

  // Send everything to the screen
  display.display();
}