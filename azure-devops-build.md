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

Since the ESP32-CAM does not have a built-in USB port, we need the ESP32-CAM shield which the board plugs into. This programmer shield allows us to flash the board with new versions of the software and provides buttons for resetting the device and programming mode (a mode we do not need or use in this workshop, since the Arduino IDE handles this for us).  

#### What's in de box?
- An ESP32-CAM module
- An ESP32-CAM programmer shield 
- A breadboard
- A breadboard powersupply
- 1 USB mini to USB A cable 
- 1 USB micro to USB A cable
- 10 jumper wires
- 1 push button
- 1 10k Ohm resistor
- 1 RGB led

## 4. Programming the ESP-32 board
Before you are able to program the board, you need to follow the instructions in the [prerequisites](/prerequisites.md) document.

1. Plug in the ESP32-CAM module on the ESP32-CAM programmer shield. The pin-out and pin-input should line up.  
1. Use the USB mini to USB A cable to connect the ESP32-CAM programmer shield to your laptop.
1. Start up Arduino IDE and make sure you have added library support for the ESP32-CAM board as specified in the [prerequisites](/prerequisites.md) document.
1. Configure the ESP32-CAM board as an 'AI thinker ESP32-CAM' board (Please note the list is **not** in alfabetical order)
1. Adjust the board specs in the 'Tools' menu to the specifications in the [board settings](/board-settings.md) document
1. Test the connection to the board by invoking 'Get board info' from the 'Tools' menu
1. Open the 'Azure_IoT_Hub_ESP32.ino' Arduino solution from the [Azure_IoT_Hub_ESP32](/Azure_IoT_Hub_ESP32) folder
1. In the 'iot_configs.h' file update the variables for the WiFi and configure your backend service endpoint accordingly if you are running your own version of the backend services.
1. Upload you sketch to the ESP32-CAM board by clicking the arrow button in the toolbar, or invoke the 'Upload' command in the 'Sketch' menu.

When succesful, continue to the next step.

## 5. Testing the ESP-32 connection with WiFi and Azure
Before we transfer our ESP32-CAM board to the breadboard, we need to verify if the WiFi connection and retrieving the build status from the Azure functions works.

1. Make sure your programming shield is still wired through USB to your laptop. 
1. Open up the serial monitor by clicking the button in the toolbar, or invoke the 'Serial monitor' command in the 'Tools' menu.
1. Verify the output in the serial monitor looks OK. An example of valid output is provided in the [valid-serial-monitor](/valid-serial-monitor.md) document. Please note things like IP numbers should differ from the provided example.

## 6. Wiring the breadboard and light
After verifying our working software, we are now ready to remove the ESP32-CAM board from the programming shield. It should resume  working every time you power it on.  
We are now going to setup the breadboard according to this example:

Keep in mind the following:  
- The color of jumper wires does not really matter, but since the GPIO pins used are hardcoded in our software, please use the provided pinouts
- Since the maximum voltage is 5V, there should not be any danger of electrocution, but do not lick exposed wires or surfaces
- When the board starts short-cycling or smoking, please disconnect and trace the connections to make sure you did not short circuit something
- You will be able to create short circuits, please do not. While there are safeguards in place in the hardware, it can result in damaging the hardware and worse.
- Please note the bread-board power supply can provide two different voltages. Configure the correct voltage for each rail. We will only be using 1 rail and that should be powered with 5v. The toggle switch on the power supply makes it possible to switch between 3.3 and 5v.

When done, it should look something like this: 
![Breadboard](/wrkshpz/images/breadboard-photo.jpg)

Schematically the connections should be:
![Breadboard](/wrkshpz/images/breadboard-schematic.png)

Assuming the ESP32-CAM is plugged in all the way on the left with the power pins (labeled 3V3 and 5V on the board) in pin 1 of the breadboard.

You are making the following connections:
| Port ESP  | From | To           | To   | Why    |
| --------- | ---- | ------------ | ---- | ------ |
| 5V        | A1   | PWR (+)      |      | Power  |
| GND       | A2   | PWR grnd (-) |      | Ground |
| IO12      | A3   | RGB Blue     | F25  | RGB    |
| IO13      | A4   | RGB Green    | F24  | RGB    |
| IO2       | A7   | RGB Red      | F22  | RGB    |
|           | F23  | RGB Cathode  | PWR grnd (-) | RGB |
| 3V3       | J1   | Button in    | H32  | Button |
| U0R (IO3) | J6   | Button out   | I30  | Button |
|           | G30  | Resistor     | G38  | Noise reduction |
|           | F30  | Resistor     | PWR grnd (-) | Noise reduction |

The push button should bridge the 30 and 32 rails on the breadboard. Keep in mind the button connects the contacts along each side... so the short side. Check the photo for reference. The button pins in the D-row are not used.

We are including the reistor for noise reduction. The IO ports tend to be a bit noisy (cheap hardware) and we want clear signals for our input ports.

The RGB led has four legs, three legs determine the color intensity (we will only be powering it full, but when varying voltages you can create all colors) for red, green and blue and the longest leg (for this LED the cathode) is ground. On the breadboard schematic this is the orange track. Since the LED is a diode, it will only work in the one way, so make sure to plug in the longest leg (the cathode) in H23.

Please check that the ESP32-CAM board is plugged in to port 1, with the power supply on the other side of the board.

## 7. Testing the standalone setup
After creating this device you should not bring in your hand luggage when flying, you are ready to test it.

1. Connect the breadboard power supply to your laptop using the USB micro to USB A cable.
1. The LED should start to blink blue while connecting to WiFi. If it has succesfully connected to WiFi the led will turn green. 
1. After a few seconds the light goes from green to red, reflecting the failed build status
1. Push the button to simulate a succeeded build, but notice the light changes to red again when the device polls the Azure function for the build status. Default the device is on a 15 second polling delay, but you can configure this in the C code in the Arduino IDE.

You have succesfully created an Azure-Devops-Build-Status-3000™ device. Feel free to play around with the code and setup, or move on to the IoT hub part.