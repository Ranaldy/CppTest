#include<opencv2\opencv.hpp>
#include <stdio.h>
#include <io.h>
#include <string>
#include <iostream>  
#include <fstream> 

using namespace std;
using namespace cv;

void getFiles2(string path, vector<string>& files, vector<string> &ownname)
{
	/*files�洢�ļ���·��������(eg.   C:\Users\WUQP\Desktop\test_devided\data1.txt)
	ownnameֻ�洢�ļ�������(eg.     data1.txt)*/

	//�ļ����  
	long   hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,����֮  
			//�������,�����б�  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles2(p.assign(path).append("\\").append(fileinfo.name), files, ownname);
			}
			else
			{
				files.push_back(path + "\\" + fileinfo.name);
				ownname.push_back(fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void getFiles1(string path, vector<string>& files)
{
	//�ļ����  
	//long hFile = 0;     //win7
	intptr_t hFile = 0;   //win10
						  //�ļ���Ϣ  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{	// "\\*"��ָ��ȡ�ļ����µ��������͵��ļ��������ȡ�ض����͵��ļ�����pngΪ�������á�\\*.png��
		do
		{
			//�����Ŀ¼,����֮  
			//�������,�����б�  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles1(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(path + "\\" + fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

int showfile(string filePath){

	vector<string> files;
	//vector<string> filesname; 

	//��ȡ��·���µ������ļ�·��  
	getFiles1(filePath, files);
	//��ȡ��·���µ������ļ�·�����ļ��� 
	//getFiles2(filePath, files, filesname);

	char str[30];
	for (int i = 0; i < files.size(); i++)
	{
		cout << files[i].c_str() << endl;
	}
	return 0;
}

int main()
{
	cout << "[INFO] 1.Get file names; 2.Convert images into a video; 3.Show sequence images;" << endl;
	int method;
	cin >> method;
	if(method==1){
	string filePath;
	cin >> filePath;
	showfile(filePath);
	/*
	VideoWriter video("test.mp4", CV_FOURCC('X', 'V', 'I', 'D'), 15.0, Size(1920, 1080));

	String img_path = "E:/Graduation_Project/DataSet/CCTSDB/Images/13000~13999/*.png";
	vector<String> img;

	glob(img_path, img, false);

	size_t count = img.size();
	for (size_t i = 0; i < count; i++)
	{
		Mat image = imread(img[i]);
		resize(image, image, Size(1920, 1080));
		video << image;
	}
	cout << "������ϣ�" << endl;
	*/
	return 0;
}
