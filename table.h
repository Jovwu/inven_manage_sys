#ifndef _TABLE_H_
#define _TABLE_H_
#include "widget.h"
#include <vector>
#include <stack>
#include "file.h"
#include "console.h"
#include "td.h"

#define SELECT_ONLY 1
#define SELECT_ALL 2
#define SELECT_FUZZY_ONLY 3
#define SELECT_FUZZY_ALL 4

#define CLICK_NULL 0
#define CLICK_ENTER 1

#define INFO_ORG 0
#define INFO_SELECT 1

class Table:public Widget
{
public:

	Table(const string Value, int POSITION_X, int POSITION_Y);

	int Load();//控件加载-->显示到屏幕上
	int GetCursor();//获得焦点
	int LostCursor();//失去焦点
	int OnClick();//控件根据操作获得响应
	int Refresh();//刷新控件
	bool RefreshHint();//刷新提示

	int AddTh(const string ThMember);//添加表头-->绘制"-"
	int SetThW(int ThW);//设置表格宽度
	int ClickHint();//触发高亮
	int ClearHint();//清除高亮
	bool Update(int Page);//更新表格的内容到第几页

	bool PushState();
	bool PopState();

	/*精确搜索*/
	bool Select(int Parameter, const string Target);
	bool SelectAllFuzzy(int Parameter, const string Target);//根据条件查询所有符合信息
	/*设置触发模式*/
	bool SetClickMode(int ClickMode);
	/*设置数据总数*/
	int SetContentTotal(int ContentTotal);
	/*设置文件*/
	int SetFile(File* file);
	/*设置分页信息*/
	int SetPaging(int Row);
	/*返回单条信息*/
	vector<string> GetClickTd() const;
	/*返回内容*/
	vector<Td*> GetContent() const;
	/*导出表格内容到指定路径文件*/
	bool ExprotContent(const string Path);
	/*读入所有内容*/
	bool InputAllContent();
	/*设置重读一次*/
	bool SetLoadAgain();


private:

	//布局信息
	vector<string> Th;//表头内容
	vector<int> ThW;//表头宽度->创建表头时创建
	int Row;//表格行数-->用于显示的文本数量,SetPaging时写入
	int Col;//表格列数-->由表头数量决定，加载时初始化

	//显示内容
	File* file;//表格文件

	
	int ContentFlag;//显示内容标志位
	vector<Td*> Content;//显示内容
	vector<Td*> SelectContent;//搜索内容

	int ContentTotal;//内容总数->SetFile时写入

	//提示信息：在最下框：数据的数量，当前为第几条
	int HintCenterX;//焦点中央X-->界面加载时赋值
	int HintCenterY;//焦点中央Y-->界面加载时赋值

	//焦点相关
	int CursorLine;//当前获得焦点的行
	

	//分页信息
	int TotalPageNum;//信息总页数-->加载时根据Row生成
	int PageNum;//当前信息页数--->初始值为1,根据OnClick选择+1还是-1
	int BrowseYet;//已浏览页数->用于判断是否去文件取，还是直接从内存取,即缓存到本地

	//触发条件及方式
	/*0:无操作，只能左右翻页。
	  1:可以使用上下键选中行，按确认键将设置ClickTD，并返回ENTER_KEY
    */
	int ClickMode;
	/*搜索模式*/
	int SelectMode;
	vector<string> ClickTd;//被选中的内容

	/*状态栈*/
	stack<int> StateStack;

	/*重新加载内容标志位*/
	int LoadContentFlag;

};



#endif // !_TABLE_H_
