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
	/*files存储文件的路径及名称(eg.   C:\Users\WUQP\Desktop\test_devided\data1.txt)
	ownname只存储文件的名称(eg.     data1.txt)*/

	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
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
	//文件句柄  
	//long hFile = 0;     //win7
	intptr_t hFile = 0;   //win10
						  //文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{	// "\\*"是指读取文件夹下的所有类型的文件，若想读取特定类型的文件，以png为例，则用“\\*.png”
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
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

	//获取该路径下的所有文件路径  
	getFiles1(filePath, files);
	//获取该路径下的所有文件路径和文件名 
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
	cout << "处理完毕！" << endl;
	*/
	return 0;
}
