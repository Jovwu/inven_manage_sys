#ifndef _TIME_H_
#define _TIME_H_
#include <string>
#include <ctime>
using namespace std;

string DateToString();
string DateToStringBySprit();//�ѵ�ǰϵͳʱ��ת��Ϊ�ַ���,����б�ָܷ�
time_t StringToTime(const string Date);//���ַ���ת��Ϊʱ��
 
#endif // !_TIME_H_
