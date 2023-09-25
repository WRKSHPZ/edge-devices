# Azure IoT hub integration
An Azure IoT hub provides a cloud-hosted solution back end to connect virtually any device. Extend your solution from the cloud to the edge with per-device authentication, built-in device management, and scaled provisioning. For more marketing speak: https://azure.microsoft.com/en-us/products/iot-hub

TODO:Steps 1-3

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
We need to create a device with the IoT hub to use when programming our ESP-32-cam board.  

1. Navigate to the newly created or preconfigured IoT hub.
2. Feel free to check out the IoT hub options and panes
3. Click on the 'Devices' pane in the left menu
4. Click 'Add Device' in the top toolbar on the 'Devices' pane
5. Choose a Device ID and make sure it is unique when using the preconfigured IoT hub, fi. using your first name or initials
6. Leave the other options as-is
7. Click on your newly registered device and copy-paste the 'Device id' and 'Primary connection string' values. You will need these values in the next step.

## 6. Programming the ESP-32 board
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

## 7. Testing the ESP-32 connection with WiFi and Azure
Before we transfer our ESP-32-cam board to the breadboard, we need to verify if the WiFi connection and retrieving the build status from the Azure functions works.

1. Make sure your programming shield is still wired through USB to your laptop. 
1. Open up the serial monitor by clicking the button in the toolbar, or invoke the 'TODO' command in the 'TODO' menu.
1. Verify the output in the serial monitor looks OK. An example of valid output is provided in the [valid-serial-monitor](/valid-serial-monitor.md) document. Please note things like IP numbers should differ from the provided example.
