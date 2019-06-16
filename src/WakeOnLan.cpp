#include "WakeOnLan.h"

WakeOnLan::WakeOnLan(WiFiUDP _udpSock) {
	udpSock = _udpSock;
}

void WakeOnLan::setBroadcastAddress(IPAddress _broadcastAddress) {
	broadcastAddress = _broadcastAddress;
}

void WakeOnLan::setRepeat(uint8_t _repeatPacket, unsigned long _delayPacket) {
	repeatPacket = _repeatPacket;
	delayPacket = _delayPacket;
}

void WakeOnLan::sendMagicPacket(uint8_t* pMacAddress, size_t sizeOfMacAddress, uint16_t portNum) {
	size_t magicPacketSize = 6 + (6 * 16);  // FF*6 + MAC*16
	uint8_t* magicPacket = new uint8_t[magicPacketSize];

	generateMagicPacket(magicPacket, magicPacketSize, pMacAddress, sizeOfMacAddress);

	for (uint8_t i = 0; i < repeatPacket; i++) {
		udpSock.beginPacket(broadcastAddress, portNum);
		udpSock.write(magicPacket, magicPacketSize);
		int sucess = udpSock.endPacket();

		Serial.print("sendMagicPacket(); returned ");
		Serial.println(sucess);

		if (delayPacket > 0)
			delay(delayPacket);
	}

	delete[] magicPacket;
}

void WakeOnLan::sendSecureMagicPacket(uint8_t* pMacAddress, size_t sizeOfMacAddress, uint8_t* pSecureOn, size_t sizeOfSecureOn, uint16_t portNum) {
	size_t magicPacketSize = 6 + (6 * 16) + 6;  // FF*6 + MAC*16 + SecureOn
	uint8_t* magicPacket = new uint8_t[magicPacketSize];

	generateMagicPacket(magicPacket, magicPacketSize, pMacAddress, sizeOfMacAddress, pSecureOn, sizeOfSecureOn);

	for (uint8_t i = 0; i < repeatPacket; i++) {
		udpSock.beginPacket(broadcastAddress, portNum);
		udpSock.write(magicPacket, magicPacketSize);
		int sucess = udpSock.endPacket();

		Serial.print("sendSecureMagicPacket(); returned ");
		Serial.println(sucess);

		if (delayPacket > 0)
			delay(delayPacket);
	}

	delete[] magicPacket;
}

void WakeOnLan::generateMagicPacket(uint8_t*& pMagicPacket, size_t& sizeOfMagicPacket, uint8_t* pMacAddress, size_t sizeOfMacAddress) {
	uint8_t macAddress[6];

	memcpy(macAddress, pMacAddress, sizeOfMacAddress);
	memset(pMagicPacket, 0xFF, 6);

	for (uint8_t i = 0; i < 16; i++) {
		uint8_t indx = (i + 1) * sizeOfMacAddress;
		memcpy(&pMagicPacket[indx], &macAddress, sizeOfMacAddress);
	}
}

void WakeOnLan::generateMagicPacket(uint8_t*& pMagicPacket, size_t& sizeOfMagicPacket, uint8_t* pMacAddress, size_t sizeOfMacAddress, uint8_t* pSecureOn, size_t sizeOfSecureOn) {
	uint8_t macAddress[6];
	uint8_t secureOn[6];

	memcpy(macAddress, pMacAddress, sizeOfMacAddress);
	memcpy(secureOn, pSecureOn, sizeOfSecureOn);

	memset(pMagicPacket, 0xFF, 6);

	for (uint8_t i = 0; i < 16; i++) {
		uint8_t indx = (i + 1) * sizeOfMacAddress;
		memcpy(&pMagicPacket[indx], &macAddress, sizeOfMacAddress);
	}

	memcpy(&pMagicPacket[17 * sizeOfSecureOn], &secureOn, sizeOfSecureOn);
}
