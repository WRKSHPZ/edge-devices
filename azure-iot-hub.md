# Azure IoT hub integration
An Azure IoT hub provides a cloud-hosted solution back end to connect virtually any device. Extend your solution from the cloud to the edge with per-device authentication, built-in device management, and scaled provisioning. For more marketing speak: https://azure.microsoft.com/en-us/products/iot-hub

## 1. Get coffee
☕

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

## 4a. Setting up Azure resources
This step is to set up the necessary IoT hub resources in the Azure portal. If you do not have access to an active Azure subscription, skip to 4b instead.

We need to create an IoT hub. You can choose to:
- [Use the Azure Portal](https://learn.microsoft.com/en-us/azure/iot-hub/iot-hub-create-through-portal)
- [Use Visual Studio Code](https://learn.microsoft.com/en-us/azure/iot-hub/iot-hub-create-use-iot-toolkit)
- [Use Azure Powershell](https://learn.microsoft.com/en-us/azure/iot-hub/iot-hub-create-using-powershell)
- [Use Azure CLI](https://learn.microsoft.com/en-us/azure/iot-hub/iot-hub-create-using-cli)

## 4b. Using preconfigured Azure resources
If you do not have access to an active Azure subscription, you can use our wrkshpz IoT hub. Log in to the Azure portal (in an in-private browser) by using these credentials:  
| Login    | https://portal.azure.com         |
| :------- | :------------------------------- |
| User     | workshop@wrkshpz.onmicrosoft.com |
| Password | *q4CKmZ#                         |
| Connection string | HostName=wrkshpz.azure-devices.net;SharedAccessKeyName=wrkshpz;SharedAccessKey=DFsqKdIOi2iR/wnf/lmR1R8aIa0Wcr/LQAIoTDGCWqE= |

These credentials will be invalidated after the workshop and can and should only be used for registering your IoT device. Please choose a unique device ID in the next step, fi. using your first name or initials.

The IoT hub in this subscription is the: wrkshpz.azure-devices.net

## 5. Registering your device
We need to create a device with the IoT hub to use when programming our ESP32-CAM board.  

1. Navigate to the newly created or preconfigured IoT hub.
2. Feel free to check out the IoT hub options and panes
3. Click on the 'Devices' pane in the left menu
4. Click 'Add Device' in the top toolbar on the 'Devices' pane
5. Choose a Device ID and make sure it is unique when using the preconfigured IoT hub, fi. using your first name or initials
6. Leave the other options as-is
7. Click on your newly registered device and copy-paste the 'Device id' and 'Primary connection string' values. You will need these values in the next step.

## 6. Programming the ESP-32 board
Before you are able to program the board, you need to follow the instructions in the [prerequisites](/prerequisites.md) document.

1. Plug in the ESP32-CAM module on the ESP32-CAM programmer shield. The pin-out and pin-input should line up.  
1. Use the USB mini to USB A cable to connect the ESP32-CAM programmer shield to your laptop.
1. Start up Arduino IDE and make sure you have added library support for the ESP32-CAM board as specified in the [prerequisites](/prerequisites.md) document.
1. Configure the ESP32-CAM board as an 'AI thinker ESP32-CAM' board (Please note the list is **not** in alfabetical order)
1. Adjust the board specs in the 'Tools' menu to the specifications in the [board settings](/board-settings.md) document
1. Test the connection to the board by invoking 'Get board info' from the 'Tools' menu
1. Open the 'Azure_IoT_Hub_ESP32.ino' Arduino solution from the [Azure_IoT_Hub_ESP32](/Azure_IoT_Hub_ESP32) folder
1. In the 'iot_configs.h' file update the variables for the WiFi and configure your backend service endpoint accordingly if you are running your own version of the backend services. Check the [values you should update](/azure-iot-hub-values.md).
1. If you get any compilation errors from missing library dependencies, open up the library manager by going to the 'Sketch' menu, follow the 'Include library'-popout-menu en select 'Manage libraries'. You can usually find the library by typing the name of the #include reference at the top of the INO file. (i.e. For "WifiClientSecure.h", search for "WifiClientSecure").
1. Upload you sketch to the ESP32-CAM board by clicking the arrow button in the toolbar, or invoke the 'Upload' command in the 'Sketch' menu.

When succesful, continue to the next step.

## 7. Testing the ESP-32 connection with Azure IoT hub
We are now ready to verify the bi-directional connection is working. Leave the ESP32-CAM board connected to your laptop through USB and open up the serial monitor.

1. Open the serial monitor by going to the 'Tools' menu and selecting the option for the 'Serial Monitor'
2. To clear output, disconnect the ESP32-CAM board, press the 'Clear output' button on the top right of the Serial Monitor (it looks like a hamburger menu with a cross) and reconnect the ESP32-CAM board.
3. You should see an output similar to the output in [this file](/valid-serial-monitor.md)  
When everything is connected, it should cycle sending Telemetry to the IoT hub.
4. We are now ready to look at the Azure IoT explorer. It is time to retrieve your connection string. If you are using your own Azure IoT Hub, connect using the connection string for your IoT hub. If your are using the shared resources wrkshpz IoT hub, use this connection string:
```HostName=wrkshpz.azure-devices.net;SharedAccessKeyName=wrkshpz;SharedAccessKey=DFsqKdIOi2iR/wnf/lmR1R8aIa0Wcr/LQAIoTDGCWqE=```
You can find the connection string in the Azure portal on the IoT hub by navigating to the 'Shared Access policies' pane and select the 'iothubowner' policy. Copy either of the connection strings.
5. Open the Azure IoT explorer
6. Navigate to the 'IoT hubs' pane 
7. Click 'Add connection'
8. Paste in the connection string and click on 'Save'
9. Click on '-> View devices on this hub'
10. Find and click on the device you registered in [part 5 of this document](#5-registering-your-device)
11. Feel free to look around, but when you are ready, go to the 'Telemetry' pane
12. Click on 'Start' in the top toolbar
13. You should see the telemetry your ESP32-CAM device is sending
14. Go to the 'Cloud-to-device message' pane
15. This will allow us to send a message back to our device. Write an appropriate message body and click on the 'Send message to device' button in the toolbar
16. Hurry over to the serial monitor in the Arduino IDE to see your message popping up.
17. Repeat steps 15 and 16 if you missed it

In this workshop, when going over these steps, it might not look like much, but take a minute to realise you have set up an actual IoT device which can be extended with a multitude of sensors and created a bi-directional interface with the Azure cloud allowing you to receive telemetry and send messages back to your device.
From Azure IoT hub it is a breeze to setup processing of events and messages using Azure services like Azure Function apps or ingest the data for processing.

