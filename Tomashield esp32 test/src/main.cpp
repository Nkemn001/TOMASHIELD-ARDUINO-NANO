#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for others
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT22 Settings
#define DHTPIN 4       // Digital pin connected to the DHT22 data pin
#define DHTTYPE DHT22  // Defining DHT 22
DHT dht(DHTPIN, DHTTYPE);

// Fan / Relay Settings
#define FAN_PIN 5      // Digital pin connected to the relay module

// Temperature Thresholds (in Celsius)
const float TEMP_ON = 28.0;   // Turn fan ON if temp reaches or exceeds this
const float TEMP_OFF = 25.0;  // Turn fan OFF if temp drops to or below this

void setup() {
  Serial.begin(115200);

  // Initialize pins
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW); // Ensure fan starts OFF

  // Initialize DHT sensor
  dht.begin();

  // Initialize the OLED display with address 0x3C
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();

  // Configure text properties
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner (x=0, y=0)
  
  // Write startup text to buffer
  display.println(F("System Initializing..."));
  display.display();
  delay(2000);
}

void loop() {
  // DHT22 requires at least 2 seconds between readings
  delay(2000);

  // Read humidity and temperature
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Clear the display buffer for the new frame
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);

  // Check if readings failed (sensor not detected / loose wire)
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    display.println(F("DHT readings not") );
    display.println(F("detected!"));
    display.display();
    return; // Skip the rest of the loop until the sensor is fixed
  }

  // Fan control logic with hysteresis
  if (temperature >= TEMP_ON) {
    digitalWrite(FAN_PIN, HIGH); // Turn Fan ON
  } else if (temperature <= TEMP_OFF) {
    digitalWrite(FAN_PIN, LOW);  // Turn Fan OFF
  }

  // Display Header
  display.println(F("ESP32 Climate Monitor"));
  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);

  // Temperature Reading
  display.setCursor(0, 18);
  display.print(F("Temp: "));
  display.setTextSize(2);
  display.setCursor(0, 28);
  display.print(temperature, 1);
  display.print((char)247); // Degree symbol
  display.print(F("C"));

  // Humidity Reading
  display.setTextSize(1);
  display.setCursor(75, 18);
  display.print(F("Humidity:"));
  display.setCursor(75, 28);
  display.print(humidity, 1);
  display.print(F("%"));

  // Fan Status Footer
  display.setCursor(0, 52);
  display.print(F("Fan Status: "));
  display.print(temperature >= TEMP_ON ? F("ON") : (temperature <= TEMP_OFF ? F("OFF") : F("Holding")));

  // Render everything onto the OLED screen
  display.display();
}