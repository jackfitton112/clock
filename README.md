# Project Saturn
GPS based 7-segment display clock.


## Contents

- [Introduction](#introduction)
- [Hardware](#hardware)
- [Schematic](#schematic)
- [Software](#software)
- [Assembly](#assembly)


## Introduction
This project is a GPS based 7-segment display clock. The clock is driven by a GPS module which provides the time and date information. The GPS module is connected to a microcontroller which processes the data and drives the 7-segment display. The display is made up of 8 7-segment displays. The MAX7219 LED driver is controlled by the microcontroller.

## Hardware

The hardware components used in this project are:
- ESP32 SuperMini [Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-c3-mini-1_datasheet_en.pdf)
- MAX7219 LED Driver [Datasheet](https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf)
- 2x Common Cathode 4x 7-segments display [Datasheet](https://www.sparkfun.com/datasheets/Components/LED/7-Segment/YSD-439AR6B-35.pdf)
- Ublox NEO-6M GPS Module [Datasheet](https://www.u-blox.com/sites/default/files/products/documents/NEO-6_DataSheet_(GPS.G6-HW-09005).pdf)
- 2x Push Buttons

## Schematic
The schematic for the project is shown below:
![alt text](image/7seg.svg)

## Software
For ease of development, an Arduino library has been created to interact with the MAX7219 LED driver. The following commands are supported:

TODO

## Assembly

TODO




