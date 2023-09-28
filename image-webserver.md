# Using the ESP-32 as a webcam
The following example is part of examples that are provided through the ESP32-CAM board library. It opens up access to using the camera, taking pictures and sending these somewhere to be processed, for instance an Azure Function calling into Azure Cognitive services to analyze the image.
The example we are going to look at, uses your browser to interface with the ESP32-CAM board.  
**Please note this example really pushes the limits of the board and is dead slow.** Do not expect amazing framerates.

## 1. Installing drivers & software
Follow the instructions on [this page](/prerequisites.md)
## 2. Getting acquainted with the ESP-32 board
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

## 3. Installing the OV2640 camera
To install the OV2640 camera, follow the instructions in the [Install camera document](/install-camera.md)  

## 4. Loading the CameraWebServer
1. Start up Arduino IDE and make sure you have added library support for the ESP32-CAM board as specified in the [prerequisites](/prerequisites.md) document.
1. Go to the 'File' menu
1. Open up the pop-out 'Examples' menu
1. Fold out the 'ESP-32' section and go to 'Camera'
1. Open the 'CameraWebServer' example
1. Comment line 17 (#define CAMERA_MODEL_ESP_EYE)
1. Uncomment line 24 (#define CAMERA_MODEL_AI_THINKER)
1. Update lines 38 and 39 with the WiFi credentials
1. Plug in the ESP32-CAM module on the ESP32-CAM programmer shield. The pin-out and pin-input should line up.  
1. Use the USB mini to USB A cable to connect the ESP32-CAM programmer shield to your laptop.
1. Upload you sketch to the ESP32-CAM board by clicking the arrow button in the toolbar, or invoke the 'Upload' command in the 'Sketch' menu.
1. Open the serial monitor by going to the 'Tools' menu and selecting the option for the 'Serial Monitor'
1. Wait for the WiFi to connect (message "WiFi connected")
1. It should state it is starting the web server, the camera is ready and should specify an IP to connect your browser to.
1. Navigate to the IP in your web browser on a device connected to the same WiFi.
1. Play around with this interface, if it crashes, just power cycle the ESP32-CAM board and reconnect.

In the lower resolution settings you even might be able to pull off real-time on-device face detection and recognition.  
It is mainly to show the endless possibilities these cheap devices bring to the table and how easy it is to think of usecases and integrations.
