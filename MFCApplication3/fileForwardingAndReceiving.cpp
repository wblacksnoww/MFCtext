#include"fileProcessing.h"
#include "fileForwardingAndReceiving.h"
#include<thread>
/*
	*1.读取文件
	*2.对文件中的数据进行处理
	*3.创建udp链接接收数据
	*4.将接收到的数据和文件中的数据进行组合
	*5.转发数据
	*/
HANDLE hMutex = NULL;
vector<vector<byte>> buff;

void thread_receive (){
	
	//接收的网络ip地址
	WaitForSingleObject(hMutex, INFINITE);
	char receiverAddress[20] = "127.0.0.1";
	class networkTransmission* links = new networkTransmission();
	//端口号
	int receiverPort = 40000;
	
	
	
	//判断条件
	int a = 1;

	
	cout << "建立链接" << endl;
	links->receive(receiverAddress, receiverPort,a);
	links->Creceive();
	ReleaseMutex(hMutex);
	return ;

}

void thread_send() 
{

	char senderAddress[20] = "192.168.10.111";
	//char senderAddress[20] = "192.168.10.255";
	//端口号

	int senderPort = 6306;
	// 判断条件

	bool b = 1;   //是否发送

		//发送数据
	vector <byte> obuff;
	

	class networkTransmission* Unlinks = new networkTransmission();

	Unlinks->send(senderAddress, senderPort, b);

	Unlinks->Csend();
}



bool fFAR::start() {

	thread dateReceive(thread_receive);
	if (dateReceive.joinable())
		dateReceive.detach();

	thread dateReceive(thread_send);
	if (dateReceive.joinable())
		dateReceive.detach();
		return true;
}
#include"pch.h"