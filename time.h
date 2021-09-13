#ifndef _TIME_H_
#define _TIME_H_
#include <string>
#include <ctime>
using namespace std;

string DateToString();
string DateToStringBySprit();//把当前系统时间转换为字符串,并以斜杠分隔
time_t StringToTime(const string Date);//将字符串转化为时间
 
#endif // !_TIME_H_
