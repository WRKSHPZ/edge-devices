# CH-340 Driver 

## Download
There are multiple versions of the CH-340 you can try (AT YOUR OWN RISK). This driver and board are made by a Chinese manufacturer and source documentation is in Chinese. 

You can find most driver download on this page: https://sparks.gogo.co.nz/ch340.html

## Version
I faced multiple issues when using the most recent driver, so I am using the 3.5.2019.1 version and that seems to have to best results (on a Windows machine).

![Driver version](/wrkshpz/images/driver.png)

## COM port settings
The driver uses a free COM port on your machine to setup the interface. While the default setup is usually ok, sometimes you have to tweak the settings.
| Setting                              | Value           |
| ------------------------------------ | ------          |
| Bits per second                      | 115200          |
| Data bits                            | 8               |
| Parity                               | None            |
| Stop bits                            | 1               |
| Flow control                         | None            |


![COM port settings](/wrkshpz/images/port-settings.png)