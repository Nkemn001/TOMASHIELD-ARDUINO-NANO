# TOMASHIELD-ARDUINO-NANO
# TomaGuard (TOMA-GUARD Monitor)

An embedded environmental monitoring and climate control module designed to track temperature and humidity levels in real time. It features an SSD1306 OLED dashboard display and automated cooling fan regulation via a MOSFET driver using hysteresis logic.

---

## Features
* **Real-Time Environmental Tracking:** Accurately reads ambient temperature and relative humidity using a DHT22 sensor.
* **OLED Visual Interface:** Displays live sensor data, system initialization states, and current cooling status on a 128x64 I2C SSD1306 display.
* **Smart Hysteresis Fan Control:** Prevents rapid relay/fan switching by utilizing upper and lower temperature thresholds (`TEMP_ON` and `TEMP_OFF`).
* **Fault Handling:** Automatically detects sensor disconnection or read failures and displays warning alerts on both the OLED screen and Serial Monitor.

---

## Hardware Pin Mapping

| Component | Pin / Interface | Description |
| :--- | :--- | :--- |
| **DHT22 Sensor** | Digital Pin 4 | Data line for temperature and humidity acquisition |
| **Cooling Fan (MOSFET)** | Digital Pin 5 | Gate pin connected via a $220\Omega$ resistor to control 12V fan load |
| **OLED Display** | I2C (`SDA`, `SCL`) | 128x64 display communicating at I2C address `0x3C` |

---

## Control Logic & Thresholds
The system uses temperature hysteresis to manage climate stability:
* **Turn Fan ON:** When temperature reaches or exceeds **$28.0^\circ\text{C}$** (`TEMP_ON`).
* **Turn Fan OFF:** When temperature drops to or below **$25.0^\circ\text{C}$** (`TEMP_OFF`).
* **Holding State:** Maintains the previous operational state when temperature is between $25.0^\circ\text{C}$ and $28.0^\circ\text{C}$.

---

## Required Libraries
To compile and run this project, make sure you have the following libraries installed in your development environment (PlatformIO or Arduino IDE):
* **Adafruit GFX Library**
* **Adafruit SSD1306**
* **DHT Sensor Library** (by Adafruit)

---

## Getting Started

1. Clone or download this project into your workspace.
2. Open the project folder in **PlatformIO** or the **Arduino IDE**.
3. Verify that your required dependencies are listed in your `platformio.ini` or installed via the Arduino Library Manager.
4. Connect your hardware components according to the [Pin Mapping](#hardware-pin-mapping) table above.
5. Build and upload the code to your microcontroller board.
