#include"fileProcessing.h"
#include "fileForwardingAndReceiving.h"
#include<thread>
/*
	*1.��ȡ�ļ�
	*2.���ļ��е����ݽ��д���
	*3.����udp���ӽ�������
	*4.�����յ������ݺ��ļ��е����ݽ������
	*5.ת������
	*/
HANDLE hMutex = NULL;
vector<vector<byte>> buff;

void thread_receive (){
	
	//���յ�����ip��ַ
	WaitForSingleObject(hMutex, INFINITE);
	char receiverAddress[20] = "127.0.0.1";
	class networkTransmission* links = new networkTransmission();
	//�˿ں�
	int receiverPort = 40000;
	
	
	
	//�ж�����
	int a = 1;

	
	cout << "��������" << endl;
	links->receive(receiverAddress, receiverPort,a);
	links->Creceive();
	ReleaseMutex(hMutex);
	return ;

}





bool fFAR::start() {
	//����ip��ַ
	
	char senderAddress[20] = "192.168.10.111";
	//char senderAddress[20] = "192.168.10.255";
	

	//�˿ں�
	
	int senderPort =6306;

	
		//��������
    vector <byte> obuff;
	
	//�ж�����
	
	bool b = 1;   //�Ƿ���
	
	
	

	class networkTransmission* Unlinks = new networkTransmission();        //���Ͷ�
    
	//��������
	thread dateReceive(thread_receive);
	if (dateReceive.joinable())
		dateReceive.detach();
	
	

	//��������
	Unlinks->send(senderAddress, senderPort,b);
	system("pause");


	//�ͷŽӿڣ���������
	Unlinks->Csend();
	

		return true;
}
#include"pch.h"