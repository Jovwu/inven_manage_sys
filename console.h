#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include "file.h"
using namespace std;




void GoToXY(int PositionX, int PositionY);//移动光标
void HideCursor(int n);//隐藏光标
void ClearArea(int PositionX, int PositionY, int Length);//清空指定区域
vector<string> Split(const string String);//分割字符串
void OrgColor();//初始颜色
void Intensity();//高亮

//template<typename T>
//void Print(T Content)
//{
//	string Str;
//	//判断参数类型，然后转化Content到string
//	if (std::is_same<T, int>::value)//int类型
//	{
//		int Temp = Content;
//		Str = to_string(Temp);
//	}
//	else if (std::is_same<T, float>::value)//float类型
//	{
//		float Temp = Content;
//		//保留两位小数
//		/*Temp =  ((float)((int)((Temp + 0.005) * 100))) / 100;*/
//		Str = to_string(Temp).substr(0, to_string(Temp).find_first_of('.') + 3);
//	}
//	else
//	{
//		Str = Content;
//	}
//	File* file = new File("console.txt");
//	//需要全局变量保存光标的位置
//	//先输出到文件
//	//文件格式    var1 var2 var3 string   var1:Y  var2:X   var3:显示状态  string:string
//	//情况：1.字符串覆盖  2.添加到结尾  3.添加到头部  
//	//需要做排序
//	//再输出到屏幕
//	//特殊情况：回车,删除键
//
//	int X = ConsoleCursorX;
//	int Y = ConsoleCursorY;
//
//	//先查找文件里面是否有该行的数据,以Y作为参考
//	vector<string> Rest = file->SelectAll(1, to_string(Y));
//	if (Rest.empty()) //如果文本中没有该行数据
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
//		file->Append(Res);//添加到文件末尾
//	}
//	else//文本中有该行
//	{
//		//插入-->条件结合当前X和传入的str长度
//		//覆盖-->字体颜色相同，字体颜色不同，字体颜色不同并交叉
//		//结尾
//	}
//
//	cout << Str;
//	//排序交由另一个函数
//	//排序：一级排序：Y  二级排序：字体颜色
//		//分别对X进行判断
//		//分别对字体颜色进行判断
//}

#endif // !_CONSOLE_H_


