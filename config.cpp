#include "config.h"

stack<Window*> Windows;

string USER_ID = "NULL";
string USER_NAME = "请先登录!";
string USER_TYPE = "请先登录!";

const string USER_RECORD = "用户记录\\user.txt";
const string GOODS_RECORD = "商品记录\\goods.txt";
const string GOODS_OUT_RECORD = "商品记录\\出库记录\\goodsout.txt";
const string GOODS_IN_RECORD = "商品记录\\入库记录\\goodsin.txt";
const string CHECK_NOTE_RECORD = "盘点记录\\checknote.txt";
const string CHECK_INFO_RECORD = "盘点记录\\盘点详情\\";
const string CHECK_INFO_RECORD_TEMP = "盘点记录\\盘点详情\\checkinfo.txt";
string CHECK_INFO_RECORD_SINGLE = "";
const string EXPORT_FILE_PATH = "导出文件\\";