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

vector<double> dataProcessing(string incomingDate) {                   //拆分CALIB TABLE
	vector<double> receiveData;//接收组
	string returnDate;//切割下来的数据
	int index;//分隔数据指针
	string temporaryStorage;//剩余数据
	string test;
	while (incomingDate.find(";") != string::npos) {					//寻找“；”，按“；”分段
		index = incomingDate.find(";");
		returnDate = incomingDate.substr(0, index);
		incomingDate = incomingDate.substr(index + 1);             //数据前移，把处理完的丢除
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
			TCHAR strFileName[MAX_PATH] = { 0 };	//用于接收文件名
			ofn.lStructSize = sizeof(OPENFILENAME);	//结构体大小
			ofn.hwndOwner = NULL;					//拥有着窗口句柄
			ofn.lpstrFilter = TEXT("Text Files(*.TXT)\0*.txt");	//设置过滤
			ofn.nFilterIndex = 1;	//过滤器索引
			ofn.lpstrFile = strFileName;	//接收返回的文件名，注意第一个字符需要为NULL
			ofn.nMaxFile = sizeof(strFileName);	//缓冲区长度
			ofn.lpstrInitialDir = NULL;			//初始目录为默认
			ofn.lpstrTitle = TEXT("请选择一个文件"); //窗口标题
			ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY; //文件、目录必须存在，隐藏只读选项
			//打开文件对话框
			if (GetOpenFileName(&ofn)) {
				string filePath = TCHAR2STRING(strFileName);//路径
				ifstream ifile;
				ifile.open(filePath);
				if (!ifile.is_open())
				{
					MessageBox(NULL, TEXT("文件打开失败，请再次选择"), NULL, MB_ICONERROR);

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
	
	bool file::createBuff( vector<vector<double> > ibuffer,vector<vector<byte> > cbuffer)			 //输入缓存。输出缓存。将接收到的数据包进行处理
	{	//用与处理的数据							
		byte buf[buffersize];								
		//输出筛选的zoom,focus,的行下标
		double index;                     
		//接受到的zoom，focus的值
		double izoom, ifocus, temporaryData;
		//0.zoom  1.focus 2.fov 3.ar 4.n 5.k1 6.k2 7.k3
		double returnval[8];
		//zoom
		izoom = arrayBitCalculation_01(buf,dateName.zoom);
		
		//传入的最大zoom和最小zoom
		maxZoom = max(izoom,maxZoom);
		minZoom = min(izoom,minZoom);
		//printf("zoomt:%fl\n", izoom);
		returnval[0] = izoom;
		
		//focus
		ifocus = arrayBitCalculation_01(buf, dateName.focus);
		
		//传入的最大focus和最小foucs
		maxFocus = max(ifocus, maxFocus);
		minFocus = min(ifocus, minFocus);
		
		returnval[1] = ifocus;

		
		//通过zoom计算方法
		

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
	

	//获得计算后的数据
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
		//保留4位小数
		DecimalPart = (in - IntegerPart)*1000;
		
	 
		return 0;
	 
	 }
	 