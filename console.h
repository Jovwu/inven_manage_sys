#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include "file.h"
using namespace std;




void GoToXY(int PositionX, int PositionY);//�ƶ����
void HideCursor(int n);//���ع��
void ClearArea(int PositionX, int PositionY, int Length);//���ָ������
vector<string> Split(const string String);//�ָ��ַ���
void OrgColor();//��ʼ��ɫ
void Intensity();//����

//template<typename T>
//void Print(T Content)
//{
//	string Str;
//	//�жϲ������ͣ�Ȼ��ת��Content��string
//	if (std::is_same<T, int>::value)//int����
//	{
//		int Temp = Content;
//		Str = to_string(Temp);
//	}
//	else if (std::is_same<T, float>::value)//float����
//	{
//		float Temp = Content;
//		//������λС��
//		/*Temp =  ((float)((int)((Temp + 0.005) * 100))) / 100;*/
//		Str = to_string(Temp).substr(0, to_string(Temp).find_first_of('.') + 3);
//	}
//	else
//	{
//		Str = Content;
//	}
//	File* file = new File("console.txt");
//	//��Ҫȫ�ֱ����������λ��
//	//��������ļ�
//	//�ļ���ʽ    var1 var2 var3 string   var1:Y  var2:X   var3:��ʾ״̬  string:string
//	//�����1.�ַ�������  2.��ӵ���β  3.��ӵ�ͷ��  
//	//��Ҫ������
//	//���������Ļ
//	//����������س�,ɾ����
//
//	int X = ConsoleCursorX;
//	int Y = ConsoleCursorY;
//
//	//�Ȳ����ļ������Ƿ��и��е�����,��Y��Ϊ�ο�
//	vector<string> Rest = file->SelectAll(1, to_string(Y));
//	if (Rest.empty()) //����ı���û�и�������
//	{
//		string Res;
//		Res.append(to_string(Y));
//		Res.append(" ");
//		Res.append(to_string(X));
//		Res.append(" ");
//		Res.append(to_string(ConsoleColor));
//		Res.append(" ");
//		Res.append(Str);
//		Res.append(" ");
//		file->Append(Res);//��ӵ��ļ�ĩβ
//	}
//	else//�ı����и���
//	{
//		//����-->������ϵ�ǰX�ʹ����str����
//		//����-->������ɫ��ͬ��������ɫ��ͬ��������ɫ��ͬ������
//		//��β
//	}
//
//	cout << Str;
//	//��������һ������
//	//����һ������Y  ��������������ɫ
//		//�ֱ��X�����ж�
//		//�ֱ��������ɫ�����ж�
//}

#endif // !_CONSOLE_H_


