#pragma warning(disable:4996)
#include "stringtool.h"


string doubleToString(const double& dbNum)
{
    char* chCode;
    chCode = new(std::nothrow)char[20];
    sprintf(chCode, "%.2lf", dbNum);  // .2 是控制输出精度的，两位小数
    string strCode(chCode);
    delete[]chCode;
    return strCode;
}
