#include "Library.h"
#include"password.h"
#include<Windows.h>

#pragma comment(lib, "winmm.lib") //有些东西会报错

void Load();
void menu(Library& library);
void Book_client(Library& library);
void Student_client(Library& library);
bool login(const password& pws, const char* filename);	 //登录

//读取文件路径
const char* TecherWord = "D://Tpsw.txt";
const char* StudentWord = "D:/Spsw.txt";

int main(int argc, char* argv[]) {
	Library lib;
	mciSendString(L"open bk.mp3 alias music", 0, 0, 0); // open bgm
	mciSendString(L"play music", 0, 0, 0);              // 播放
	system("color 5B");
	Load();
	if(!(lib.outFileToBook("D://Book.txt")) || !(lib.outFileToStudent("D://Student.txt"))) {
		system("pause");
	}
	menu(lib);
	return 0;
}

bool login(password& pws, const char* filename)
{
	system("cls");
	int pw = 0;
	bool flag = false;  //接收返回值
	cout << setw(50) << "[1]->sign in\t\t[2]->log in\n";
	cin >> pw;
	if (pw == 1) {
		flag = pws.regest(filename);
		return flag;
	}
	if (pw == 2)
		flag = pws.login(filename);
	return flag;
}

void Load()
{
	cout.width(30);
	std::cout << "\nReading file...... ";
	for (int i = 0; i <= 100; i++)      // 打印百分比 
	{
		std::cout.width(3);				//i的输出为3位宽
		std::cout << i << "%";
		Sleep(22);
		std::cout << "\b\b\b\b";		//回删三个字符，使数字在原地变化
	}
	cout << endl;
}

void menu(Library& lib) {
	int n = 1;
	password stu, book;
	while (1)
	{
		system("cls");
		cout << setw(70) << "[1]-->Book_client\t [2]-->Student_client\n";
		cout << setw(35) << "please enter: ";
		cin >> n;
		switch (n)
		{
		case one:
			if (login(book, TecherWord) == true) {
				Book_client(lib);
				break;
			}
			else
				exit(EXIT_SUCCESS);
			Book_client(lib);
			break;
		case two:
			if (login(stu, StudentWord) == true) {
				Student_client(lib);
				break;
			}
			else
				exit(EXIT_SUCCESS);
			Student_client(lib);
			break;
		default:
			system("cls");
			cout << setw(50) << "Enter error.\a\n";
			Sleep(1000);
			break;
		}
	}
}

void Student_client(Library& library)
{
	int choose = 0;
	system("cls");
	cout << setw(70) << "Welcome to the student client.\n";
	Sleep(1000);
	while (true)
	{
		system("cls");
		cout << setw(60) << "[1]-> Borrow books.\n";
		cout << setw(63) << "[2]-> Return the book.\n";
		cout << setw(52) << "[3]-> Mune.\n";

		cout << setw(30) << "please enter: ";
		cin >> choose;
		switch (choose)
		{
		case one:
			library.BorrowBook();
			break;
		case two:
			library.ReturnBook();
			system("pause");
			break;
		case three:
			menu(library);
			break;
		default:
			system("cls");
			cout << setw(60) << "Enter error.\a\n";
			system("pause");
			break;
		}
	}
}

void Book_client(Library& library)
{
	system("cls");
	int choose = 0;
	string name = "\0";
	cout << setw(70) << "***** Library Management System *****\n";
	Sleep(1000);
	while (true)
	{
		system("cls");
		cout << setw(60) << "[1]-> Create a book.\n";
		cout << setw(58) << "[2]-> Add q books.\n";
		cout << setw(60) << "[3]-> Delete a book.\n";
		cout << setw(59) << "[4]-> Query a book.\n";
		cout << setw(63) << "[5]-> Modify the books.\n";
		cout << setw(59) << "[6]-> Library data.\n";
		cout << setw(63) << "[7]-> Borrow situation.\n";
		cout << setw(51) << "[8]-> Menu.\n";
		cout << setw(38) << "please enter: ";
		cin >> choose;
		switch (choose)
		{
		case zere:
			system("cls");
			cout << "\n\n\n\nThank you for using\n\n\n\n";
			exit(EXIT_FAILURE);
		case one:
			system("cls");
			int n;
			cout << setw(40) << "please enter the number of:";
			cin >> n;
			library.CreatBook(n);
			break;
		case two:
			system("cls");
			int _n;
			cout << setw(40) << "please enter the number of:";
			cin >> _n;
			library.Add(_n);
			system("pause");
			break;
		case three:
			library.show();
			int member;
			cout << setw(40) << "Please enter the book ID you want to delete:";
			cin >> member;
			library.Delete(member);
			system("pause");
			break;
		case four:
			system("cls");
			int ID;
			cout << setw(40) << "Please enter the ID you want to query:";
			cin >> ID;
			library.find(ID);
			system("pause");
			break;
		case five:
			library.show();
			cout << setw(40) << "Please enter the modified name:";
			cin >> name;
			library.modification(name);
			system("pause");
			break;
		case six:
			library.show();
			system("pause");
			break;
		case seven:
			library.Traverse();
			system("pause");
			break;
		case eight:
			menu(library);
			break;
		default:
			system("cls");
			cout << setw(40) << "enter error.\a\n";
			Sleep(1000);
			break;
		}
	}
}
