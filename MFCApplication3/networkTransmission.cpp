#include"pch.h"
#include"networkTransmission.h"
#include<iostream>
#include<errno.h>
#include<sstream>
#include<iomanip>


int j = 0;
byte buffer[buffersize] ;

static list<vector<byte> >  cbuffer;
static vector<byte> abuffer;                       //һ����Ҫ���մ��������
            //һ����Ҫ���������

string to_hex(unsigned char* data, int len) {
   stringstream ss;
    ss << uppercase << hex << setfill('0');
    for (int i = 0; i < len; i++) {
        ss << setw(2) << static_cast<unsigned>(data[i]);

    }
    return ss.str();
}

 bool  networkTransmission::send(char oaddr[],int oport,bool x)                   //�������ͣ�����ip��ַ���˿ںţ�

{
   // �����׽���
    if (WSAStartup(MAKEWORD(1, 1),&wsaData) != 0)
    {
        printf("�����׽���ʧ�ܣ�%d......\n", WSAGetLastError());
        return 1;
    }
    // ��ʼ��IP�Ͷ˿���Ϣ
    startUdpAddr.sin_family = AF_INET;
    startUdpAddr.sin_port = htons(oport);
    inet_pton(AF_INET, oaddr, (PVOID*)(&startUdpAddr.sin_addr.s_addr));
    link = socket(AF_INET, SOCK_DGRAM, 0);
    int nLen = sizeof(SOCKADDR);
    static vector<byte> y;
    while(1)
    {
       
        if (!cbuffer.empty())
        {
            if (!y.empty())
            {
                y.clear();
            }
               y = cbuffer.front();
                
               
               cbuffer.pop_front();
               
                char z[buffersize];

                for (int i = 0; i < buffersize; i++) {
                    if (y.empty())
                        break;
                    z[i] = y[i];
                    //cout << z[i] << endl;

                }

                if (!sendto(link, (const char*)z, sizeof(z), 0, (SOCKADDR*)&startUdpAddr, nLen))
                {
                    printf("����ʧ��\n");

                }
            
            Sleep(5);
        }
        
    }

    return 0;
}

 void networkTransmission::Csend() {

    closesocket(link);
}


 bool networkTransmission::receive(char iaddr[], int iport,bool x)

{
     double count=50;
     double startClock;
     double endClock;
    // �����׽���
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("�����׽���ʧ�ܣ�%d......\n", WSAGetLastError());

        return 1;
    }
    


    // socket()
    link = socket(AF_INET, SOCK_DGRAM, 0);
    if (SOCKET_ERROR == link) {
        printf("�����׽���ʧ�ܣ�%d......\n", WSAGetLastError());
        return 1;
    }  
    // ��ʼ��IP�Ͷ˿���Ϣ
    startUdpAddr.sin_family = AF_INET;



    startUdpAddr.sin_port = htons(iport);

    startUdpAddr.sin_addr.S_un.S_addr = INADDR_ANY;

    if (bind(link, (SOCKADDR*)&startUdpAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        printf("1�׽��ְ�ʧ�ܣ�%d......\n", WSAGetLastError());
        return 1;
    }
    //���ļ�
    //class file* file1 = new file();
    //vector<vector<double> > DOF;
    //vector<vector<double> > CT;   //�����ļ�����ĳ���������
    //�ļ�����
    //file1->readFile(CT,DOF);                                     //��ȡ�ĵ�
    
    int nLen = sizeof(SOCKADDR);

    while (1) {
        startClock = clock();
        int iRet = recvfrom(link,(char*)buffer, sizeof(buffer), 0, (SOCKADDR*)&iaddr, &nLen);
        if (iRet < 0) {

            cout << "erron" << endl;
            continue;
        }
        if (nLen > 0)
        {
           
           //cout << to_hex(buffer,sizeof(buffer)) << endl;                                           //�����յ�������
           //    for (unsigned char tBuf : buffer)                                                    //���յ������ݴ���cbuffer�У���ʱ����
           //    {
           //        
           //        abuffer.push_back(tBuf);
           //
           //    }
           //    cbuffer.push_back(abuffer);
           //    abuffer.clear();
           //    file1->createBuff(CT,this->getbuf());
           //    

        }
        else
        {
            cout << "fail" << endl;
        }
        void gotoxy(int x, int y);
        
        count++;
        //gotoxy(0, 0);
        endClock = clock();
        cout << 1/((endClock-startClock)/1000) << endl;
    }
    
    //memset(buffer, 0x00, sizeof(buffer));
    return 0;
   
}
 void gotoxy(int x, int y)
 {
     COORD pos = { x,y };//�ƶ����
     HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleCursorPosition(hOut, pos);
 }


 void networkTransmission::Creceive(){

    closesocket(link);
}
list<vector<byte> > networkTransmission::getbuf() 
{
    return cbuffer;
}