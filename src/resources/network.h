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

	sf::Socket::Status connect();
	void disconnect(int) { tcpSock.disconnect(); }
	void sendTCP(sf::Packet&);
	void sendUDP(sf::Packet&);
	void sendSignal(int signalID, int val1=-1, int val2=-1);
	void sendUdpConfirm(sf::Uint16);
	void sendPing(int myID, int pingID);

	sf::String sendCurlPost(const sf::String& URL, const sf::String& postData, sf::Uint8 type);

	bool receiveData();
};

#endif