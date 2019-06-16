#ifndef WakeOnLan_h
#define WakeOnLan_h

#include <SPI.h>
#include <WiFiUDP.h>

class WakeOnLan {
   private:
	WiFiUDP udpSock;
	IPAddress broadcastAddress = IPAddress(255, 255, 255, 255);

	uint8_t repeatPacket = 1;
	unsigned long delayPacket = 100;

   public:
	WakeOnLan(WiFiUDP _udpSock);

	void setBroadcastAddress(IPAddress _broadcastAddress);
	void setRepeat(uint8_t _repeatPacket, unsigned long _delayPacket);

	void generateMagicPacket(uint8_t*& pMagicPacket, size_t& sizeOfMagicPacket, uint8_t* pMacAddress, size_t sizeOfMacAddress);
	void generateMagicPacket(uint8_t*& pMagicPacket, size_t& sizeOfMagicPacket, uint8_t* pMacAddress, size_t sizeOfMacAddress, uint8_t* pSecureOn, size_t sizeOfSecureOn);

	void sendMagicPacket(uint8_t* pMacAddress, size_t sizeOfMacAddress, uint16_t portNum = 9);
	void sendSecureMagicPacket(uint8_t* pMacAddress, size_t sizeOfMacAddress, uint8_t* pSecureOn, size_t sizeOfSecureOn, uint16_t portNum = 9);
};

#endif