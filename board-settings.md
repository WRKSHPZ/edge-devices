# Arduino IDE board settings

## Arduino IDE boards manager urls
Configure the Arduino IDE to include extra board manager URLs by:
1. Going to 'File' menu
2. Click on 'Preferences'
3. Add these comma separated URLs to the 'Additional boards manager URLs':
```http://arduino.esp8266.com/stable/package_esp8266com_index.json,https://dl.espressif.com/dl/package_esp32_index.json,https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json```
4. Click on 'Ok'
5. Restart Arduino IDE to load the extra board definitions
6. Load the board definition for de esp32 boards from EspressIf by navigating to the 'Tools' menu, pop-out the Boards sub-menu and open the boards manager. Now search for 'esp32' and install the esp32 library from EspressIf.

## Arduino board type
Configure the Arduino IDE to connect to an 'AI Thinker ESP32-CAM' by:
1. Going to 'Tools' menu
2. Click on 'Board'
3. Open 'esp32' fold-out menu
4. Select 'AI thinker ESP32-CAM' in this awful non-ordered list. It is somewhere past the middle near two-thirds of the list

## Arduino board settings
Normally the board settings are ok, but if you made changes, or want to verify board settings that work, this is a working setup:
| Setting                              | Value           |
| ------------------------------------ | ------          |
| CPU frequency                        | 80MHz (WiFi/BT) |
| Core Debug Level                     | Verbose         |
| Erase All Flasg Before Sketch Upload | Enabled         |
| Flash Frequency                      | 80MHz           |
| Flash Mode                           | DIO             |
| Partition Scheme                     | Minimal (1.3MB APP/700KB SPIFFS)

![Board settings](/wrkshpz/images/board-settings.png)

