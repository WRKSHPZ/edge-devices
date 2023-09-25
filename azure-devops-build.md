# Azure Devops build status light

We have all been there. Our build in Azure Devops is broken and we are too lazy to navigate to the portal to notice this and our tests fail because there is no new version deployed to the other DTAP environments.  
How time-saving would it be to see the build status on our Azure-Devops-Build-Status-3000™. For this we are going to leverage an ESP-32 microcontroller board, a breadboard, some cableing and an Azure Function. You can setup your own backing Azure Function on your own build pipeline, or you can skip this step by using the ready-made provided backend.

We are going through the following steps: 
1. [Setting up the backend services (Can be skipped)](#1-setting-up-the-backend-services-can-be-skipped)
1. [Installing drivers & software](#2-installing-drivers--software)
1. [Getting acquainted with the ESP-32 board](#3-getting-acquainted-with-the-esp-32-board)
1. [Programming the ESP-32 board](#4-programming-the-esp-32-board)
1. [Testing the ESP-32 connection with WiFi and Azure](#5-testing-the-esp-32-connection-with-wifi-and-azure)
1. [Wiring the breadboard and light](#6-wiring-the-breadboard-and-light)
1. [Testing the standalone setup](#7-testing-the-standalone-setup)

## 1. Setting up the backend services (Can be skipped)
Follow the instructions on [this page](/azure-backend-services.md)
## 2. Installing drivers & software
Follow the instructions on [this page](/prerequisites.md)
## 3. Getting acquainted with the ESP-32 board
ESP32 is a series of low-cost, low-power system on a chip microcontrollers with integrated Wi-Fi and dual-mode Bluetooth. ESP32 is created and developed by Espressif Systems, a Shanghai-based Chinese company. It is a successor to the ESP8266 microcontroller.  
It is a programmable board that can be flashed with C code using a multitude of software, but we will be using de Arduino Integrated Development Environment (IDE) since this will greatly improve the development process for people not familiar with developing for this kind of hardware.  
The board we are using is the ESP32-CAM and has an OV2640 camera onboard, a microSD card slot and 10 IO ports we can use to our liking. There are also some power and ground pins. You can power the ESP32-CAM through the 3.3V or 5V pins. However, many people reported errors when powering the ESP32-CAM with 3.3V, so we always advise to power the ESP32-CAM through the 5V pin.  
For more information on the ESP-32 CAM board, consult the excellent data sheet from Random nerd tutorials: https://randomnerdtutorials.com/esp32-cam-ai-thinker-pinout/

#### ESP-32 Cam pinout 
![ESP-32 CAM pinout](/wrkshpz/images/ESP32-CAM-pinout-new.webp "ESP-32 pinout")

Since the ESP-32-cam does not have a built-in USB port, we need the ESP-32-cam shield which the board plugs into. This programmer shield allows us to flash the board with new versions of the software and provides buttons for resetting the device and programming mode (a mode we do not need or use in this workshop, since the Arduino IDE handles this for us).  

#### What's in de box?
- An ESP-32-cam module
- An ESP-32-cam programmer shield 
- A breadboard
- A powersupply
- 1 USB mini to USB A cable 
- 1 USB micro to USB A cable
- 10 jumper wires
- 1 RGB led
- 1 Ohm resistor

## 4. Programming the ESP-32 board
Before you are able to program the board, you need to follow the instructions in the [prerequisites](/prerequisites.md) document.

1. Plug in the ESP-32-cam module on the ESP-32-cam programmer shield. The pin-out and pin-input should line up.  
1. Use the USB mini to USB A cable to connect the ESP-32-cam programmer shield to your laptop.
1. Start up Arduino IDE and make sure you have added library support for the ESP-32-cam board as specified in the [prerequisites](/prerequisites.md) document.
1. 


## 5. Testing the ESP-32 connection with WiFi and Azure
## 6. Wiring the breadboard and light
## 7. Testing the standalone setup