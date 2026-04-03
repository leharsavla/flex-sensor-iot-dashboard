
# Flex Sensor IoT Dashboard

## What it does
Reads a flex sensor bend angle in real time, controls a servo motor, 
and streams live data to a Node-RED dashboard over MQTT.

## Hardware used
- ESP32 Dev Kit V1
- Flex sensor
- Servo motor
- 10kΩ resistor
- Breadboard and jumpers

## Tech stack
- Firmware: Arduino C++
- Protocol: MQTT over TLS
- Broker: HiveMQ Cloud
- Dashboard: Node-RED

## How it works
Flex sensor → ESP32 reads analog value → maps to servo angle → 
publishes to HiveMQ via MQTT → Node-RED receives and displays on gauge.

## Dashboard screenshot
[add your screenshot here]
