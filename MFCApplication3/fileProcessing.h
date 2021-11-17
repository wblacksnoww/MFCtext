#pragma once
#include"networkTransmission.h"
#include<windows.h>
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<commdlg.h>
#include<math.h>


//double x; //传入包中的数据


using namespace std;
//zoom最大值
static int maxZoom = 0x0;
//zoom最小值
static int minZoom = 0xffffff;
//foucs最大值
static int maxFocus = 0x0;
//foucs最小值
static int minFocus = 0xffffff;
static struct fileDate{
	static const unsigned int zoom;
	static const unsigned int focus;
	static const unsigned int fov;
	//static const unsigned int fov2;
	static const unsigned int ar;
	static const unsigned int nodal;
	static const unsigned int k1;
	static const unsigned int k2;
	static const unsigned int k3;
	static const unsigned int p1;
	static const unsigned int p2;
	static const unsigned int ctx;
	static const unsigned int cty;
	static const unsigned int iris;
	static const unsigned int Dof;
	static const unsigned int Sw;
	static const unsigned int checksum2;
/*

文件字节看情况添加
*/


	static const unsigned int checkNum;

}dateName;
class file {
public:
	//file() {};
	//~file() {};
	bool readFile(vector < vector <double> >& Oarr1, vector<vector<double> >& Oarr2);			//输出两个文件中的数组用于计算
	//参数1：需要进行分析的数据，参数2：网络中接受到的数据组
	bool createBuff( vector<vector<double> >ibuf, vector<vector<byte> >buffer);			//进入文件数组，放出处理后发送的数组
	//把rec接受的到数据，按照设定数组中的位置转化为实际的值，01计算
	double arrayBitCalculation_01(byte date[80],int indx);
	//把rec接受的到数据，按照设定数组中的位置转化为实际的值，角度计算
	double arrayBitCalculation_(byte date[80], int indx);
	
	//将获得数据转化位3位byte数据
	byte calculateTheReturnValue_3(double in, byte out[80], int index);
	//将获得数据转化位4位byte数据
	byte calculateTheReturnValue_4(double in, byte out[80], int index);
	double LinkedData(double izoon, double ifocus, vector<vector<double> >buf, double val[8], int index);
protected:
	int NUMBER_OF_ZOOM_LINES = 0;
	int NUMBER_OF_FOCUS_LINES = 0;
	vector<vector<byte>> z;
};