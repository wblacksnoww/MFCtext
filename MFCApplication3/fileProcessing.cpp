#include"pch.h"
#include"fileProcessing.h"
#include<windows.h>
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<commdlg.h>


using namespace std;

const unsigned int fileDate::zoom =20;
const unsigned int fileDate::focus =23;
const unsigned int fileDate::fov =26;
//const unsigned int fileDate::fov2 = 29;
const unsigned int fileDate::nodal = 29;
const unsigned int fileDate::ctx = 32;
const unsigned int fileDate::cty = 35;
const unsigned int fileDate::k1=39;
const unsigned int fileDate::k2 = 42;
const unsigned int fileDate::k3 =46;
const unsigned int fileDate::p1 = 50;
const unsigned int fileDate::p2 = 53;
const unsigned int  fileDate::iris = 56;
const unsigned int fileDate::Dof = 59;
const unsigned int fileDate::ar = 62;
const unsigned int fileDate::Sw = 65;
const unsigned int fileDate::checksum2 =68;

vector<double> dataProcessing(string incomingDate) {                   //���CALIB TABLE
	vector<double> receiveData;//������
	string returnDate;//�и�����������
	int index;//�ָ�����ָ��
	string temporaryStorage;//ʣ������
	string test;
	while (incomingDate.find(";") != string::npos) {					//Ѱ�ҡ����������������ֶ�
		index = incomingDate.find(";");
		returnDate = incomingDate.substr(0, index);
		incomingDate = incomingDate.substr(index + 1);             //����ǰ�ƣ��Ѵ�����Ķ���
		if (returnDate.find(",") != string::npos) {
			int x = returnDate.find(",");
			returnDate.erase(x, 1);
			returnDate.insert(x, ".");
		}
		//cout << stod(returnDate) << endl;
		//cout << atof(returnDate.c_str()) << endl;
		receiveData.push_back(atof(returnDate.c_str()));
	}
	return receiveData;
}


	string TCHAR2STRING(TCHAR * str) {
		std::string strstr;
		try
		{
			int iLen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

			char* chRtn = new char[iLen * sizeof(char)];

			WideCharToMultiByte(CP_ACP, 0, str, -1, chRtn, iLen, NULL, NULL);

			strstr = chRtn;
		}
		catch (exception e)
		{
		}
		
		return strstr;
	}

	bool file ::readFile(vector<vector<double> >& CTarr, vector<vector<double> >& DOFarr){
		while (1) {
			OPENFILENAME ofn = { 0 };
			TCHAR strFileName[MAX_PATH] = { 0 };	//���ڽ����ļ���
			ofn.lStructSize = sizeof(OPENFILENAME);	//�ṹ���С
			ofn.hwndOwner = NULL;					//ӵ���Ŵ��ھ��
			ofn.lpstrFilter = TEXT("Text Files(*.TXT)\0*.txt");	//���ù���
			ofn.nFilterIndex = 1;	//����������
			ofn.lpstrFile = strFileName;	//���շ��ص��ļ�����ע���һ���ַ���ҪΪNULL
			ofn.nMaxFile = sizeof(strFileName);	//����������
			ofn.lpstrInitialDir = NULL;			//��ʼĿ¼ΪĬ��
			ofn.lpstrTitle = TEXT("��ѡ��һ���ļ�"); //���ڱ���
			ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY; //�ļ���Ŀ¼������ڣ�����ֻ��ѡ��
			//���ļ��Ի���
			if (GetOpenFileName(&ofn)) {
				string filePath = TCHAR2STRING(strFileName);//·��
				ifstream ifile;
				ifile.open(filePath);
				if (!ifile.is_open())
				{
					MessageBox(NULL, TEXT("�ļ���ʧ�ܣ����ٴ�ѡ��"), NULL, MB_ICONERROR);

					return false;
				}
				string temp;
				while (getline(ifile, temp)) 
				{
					if (temp == "NUMBER OF ZOOM LINES") {
						getline(ifile, temp);
						NUMBER_OF_ZOOM_LINES = atoi(temp.c_str());
							//cout << zoomlines << endl;
					}
					if (temp == "NUMBER OF FOCUS LINES") {
						getline(ifile, temp);
						NUMBER_OF_FOCUS_LINES = atoi(temp.c_str());
						//cout << focuslines << endl;
					}
					if (temp == "CALIB TABLE"){
						getline(ifile, temp);
						while(temp!="DOF (PERCENT 0-CLOSEST; DISTANCE [m])") {
							getline(ifile, temp);
							CTarr.push_back(dataProcessing(temp));
							
						}
					}
					if (temp == "END DOF"){
						DOFarr.push_back(dataProcessing(temp));
						getline(ifile, temp);
					
					}
					//cout << temp << endl;
				}	

				return 0;
			}

		}

	}
	
	bool file::createBuff( vector<vector<double> > ibuffer,vector<vector<byte> > cbuffer)			 //���뻺�档������档�����յ������ݰ����д���
	{	//���봦�������							
		byte buf[buffersize];								
		//���ɸѡ��zoom,focus,�����±�
		double index;                     
		//���ܵ���zoom��focus��ֵ
		double izoom, ifocus, temporaryData;
		//0.zoom  1.focus 2.fov 3.ar 4.n 5.k1 6.k2 7.k3
		double returnval[8];
		//zoom
		izoom = arrayBitCalculation_01(buf,dateName.zoom);
		
		//��������zoom����Сzoom
		maxZoom = max(izoom,maxZoom);
		minZoom = min(izoom,minZoom);
		//printf("zoomt:%fl\n", izoom);
		returnval[0] = izoom;
		
		//focus
		ifocus = arrayBitCalculation_01(buf, dateName.focus);
		
		//��������focus����Сfoucs
		maxFocus = max(ifocus, maxFocus);
		minFocus = min(ifocus, minFocus);
		
		returnval[1] = ifocus;

		
		//ͨ��zoom���㷽��
		

		//fov
		LinkedData(izoom, ifocus, ibuffer, returnval, 2);


		//ar
		LinkedData(izoom, ifocus, ibuffer, returnval, 3);

		//n
		LinkedData(izoom, ifocus, ibuffer, returnval, 4);

		//k1
		LinkedData(izoom, ifocus, ibuffer, returnval, 5);

		//k2
		LinkedData(izoom, ifocus, ibuffer, returnval, 6);

		//k3
		LinkedData(izoom, ifocus, ibuffer, returnval, 7);
		
		for (int i = 0; i < buffersize; i++)
		{

			//buf[i] = cbuffer.front()[i];

			//printf("0x%x", buf[i]);
		}
		double val;
		val = returnval[2];
		int valIntegerPart;
		double valDecimalPart;
		valIntegerPart = val;
		valDecimalPart = val - valIntegerPart;
		
		buf[dateName.fov] = val;
		//buf[dateName.fov]=(val<<4);
		
	
	     
		return 0;
	
	}
	

	//��ü���������
	double file::LinkedData(double zoom, double focus,vector<vector<double> >buf, double val[8], int index)
	{
	
		for (int i = 0; i < this->NUMBER_OF_ZOOM_LINES * this->NUMBER_OF_FOCUS_LINES; i++) {
			double idxZoom, idxFocus;
			idxZoom = zoom / ((double)(maxZoom - minZoom) / (double)(NUMBER_OF_ZOOM_LINES - 1));
			int idxZoomIntegerPart;
			double idxZoomDecimalPart;
			idxZoomIntegerPart = idxZoom;
			idxZoomDecimalPart = idxZoom - idxZoomIntegerPart;
			idxFocus = focus / ((double)(maxFocus - minFocus) / (double)(NUMBER_OF_FOCUS_LINES - 1));
			int idxFocusIntegerPart;
			double idxFocusDecimalPart;
			idxFocusIntegerPart = idxFocus;
			idxFocusDecimalPart = idxFocus - idxFocusIntegerPart;
			double poorData;


			if (buf[i][0] = idxZoomIntegerPart) {
				cout << buf[i][0] << endl;
				poorData = (double)buf[i][index] - (double)buf[i + NUMBER_OF_FOCUS_LINES - 1][2];

				val[index] = buf[i][index] + (poorData * idxZoomDecimalPart * idxFocusDecimalPart);
				break;


			}
		}
	
	
	
	
	
		return val[2];
	
	
	
	
	
	
	}




	 double file::arrayBitCalculation_01( byte date[buffersize],int index) 
	{	
		double val;
		int sum;
		if (0xf80000<(date[index]*0x10000)&& (date[index] * 0x10000) <=0xff0000)
		{
			sum = date[index] * 0x10000 + ((date[index+1]) * 0x100) + date[index+2];
			//printf("sum:0x%x\n", sum);
			val = sum - 0xf80000;
			val = -val;
			return val;

		}
		else if (0x0 <=(date[index] * 0x10000) && (date[index] * 0x10000) <= 0x80000)
		{
			sum = date[index] * 0x10000 + ((date[index + 1]) * 0x100) + date[index + 2];
			val = sum - 0x80000;
			return val;

		}
		return 8;
	}
	 byte file::calculateTheReturnValue_3(double in,byte out[buffersize],int index)
	 {
	 
		int IntegerPart;
		int DecimalPart;
		IntegerPart = in;
		//����4λС��
		DecimalPart = (in - IntegerPart)*1000;
		
	 
		return 0;
	 
	 }
	 