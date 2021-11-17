#pragma once
#ifndef _NETWORKTRANSMISSION_H_
#define _NETWORKTRANSMISSION_H_
#endif // !_NETWORKTRANSMISSION.H_


#include<stdio.h>
#include<WinSock2.h>
#include<string>
#include <WS2tcpip.h>
#include<vector>
#include<list>
#pragma comment(lib,"ws2_32.lib")
#include"fileProcessing.h"
#define buffersize 80
using namespace std;
class networkTransmission
{
public:
	//networkTransmission();
	//~networkTransmission();
public:
	bool send(char oaddr[], int oport, bool x);
	bool receive(char iaddr[], int iport, bool x);
	void Csend();
	void Creceive();
	WSADATA wsaData;
	SOCKET link;
	SOCKADDR_IN startUdpAddr;
	list<vector< byte> > getbuf();
protected:
	
	


};

