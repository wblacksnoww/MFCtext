#pragma once
#include"networkTransmission.h"
#include<windows.h>
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<commdlg.h>
#include<math.h>


//double x; //������е�����


using namespace std;
//zoom���ֵ
static int maxZoom = 0x0;
//zoom��Сֵ
static int minZoom = 0xffffff;
//foucs���ֵ
static int maxFocus = 0x0;
//foucs��Сֵ
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

�ļ��ֽڿ�������
*/


	static const unsigned int checkNum;

}dateName;
class file {
public:
	//file() {};
	//~file() {};
	bool readFile(vector < vector <double> >& Oarr1, vector<vector<double> >& Oarr2);			//��������ļ��е��������ڼ���
	//����1����Ҫ���з��������ݣ�����2�������н��ܵ���������
	bool createBuff( vector<vector<double> >ibuf, vector<vector<byte> >buffer);			//�����ļ����飬�ų�������͵�����
	//��rec���ܵĵ����ݣ������趨�����е�λ��ת��Ϊʵ�ʵ�ֵ��01����
	double arrayBitCalculation_01(byte date[80],int indx);
	//��rec���ܵĵ����ݣ������趨�����е�λ��ת��Ϊʵ�ʵ�ֵ���Ƕȼ���
	double arrayBitCalculation_(byte date[80], int indx);
	
	//���������ת��λ3λbyte����
	byte calculateTheReturnValue_3(double in, byte out[80], int index);
	//���������ת��λ4λbyte����
	byte calculateTheReturnValue_4(double in, byte out[80], int index);
	double LinkedData(double izoon, double ifocus, vector<vector<double> >buf, double val[8], int index);
protected:
	int NUMBER_OF_ZOOM_LINES = 0;
	int NUMBER_OF_FOCUS_LINES = 0;
	vector<vector<byte>> z;
};