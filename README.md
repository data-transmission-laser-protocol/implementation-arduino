This implementation was extended from DTLP philosophy - a protocol:
https://github.com/data-transmission-laser-protocol/protocol-definition

# DTLP Implementation on Arduino
Data Transmission Laser Protocol Implementation on Arduino.

Basically this is a simple lib which allows you to start DTLP communication between two machines.

### Installation
1. Download the latest version from: https://github.com/data-transmission-laser-protocol/implementation-arduino/releases/latest
2. Open Arduino IDE and open your sketch
3. Navigate to Sketch -> Include Library -> Add .ZIP Library
4. Get usage example from examples folder. To have a fully working scenario, you need to have two sketches - one for transmitter and the second one for receiver. Both examples are included in repo.

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
- Photoresistor KY-018

### Speed & Optimization
The source code needs to be improved and optimized. Beside it the receiver should be tested with photodiode. Current speed is 1bit per 70ms (it's a min rate for digital photoresistor), that's it ~0.0015kbit/sec which is awful.
