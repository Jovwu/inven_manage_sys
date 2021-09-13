#include "widget.h"
#include "label.h"
#include "button.h"
#include "edit.h"
#include "select.h"
#include "border.h"
#include "user.h"
#include "goods.h"
#include "checknote.h"
#include "checkinfo.h"

#include "time.h"
#include "userfile.h"
#include "goodsfile.h"
#include "checkinfofile.h"
#include "checknotefile.h"
#include "table.h"
#include "window.h"

#include "login.h"
#include "reg.h"

#include "app.h"


#include <stack>

#include "checkmenu.h"
#include "goodsquery.h"
#include "checkstock.h"
#include "checkrecord.h"
#include "checkrecordsingle.h"
#include "addgoods.h"
#include "managermenu.h"
#include "goodsoutin.h"
#include "goodsoutrecord.h"
//#include "userfile.h"

void main()
{
	

	App();

	/*商品出库界面*/
	/*(new GoodsOutRecord())->Run();*/

	/*出入库界面*/
	/*(new GoodsOutIn())->Run();*/

	/*管理员界面*/
	/*(new ManagerMenu())->Run();*/

	/*商品添加页面*/
	//(new AddGoods())->Run();

	/*盘点详细记录页面*/
	//CHECK_INFO_RECORD_SINGLE = "20200405-002.txt";
	//(new CheckRecordSingle())->Run();

	/*盘点信息界面*/
	/*(new CheckRecord())->Run();*/

	/*商品盘点界面*/
	/*(new CheckStock())->Run();*/


	/*商品查询界面*/
	/*(new GoodsQuery())->Run();*/

	/*盘点员界面*/
	/*(new CheckMenu())->Run();*/

	

	//Border* b = new Border(3,3,30,10);
	


	/*Login* login = new Login();
	login->Run();*/

	//Reg* reg = new Reg();
	//reg->Run();

	
	/*Button* login = new Button("登录", 44, 19);
	Widget* p = login;
	cout << login;
	cout << p;
	if (login == p )
	{
		cout << "ad";
	}*/

	/*LoginMsgBox* MS = new LoginMsgBox();
	MS->Run();*/
	/*Window测试*/

	/*Widget测试*/

	/*Table*/
	//Table* table = new Table(1,"测试表格",4,4);//初始化基本信息
	//table->SetFile(new UserFile());//设置文件
	//table->SetPaging(3);//设置分页信息
	////设置触发条件
	//table->AddTh("用户ID");
	//table->AddTh("用户名");
	//table->AddTh("用户密码");
	//table->AddTh("角色类型");
	//table->Load();
	//table->GetCursor();
	//GoToXY(20,20);
	//cout << table->OnClick() << endl;
	//cout << table->GetClickTd();

	//
	//Sleep(5000);

	/*cout << "＜ 1/5 ＞" << endl;
	cout << "≮ 5/5 ≯" << endl;*/




/*Label测试*/
	//Label* label = new Label(1,"测试",4,4);
	//label->Load();

	/*Button测试*/
//    Button* button = new Button(2,"测试",4,4);
//	button->SetEvent(BtnOn);
//	button->Load();
//	button->GetCursor();
//	Sleep(500);
// 	button->LostCursor();

	/*Eidt测试*/
	//Edit* edit = new Edit(3,"测试文字",4,4,"ONLYFIGURE", EDIT_INPUT_MAX);
	//edit->SetValue("");
	//edit->Load();
	//edit->GetCursor();
	//GoToXY(20,20);
	//cout << edit->GetValue() << endl;
 //	Sleep(8000);


	

	/*Select测试*/
//	Select* select = new Select(4,"",4,4);
//	select->AddOption("选项1");
//	select->AddOption("选项2");
//	select->AddOption("选项3");
//	select->AddOption("选项4");
//	select->Load();
//	select->GetCursor();
//	select->OnClick();
//
// 	system("pause");

								/*Class测试*/

	/*User类测试*/
//	User* user = new User(1,"钟石羽","zsy123456","管理员");
//	cout<<"ID:"<<user->GetID()<<endl;
//	cout<<"Name:"<<user->GetName()<<endl;
//	cout<<"PassWord:"<<user->GetPassWord()<<endl;
//	cout<<"TYPE:"<<user->GetTYPE()<<endl;

	/*Goods类测试*/

//	Goods* goods = new Goods("1","iphoneSE","手机",2222.22,5,"XXX111");
//	cout<<"ID"<<goods->GetID()<<endl;
//	cout<<"Name"<<goods->GetName()<<endl;
//	cout<<"Type"<<goods->GetType()<<endl;
//	cout<<"Price"<<goods->GetPrice()<<endl;
//	cout<<"Count"<<goods->GetCount()<<endl;
//	cout<<"LocID"<<goods->GetLocID()<<endl;

	/*CheckNote*/ /*CheckInfo*/
	/*CheckInfo* checkinfo = new CheckInfo("20200322","DX191118","GD1111",50,30);
	cout<<"ID:"<< checkinfo->GetID()<<endl;
	cout<<"User:"<< checkinfo->GetUser()<<endl;
	cout<<"Date:"<< checkinfo->GetCheckDate()<<endl;
	cout<<"Goods:"<< checkinfo->GetGoods()<<endl;
	cout<<"OrgCount:"<< checkinfo->GetOrgCount()<<endl;
	cout<<"CheckCount:"<< checkinfo->GetCheckCount()<<endl;
	cout << endl;
	CheckNote* checkNote = new CheckNote("20200322");
	checkNote->SetExplain("降低哇哦的霍瓦河对哇和第五啊");
	cout << "ID:" << checkNote->GetID() << endl;
	cout << "Reverse:" << checkNote->GetReverse() << endl;
	cout << "Explain:" << checkNote->GetExplain() << endl;*/

				/*Tools测试*/

	/*Time测试*/
	/*string time = DateToSrting();
	cout << time;*/


	/*******************************Config测试******************************************************/

	//Config::Init();
	//cout << Config::App::UserFilePath << endl;
	//cout << Config::App::GoodsFilePath << endl;
	//cout << Config::App::CheckNoteFilePath << endl;
	//cout << Config::App::CheckInfoFilePath << endl;

	/*******************************UserFile类测试******************************************************/

	//UserFile* u = new UserFile();
	//u->AppendUser(new User("1","钟石羽","password","管理员"));
	//User* user = u->GetUser(u->Select(1,"1"));
	//cout << user->GetID() << endl;
	//cout << user->GetName() << endl;
	//cout << user->GetPassWord() << endl;
	//cout << user->GetTYPE() << endl;

	/*******************************GoodsFile类测试******************************************************/

	//GoodsFile* g = new GoodsFile();
	//g->AppendGoods(new Goods("20200323DD","iphoneSE","手机",2223.32,20,"DWW22"));
	//Goods* goods = g->GetGoods(g->Select(3, "手机"));
	//cout << goods->GetID() << endl;
	//cout << goods->GetName() << endl;
	//cout << goods->GetType() << endl;
	//cout << goods->GetPrice() << endl;
	//cout << goods->GetCount() << endl;
	//cout << goods->GetLocID() << endl;

/*******************************CheckInfoFile类测试******************************************************/

	/*CheckInfoFile* s = new CheckInfoFile();
	s->AppendCheckInfo(new CheckInfo("ID111","钟石羽","iphoneSE",30,40));
	CheckInfo* a = s->GetCheckInfo(s->Select(1, "ID111"));*/

/*******************************CheckNoteFile类测试******************************************************/
	
	/*CheckNoteFile* f = new CheckNoteFile();
	f->AppendCheckNote(new CheckNote("ID111"));
	CheckNote* n = f->GetCheckNote(f->Select(1, "ID111"));*/

	/*******************************File类测试******************************************************/
	

	/*File* file = new File("user.txt");

	/*Count*/
	/*cout << file->Count();*/

	/*SelectByRow*/
	//string str = file->SelectByRow(1);


	/*All*/
	/*vector<string> Res = file->All();*/

	/*DelectAll*/
	//bool i = file->DeleteAll(4, "盘点员");
	//cout << i;

	/*SelectRowAll*/
	//vector<int> v = file->SelectRowAll(4,"盘点员");
	//int i = 0;
	//while ((v.begin() + i) != v.end())
	//{
	//	cout << *(v.begin() + i) << endl;
	//	i++;
	//}

	/*Delete*/
	/*bool i = file->Delete(4,"管理员");
	cout << i;*/

	/*SelectAllFuzzy*/
	//vector<string> v = file->SelectAllFuzzy(4,"盘点");
	//int i = 0;
	//while ((v.begin()+i) != v.end())
	//{	
	//	cout << *(v.begin() + i) << endl;
	//	i++;
	//}


	/*SelectFuzzy*/
	/*string str = file->SelectFuzzy(4,"理员");
	cout<<str;*/

	/*Select*/
	/*string str = file->Select(4,"盘点员");
	cout << str << endl;*/

	/*SelectRow*/
	/*int Row = file->SelectRow(4,"盘点员");
	cout << Row << endl;*/

	/*SelectAll*/
	/*vector<string> v;
	vector<string>::iterator It;
	v = file->SelectAll( 4,"管理员");
	for (It = v.begin(); It != v.end(); It++)
	{
		cout << *It << endl;
	}*/

	/*Modify*/
	/*bool res = file->Modify(2,"庄江海",4,"盘点员");
	cout << res << "|" << endl;*/

 //   cout << "-------------------------------------"<< endl;0
	//cout << "|--数据--|--数据--|--数据--|--数据--|" << endl;1
	//cout << "-------------------------------------" << endl;2
	//cout << "|123456  |  数据  |  数据  |  数据  |" << endl;3
	//cout << "-------------------------------------" << endl;4
	//cout << "|  数据  |  数据  |  数据  |  数据  |" << endl;5
	//cout << "-------------------------------------" << endl;6
	//cout << "|  数据  |  数据  |  数据  |  数据  |" << endl;7
	//cout << "-------------------------------------" << endl;8

	/*cout << "**********************";
	cout << "*					  *";
	cout << "**********************";
	cout << "**********************";
	cout << "**********************";
	cout << "**********************";
	cout << "**********************";*/

	/*cout << "――" << endl;
	cout << "｜" << endl;
	cout << "︱" << endl;
	cout << "︱" << endl;
	*/

/***************************************Console测试********************************************/


	
     
}


