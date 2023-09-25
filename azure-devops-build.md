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
- A breadboard powersupply
- 1 USB mini to USB A cable 
- 1 USB micro to USB A cable
- 10 jumper wires
- 1 push button
- 1 RGB led
- 1 TODO Ohm resistor

## 4. Programming the ESP-32 board
Before you are able to program the board, you need to follow the instructions in the [prerequisites](/prerequisites.md) document.

1. Plug in the ESP-32-cam module on the ESP-32-cam programmer shield. The pin-out and pin-input should line up.  
1. Use the USB mini to USB A cable to connect the ESP-32-cam programmer shield to your laptop.
1. Start up Arduino IDE and make sure you have added library support for the ESP-32-cam board as specified in the [prerequisites](/prerequisites.md) document.
1. Configure the ESP-32-cam board as an 'AI thinker ESP-32-cam' board (Please note the list is **not** in alfabetical order)
1. Adjust the board specs in the 'Todo' menu to the specifications in the [board settings](/board-settings.md) document
1. Test the connection to the board by invoking 'Get board info' from the 'TODO' menu
1. Open the 'TODO.ino' Arduino solution from this repository
1. In the 'TODO.c' file update the variables for the WiFi and configure your backend service endpoint accordingly if you are running your own version of the backend services.
1. Upload you sketch to the ESP-32-cam board by clicking the arrow button in the toolbar, or invoke the 'TODO' command in the 'TODO' menu.

When succesful, continue to the next step.

## 5. Testing the ESP-32 connection with WiFi and Azure
Before we transfer our ESP-32-cam board to the breadboard, we need to verify if the WiFi connection and retrieving the build status from the Azure functions works.

1. Make sure your programming shield is still wired through USB to your laptop. 
1. Open up the serial monitor by clicking the button in the toolbar, or invoke the 'TODO' command in the 'TODO' menu.
1. Verify the output in the serial monitor looks OK. An example of valid output is provided in the [valid-serial-monitor](/valid-serial-monitor.md) document. Please note things like IP numbers should differ from the provided example.

## 6. Wiring the breadboard and light
After verifying our working software, we are now ready to remove the ESP-32-cam board from the programming shield. It should resume  working every time you power it on.  
We are now going to setup the breadboard according to this example:

Keep in mind the following:  
- The color of jumper wires does not really matter, but since the GPIO pins used are hardcoded in our software, please use the provided pinouts
- Since the maximum voltage is 5V, there should not be any danger of electrocution, but do not lick exposed wires or surfaces
- You will be able to create short circuits, please do not. While there are safeguards in place in the hardware, it can result in damaging the hardware and worse.
- Please note the bread-board power supply can provide two different voltages. Configure the correct voltage for each rail.

When done, it should look something like this: 


## 7. Testing the standalone setup
After creating this device you should not bring in your hand luggage when flying, you are ready to test it.

1. Connect the breadboard power supply to your laptop using the USB micro to USB A cable.
1. Verify the light goes from green to red, reflecting the failed build status
1. Push the button to simulate a succeed build, but notice the light changes to red again when the device polls the Azure function for the build status.