# M5Cardputer Movement Detector Alarm

 An alarm system using the M5Cardputer platform, designed to detect movement using a PIR sensor. When motion is detected, the system will sound an alarm and indicate the detection through the screen/builtin LED.

## Components

- M5CardPuter
- PIR Sensor [Grove](https://wiki.seeedstudio.com/Grove-Digital-PIR-Sensor/)  connected to Pin 1

It should work with any digital PIR Sensor

## Features

- Detects movement using a PIR sensor
- Sounds an alarm with adjustable volume
- Displays detection status on the M5Cardputer screen
- Built-in RGB LED indicates the status
- Control over display brightness and volume

## Installation

- <b>M5Burner</b> : Search into M5CARDPUTER section and simply burn it
- <b>Old school</b> : Build or take the firmware.bin from the github release and flash it

## Usage

1. The PIR sensor continuously monitors for movement.

2. When movement is detected, the RGB LED turns red, and an alarm sounds with a frequency pattern.

# Controls

- <b>Volume down:</b> Arrow Down
- <b>Volume up: </b>Arrow Up
- <b>Brightness down:</b> Arrow Left
- <b>Brightness up:</b> Arrow Right
