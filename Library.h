#pragma once
#ifndef LIBRARY_H_
#define LIBRARY_H_
#include<ctime>
#include<iomanip>
#include <string>
#include "MyList.h"
#include "password.h"

using std::setw;
using std::string;

enum MyEnum
{
	zere = 0,
	one,
	two,
	three,
	four,
	five,
	six,
	seven,
	eight
};

struct library_node
{
	int idnum;										//图书检索号
	int BorrowCount;							    //图书借阅量,初始化为0
	string name;									//书名
	double price;									//图书价格
	int booksum;									//当前书本数量
	int sum;										//图书总库存存量
	string author;									//图书作者
	string borrowdate;								//图书最近一次借出时间
	string returndate;								//图书最近一次归还时间
	string room;									//馆藏地
	library_node(int id = 0, int bor = 0, string _name = "\0", double pr = 0.0, int _s = 0, int bks = 0,
		string aut = "\0", string rom = "\0", string bord = "0-0-0", string red = "0-0-0");
};

struct student
{
	int ID;											//读者编号
	string name;									//读者姓名
	int flag;										//归还标记
	int amount;										//借阅数量
	int menmber;									//图书ID
	int returnbook;									//现在还有多少本书未还，默认为0
	string borrowday;								//借阅时间
	string returnday; 								//归还时间
	student(int _ID = 0, string _name = "\0", int _flag = 0, int am = 0, int meb = 0, int rebok = 0, string bord ="0-0-0", string red = "0-0-0");
};

class Library
{
private:
	student stu;
	library_node node;
	MyList<student> slist;
	MyList<library_node> list;
public:
	//写入文件路径
	const char* InFileBook = "D://Book.txt";
	const char* InFileStu = "D://Student.txt";
public:

	Library() :node(), list(), stu(), slist() {}
	~Library() { cout << "感谢使用\n"; };
	bool CreatBook(const int n);					     //构建图书
	bool Add(const int n);								 //添加图书
	bool Delete(const int ID);							 //删除图书
	void find(const int n);								 //查询图书
	void show();										 //打印图书
	void BorrowBook();									 //借书
	void ReturnBook();									 //还书
	void Traverse();									 //借书情况
	bool modification(const string name);
	bool outFileToBook(const char* filename);			 //保存到链表中
	bool outFileToStudent(const char* filename);
	void InFileToBook(const char* filename);			 //写入到文件中
	void InFileToStudent(const char* filename);
};


#endif // LIBRARY_H_