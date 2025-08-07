# ESP32 Multi-Sensor Project

ESP32 project with MQ2 gas sensor, HC-SR04 ultrasonic, I2C LCD, buzzer, and LED control using FreeRTOS.

## Hardware

| Component | Pin |
|-----------|-----|
| MQ2 Sensor | GPIO32 |
| HC-SR04 | Trig: GPIO23, Echo: GPIO5 |
| LCD I2C | SDA/SCL (0x27) |
| Buzzer | GPIO15 |
| LED | GPIO14 |
| LED Blink | GPIO12 |
| Button ON/OFF | GPIO2/GPIO18 |
| Button SEM | GPIO27 |

## Libraries
- LiquidCrystal_I2C
- HCSR04 (gamegine/HCSR04)

## Usage
1. Install libraries and upload code to ESP32
2. ON/OFF buttons control main LED
3. SEM button blinks LED 3 times (semaphore)
4. LCD shows gas levels and distance every 1s
5. Buzzer plays Super Mario theme

## License
MIT License
