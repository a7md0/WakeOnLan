# WakeOnLan [![Build Status](https://travis-ci.com/a7md0/WakeOnLan.svg?branch=master)](https://travis-ci.com/a7md0/WakeOnLan) [![PlatformIO Registry](https://badges.registry.platformio.org/packages/a7md0/library/WakeOnLan.svg)](https://registry.platformio.org/libraries/a7md0/WakeOnLan) [![arduino-library-badge](https://www.ardu-badge.com/badge/WakeOnLan.svg?)](https://reference.arduino.cc/reference/en/libraries/wakeonlan)
This Library provides an easy way to generate/send magic packets from an ESP8266 or ESP32 to any MAC Address. Additionally, it supports the "SecureOn" feature from some motherboard manufacturers. Finally, it also supports using any port number (instead of the default port 9.)<br /><br />
This library can be used in any environment that the IPAddress, WiFiUDP & delay classes are available.

## **Install**
You can install this library in the Arduino IDE by navigating to Tools -> Library Manager and search for this library's name. Alternatively, download this repository as zip file, then in the IDE navigate to Sketch -> Include library -> Add .ZIP library<br /><br />

To install the library in the PlatformIO IDE, use the library name like so:
`lib_deps = WakeOnLan`
 OR copy the repository link and add to the 'lib_deps' variable:
`lib_deps = https://github.com/a7md0/WakeOnLan.git`

#### Include and initialize WiFiUDP
```cpp
#include <WiFiUdp.h>
WiFiUDP UDP;
```

#### Include and initialize WakeOnLan class
```cpp
#include <WakeOnLan.h>
WakeOnLan WOL(UDP); // Pass WiFiUDP class
```

#### Add this line in void setup() (optional)

`WOL.setRepeat(3, 100); // Repeat the packet three times with 100ms delay between`

#### After connecting to WiFi successfully, Calculate and set the broadcast address (optional)
`WOL.calculateBroadcastAddress(WiFi.localIP(), WiFi.subnetMask());`

#### Manually set the broadcast address (optional)
`WOL.setBroadcastAddress("192.168.1.255");`
  
## **Usage**

### **Send WOL from char array MAC Address**

#### Set MAC address in variable
```cpp
const char *MACAddress = "01:23:45:67:89:AB";
```

##### Send WOL UDP packet (Using the default port - 9)
`WOL.sendMagicPacket(MACAddress);`

##### Send WOL UDP packet (Use port 7)
`WOL.sendMagicPacket(MACAddress, 7);`


#### Set MAC address and SecureOn variables
```cpp
const char *MACAddress = "01:23:45:67:89:AB";
const char *secureOn = "FE:DC:BA:98:76:54";
```

##### Send WOL UDP packet with password (Using the default port - 9)
`WOL.sendSecureMagicPacket(MACAddress, secureOn);`

##### Send WOL UDP packet with password (Use port 7)
`WOL.sendSecureMagicPacket(MACAddress, secureOn, 7);`
  
### **Send WOL from byte array MAC Address**

#### Set MAC address in variable
```cpp
uint8_t MAC[6] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB}; // 01:23:45:67:89:AB
```

##### Send WOL UDP packet (Using the default port - 9)
`WOL.sendMagicPacket(MAC, sizeof(MAC));`

##### Send WOL UDP packet (Use port 7)
`WOL.sendMagicPacket(MAC, sizeof(MAC), 7);`


#### Set MAC address and SecureOn in variable
```cpp
uint8_t MAC[6] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB}; // 01:23:45:67:89:AB
uint8_t SECURE_ON[6] = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54}; // FE:DC:BA:98:76:54
```

##### Send WOL UDP packet with password (By default port 9)
`WOL.sendSecureMagicPacket(MAC, sizeof(MAC), SECURE_ON, sizeof(SECURE_ON));`

##### Send WOL UDP packet with password (Use port 7)
`WOL.sendSecureMagicPacket(MAC, sizeof(MAC), SECURE_ON, sizeof(SECURE_ON), 7);`


### **Generate magic packet**

#### Generate
```cpp
size_t magicPacketSize = 6 + (6 * 16);  // FF*6 + MAC*16
uint8_t* magicPacket = new uint8_t[magicPacketSize]; // Magic packet will be stored in this variable

uint8_t MAC[6] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB}; // 01:23:45:67:89:AB

WOL.generateMagicPacket(magicPacket, magicPacketSize, pMacAddress, sizeof(MAC));
```

#### Generate with "SecureOn"
```cpp
size_t magicPacketSize = 6 + (6 * 16) + 6;  // FF*6 + MAC*16 + SecureOn
uint8_t* magicPacket = new uint8_t[magicPacketSize]; // Magic packet will be stored in this variable

uint8_t MAC[6] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB}; // MAC Address = 01:23:45:67:89:AB
uint8_t SECURE_ON[6] = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54}; // SecureOn = FE:DC:BA:98:76:54

WOL.generateMagicPacket(magicPacket, magicPacketSize, MAC, sizeof(MAC), SECURE_ON, sizeof(SECURE_ON));
```
