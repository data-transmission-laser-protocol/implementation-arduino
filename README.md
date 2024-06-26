This implementation was extended from DTLP philosophy - a protocol:
https://github.com/data-transmission-laser-protocol/protocol-definition

# DTLP Implementation on Arduino
Data Transmission Laser Protocol Implementation on Arduino.

Basically this is a simple lib which allows you to start DTLP communication between two machines.

### Installation
1. Download the latest version from: https://github.com/data-transmission-laser-protocol/implementation-arduino/releases/latest
2. If you want to installed the specific version move here: https://github.com/data-transmission-laser-protocol/implementation-arduino/releases. The major version specifies the version of DTLP protocol. More: [https://github.com/data-transmission-laser-protocol/implementation-arduino/releases](https://github.com/data-transmission-laser-protocol/implementation-arduino/releases)
3. Open Arduino IDE and open your sketch
4. Navigate to Sketch -> Include Library -> Add .ZIP Library
5. Get usage example from examples folder. To have a fully working scenario, you need to have two sketches - one for transmitter and the second one for receiver. Both examples are included in repo.

### Versioning
It's a semantic versioning, i.e. X.Y.Z where X is a major release (a version of DTLP, see: https://github.com/data-transmission-laser-protocol/protocol-definition/blob/main/README.md#protocol-versions), Y feature releases and Z are bugfix and other releases.
To be informed about upcoming versions and features of the protocol see: https://github.com/data-transmission-laser-protocol/protocol-definition/blob/main/README.md#upcoming-versions

### Tests 
During development the code was ran and tested on the following hardware:

##### Boards
- Arduino UNO
- ESP32 Cam AI Thinker

##### Transmitter Hardware
- Laser KY-008

##### Receiver Hardware
- Photoresistor KY-018 (max speed 70ms per bit)
- Photodiode of Flyingfish IR Sensor (black diode) (max speed 30ms per bit)
- Photodiode DS18B20 (max speed 30ms per bit)

### TODOs
- Cannot force Arduino IDE 2 to show the example from the lib after lib installation. Make examples visible in Examples section in the IDE after lib installation.
- Work on speed

### Licence 
This software is under the CC BY-NC-ND 4.0 licence. For more info see: https://github.com/data-transmission-laser-protocol/implementation-arduino/blob/master/LICENCE
