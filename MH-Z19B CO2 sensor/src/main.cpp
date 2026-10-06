#include <Arduino.h>

// For CO2 Sensor to work alone


// #include <Arduino.h>
// #include <MHZ19.h>

// // Define hardware serial pins for ESP32 (Serial2)
// const int rx_pin = 16; // Connect to MH-Z19B TX pin
// const int tx_pin = 17; // Connect to MH-Z19B RX pin

// MHZ19 myMHZ19;

// void setup() {
//   // Start standard hardware serial for debugging (Serial Monitor)
//   Serial.begin(115200);
//   while (!Serial);

//   // Initialize Serial2 for the sensor (9600 baud is default for MH-Z19B)
//   Serial2.begin(9600, SERIAL_8N1, rx_pin, tx_pin);

//   myMHZ19.begin(Serial2);          // Pass the Serial2 stream to the sensor object
//   myMHZ19.autoCalibration(false);  // Disable auto-baseline calibration (optional for strict testing)

//   Serial.println("\nMH-Z19B CO2 Sensor Initializing...");
//   Serial.println("Warning: The sensor requires about 3 minutes of warm-up time to provide accurate data.");
// }

// void loop() {
//   int co2ppm = myMHZ19.getCO2();         // Read CO2 concentration in ppm
//   int temperature = myMHZ19.getTemperature(); // Read built-in thermistor temperature

//   // Print data to the Serial Monitor
//   Serial.print("CO2 Concentration: ");
//   Serial.print(co2ppm);
//   Serial.print(" ppm\t");
  
//   Serial.print("Temperature: ");
//   Serial.print(temperature);
//   Serial.println(" °C");

//   // MH-Z19 recommendations suggest not querying faster than every 2-5 seconds
//   delay(5000);
// }


// For Web dashboard
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <MHZ19.h>

// Replace with your network credentials
const char* ssid     = "Skill G Innovation";
const char* password = "INNOV8HUB";

// MH-Z19B Pins (Serial2)
const int rx_pin = 16; 
const int tx_pin = 17; 

MHZ19 myMHZ19;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// HTML template with embedded JavaScript for real-time updates
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 CO2 Monitor</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; background-color: #f4f7f6; margin-top: 50px; }
    .card { background: white; padding: 20px; border-radius: 10px; box-shadow: 0px 4px 10px rgba(0,0,0,0.1); display: inline-block; margin: 10px; width: 250px; }
    h1 { color: #333; }
    .value { font-size: 28px; font-weight: bold; color: #007BFF; }
  </style>
</head>
<body>
  <h1>ESP32 MH-Z19B CO2 Monitor</h1>
  
  <div class="card">
    <h3>CO2 Concentration</h3>
    <p><span id="co2" class="value">--</span> ppm</p>
  </div>
  
  <div class="card">
    <h3>Temperature</h3>
    <p><span id="temp" class="value">--</span> &deg;C</p>
  </div>

  <script>
    setInterval(function () {
      // Fetch CO2
      fetch('/co2')
        .then(response => response.text())
        .then(data => { document.getElementById('co2').innerHTML = data; });

      // Fetch Temperature
      fetch('/temperature')
        .then(response => response.text())
        .then(data => { document.getElementById('temp').innerHTML = data; });
    }, 3000); // Update every 3 seconds
  </script>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);

  // Initialize MH-Z19B Sensor
  Serial2.begin(9600, SERIAL_8N1, rx_pin, tx_pin);
  myMHZ19.begin(Serial2);
  myMHZ19.autoCalibration(false);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP Address: http://");
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Route to get current CO2
  server.on("/co2", HTTP_GET, [](AsyncWebServerRequest *request){
    int co2ppm = myMHZ19.getCO2();
    request->send(200, "text/plain", String(co2ppm));
  });

  // Route to get current Temperature
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    int temperature = myMHZ19.getTemperature();
    request->send(200, "text/plain", String(temperature));
  });

  // Start server
  server.begin();
}

void loop() {
  // Nothing needed here because AsyncWebServer runs on background tasks!
}