# Connecting edge devices to Azure

For this workshop we are going to explore two scenarios connecting an ESP-32 microcontroller to Azure. These two scenarios provide a way to get acquainted with the technology to open up your mind to the vast number of possibilites this can offer.

## The ESP-32 microcontroller
The ESP-32 microcontroller is the successor to the ESP-8266 microcontroller. These are low-cost, low-power boards with integrated WiFi. These boards can have a camera and USB port integrated on the board. For this workshop we are going to use the ESP-32-CAM which has a camera, but does not have an integrated USB port. To be able to program the boards, we are going to use a programmer board which allows us to interface with the board through USB.
To allow the USB connection we have to install the CH-340 USB drivers, as mentioned in the installation and setup instructions in the prerequisites document.

## The Workshop
The workshop consists of two parts: 
1. **[Azure Devops Build status light](/azure-devops-build.md)**  
Challenge yourself with programming the ESP-32 board with C code that allows you to retrieve an Azure Devops build status and toggle a RGB led to reflect this status. 
This part of the workshop combines both flashing the board with code as well as wiring up the light and letting the board run it's magic.
2. **[Connecting ESP-32 board to Azure IoT Hub](/azure-iot-hub.md)**  
Challenge yourself with programming the ESP-32 board with C code that allows you to interface with an actual Azure IoT hub. 
This part of the workshop is programming only, but opens up the possibilities of interfacing of a SaaS IoT hub which really helps with building maintainable IoT solutions


