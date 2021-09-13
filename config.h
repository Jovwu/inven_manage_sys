#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <string>
#include <stack>
using namespace std;
class Window;
/**************************程序信息****************************/
/*w文件路径*/
extern const string USER_RECORD;
extern const string GOODS_RECORD;
extern const string GOODS_OUT_RECORD;
extern const string GOODS_IN_RECORD;
extern const string CHECK_NOTE_RECORD;
extern const string CHECK_INFO_RECORD;
extern const string CHECK_INFO_RECORD_TEMP;
extern string CHECK_INFO_RECORD_SINGLE;
extern const string EXPORT_FILE_PATH;
/*登录信息*/
extern string USER_ID;
extern string USER_NAME;
extern string USER_TYPE;

/***************************界面******************/
extern stack<Window*> Windows;
/*界面方法*/
#define WIN_NO_OPS 0 //无操作
#define WIN_EXIT 1 //界面退出
#define WIN_REFRESH 3
/*界面编号*/
#define WIN_FLAG 5000
#define WIN_LOGIN 5001 //登录界面
#define WIN_REG 5002 //注册界面
#define WIN_CHECK_MENU 5003 //盘点员界面
#define WIN_ADMIN_MENU 5004 //管理员界面
#define WIN_GOODS_QUERY 5005 //商品查询页面
#define WIN_CHECK_STOCK 5006 //商品新建盘点页面
#define WIN_CHECK_RECORD 5007 //盘点记录查看页面
#define WIN_CHECK_RECORD_SINGLE 5008 //盘点单条详情页面
#define WIN_ADD_GOODS 5009 //商品添加页面
#define WIN_GOODS_OUT_IN 5010//商品出入库
#define WIN_GOODS_OUT_RECORD 5011//商品出库记录
#define WIN_GOODS_IN_RECORD 5012 //商品入库记录
/*控件位置*/
#define WIN_CUR_POS_1 49
#define WIN_CUR_POS_2 50
#define WIN_CUR_POS_3 51
#define WIN_CUR_POS_4 52
#define WIN_CUR_POS_5 53
#define WIN_CUR_POS_6 54
#define WIN_CUR_POS_7 55
#define WIN_CUR_POS_8 56
#define WIN_CUR_POS_9 57

/********************窗口属性值******************************/

/*普通窗口*/
#define WIN_POS_X 0
#define WIN_POS_Y 0
#define WIN_WIDTH 118
#define WIN_HEIGHT 29
/*操作框*/
#define CTR_BOX_POS_X 40
#define CTR_BOX_POS_Y 8
#define CTR_BOX_WIDTH 42
#define CTR_BOX_HEIGHT 15
/*提示框*/
#define HINT_BOX_POS_X 44
#define HINT_BOX_POS_Y 10
#define HINT_BOX_WIDTH 30
#define HINT_BOX_HEIGHT 8
#define HINT_BOX_SLEEP_TIME 1000 //提示时间

/********************控件属性值******************************/

/*EDIT长度*/
/*User*/
#define USER_ID_MAX 4
#define USER_NAME_MAX 8
#define USER_PASSWORD_MAX 10

/*Goods类*/
#define GOODS_ID_MAX 12
#define GOODS_NAME_MAX 12
#define GOODS_COUNT_MAX 4
#define GOODS_PRICE_INTEGER_MAX 5
#define GOODS_PRICE_DECIMALS_MAX 2
#define GOODS_LOCID_MAX 5
#define GOODS_INOROUT_MAX 4

/*CheckNote类*/
#define CHECKNOTE_ID_MAX 12
#define CHECKNOTE_EXPLAIN_MAX 16

/*CheckInfo类*/
#define CHECKINFO_CHECKCOUNT_MAX 5


#endif // !_CONFIG_H_
