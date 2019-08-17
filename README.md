# ESP32 PROMISCUOUS OSC

This project is made for my Bachelor's finalwork. It enables you to monitor your own "Safety levels" by scanning your environment 
for dangerous "Technological activities" (It's a WiFi sniffer, with some personal sensors).

**VERY IMPORTANT:** *This code is only for educational purposes. We don’t want to listen for any private communication and we don't do it. All packets that you can listen with this code are public packets without any encryption or secure layer on it, continuously broadcasted to the air by smartphones. Please, check which country's laws applies to you before use this code.*

## Getting Started

Some quick guideliness if you wish to run this yourself.

### Prerequisites

The IDE and plugin

* [VSCode](https://code.visualstudio.com/) - Recent version of Visual Studio Code
* [PlatformIO](https://platformio.org/) - Open source ecosystem for IoT development

The sensors I used for monitoring health and nervousness.

* [MAX30105 Particle and Pulse Ox Sensor](https://learn.sparkfun.com/tutorials/max30105-particle-and-pulse-ox-sensor-hookup-guide/all) - Powerfull multifunctional sensor
* [Grove GSR Sensor](http://wiki.seeedstudio.com/Grove-GSR_Sensor/) - Galvanic Skin Response sensor

### Installing

Folow the setup tutorial provided by [PlatformIO VSCode setup](https://docs.platformio.org/en/latest/ide/vscode.html).
Afterwards open this project via PlatformIO in VSCode.

Make sure you setup the platformio.ini correct for your system.

* Check if the COM port is correct
* Check if all libraries are included, you can install them via PlatformIO
## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* Inspired by this project on github [Paxcounter](https://github.com/cyberman54/ESP32-Paxcounter)
* Hat tip to everyone at [Gitter arduino-esp32](https://gitter.im/espressif/arduino-esp32) for responding fast to my questions.
* [David Walschots](https://github.com/davidwalschots) for coding tips and improvements. 
