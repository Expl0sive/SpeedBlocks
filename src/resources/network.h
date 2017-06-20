#ifndef NETWORK_H
#define NETWORK_H

#include <SFML/Network.hpp>
#include <list>
#include <curl/curl.h>
#include <stdio.h>

class network {
public:
	network();
	~network();

	sf::TcpSocket tcpSock;
	sf::UdpSocket udpSock;

	sf::IpAddress serverAdd;
	unsigned short tcpPort;
	unsigned short udpPort;

	sf::Packet packet;
	sf::Uint8 packetid;

	sf::Socket::Status connect();
	void disconnect() { udpSock.unbind(); tcpSock.disconnect(); }
	void sendTCP();
	void sendUDP();
	void sendSignal(sf::Uint8 signalId, int id1 = -1, int id2 = -1);
	void sendUdpConfirm(sf::Uint16);
	void sendPing(sf::Uint16 myId, sf::Uint8 pingId);

	sf::String sendCurlPost(const sf::String& URL, const sf::String& postData, sf::Uint8 type);

	bool receiveData();
};

#endif