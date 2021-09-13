#include "time.h"

//string DateToSrting()
//{
//	string Time;
//	time_t Now = time(0);
//	tm* Ltm = localtime(&Now);
//	Time.append(to_string(Ltm->tm_year));
//	Time.append("/");
//	Time.append(to_string(Ltm->tm_mon));
//	Time.append("/");
//	Time.append(to_string(Ltm->tm_mday));
//	return Time;
//}

string DateToString()
{
	string Time;
	time_t Now = time(0);
	struct tm NowTime;
	localtime_s(&NowTime, &Now);
	Time.append(to_string(NowTime.tm_year + 1900));
	Time.append(
		to_string(NowTime.tm_mon + 1).size() == 1 ? "0"+ to_string(NowTime.tm_mon + 1) : to_string(NowTime.tm_mon + 1)
	);
	Time.append(
		to_string(NowTime.tm_mday).size() == 1 ? "0" + to_string(NowTime.tm_mday) : to_string(NowTime.tm_mday)
	);
	return Time;
}

string DateToStringBySprit()
{
	string Time;
	time_t Now = time(0);
	struct tm NowTime;
	localtime_s(&NowTime,&Now);
	Time.append(to_string(NowTime.tm_year+1900));
	Time.append("/");
	Time.append(
		to_string(NowTime.tm_mon + 1).size() == 1 ? "0" + to_string(NowTime.tm_mon + 1) : to_string(NowTime.tm_mon + 1)
	);
	Time.append("/");
	Time.append(
		to_string(NowTime.tm_mday).size() == 1 ? "0" + to_string(NowTime.tm_mday) : to_string(NowTime.tm_mday)
	);
	return Time;
}

time_t StringToTime(const string Date)
{
	return time_t();
}

