#include "Library.h"
#include  <cstring>

inline void print(){
	cout << "name\t" << "ID\t" << "menmber\t" << "amount\t"
		<< "returnbook\t" << "borrowday\t\t\t" << "returnday\n";
}

inline string Time() {
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d-%X-%A", localtime(&t));
	string s = tmp;
	return s;
}

//初始化图书节点
library_node::library_node(int id, int bor, string _name, double pr, int _s, int bks, string aut, string rom, string bord, string red) :
	idnum(id), BorrowCount(bor), name(_name), price(pr), sum(_s), author(aut), borrowdate(bord), returndate(red), room(rom), booksum(bks) {}

student::student(int _ID, string _name, int _flag, int am, int meb, int rebok, string bord, string red)
	: ID(_ID), name(_name), flag(_flag), amount(am), menmber(meb), returnbook(rebok), borrowday(bord), returnday(red)
{
}

bool Library::CreatBook(const int n)
{
	if (n <= 0)
	{
		cout << setw(60) << "Unvalidated Input.\a\n";
		return false;
	}
	for (int x = 0; x != n; ++x)
	{
		cout << "please enter book ID:";
		cin >> node.idnum;

		cout << "\nplease enter book name:";
		cin >> node.name;

		cout << "\nplease enter book author:";
		cin >> node.author;

		cout << "\nplease enter book price:";
		cin >> node.price;

		cout << "\nplease enter book sum:";
		cin >> node.booksum;

		cout << "\nplease enter book room:";
		cin >> node.room;

		node.sum += node.booksum;
		list.push_front(node);
		system("cls");
		cout << "\n";
	}
	InFileToBook(InFileBook);
	return true;
}

bool Library::Delete(const int ID)
{
	auto x = list.begin();
	while (x != list.end())
	{
		if (x.current->val.idnum == ID)
		{
			list.erase(x);
			cout << setw(50) << "Deleting completed.\n";
			return true;
		}
		x++;
	}
	cout << setw(50) << "Not find.\n";
	return false;
}

void Library::find(const int n)
{
	auto itr = list.begin();
	while (itr != list.end())
	{
		if (itr.current->val.idnum == n)
		{
			system("cls");
			cout << itr.current->val.idnum << '\t' << itr.current->val.name << '\t' << itr.current->val.author << '\t'
				<< itr.current->val.price << '\t' << itr.current->val.room << '\t' << itr.current->val.booksum << '\t'
				<< itr.current->val.BorrowCount << '\n';
			return;
		}
		++itr;
	}
	cout << setw(50) << "Not find....\n";
}

bool Library::modification(const string name)
{
	show();
	auto itr = list.begin();
	while (itr != list.end())
	{
		if (itr.current->val.name == name)
		{
			int choose = 0;
			cout << setw(50) << "[1]-> ID\t[2]->name\t[3]->author\n"
				"[4]->price\n";
			cout << setw(30) << "please choose number: ";
			cin >> choose;
			string _name;
			switch (choose)
			{
			case 1:
				int ID;
				cout << setw(40) << "Enter a new book ID: ";
				cin >> ID;
				itr.current->val.idnum = ID;
				break;
			case 2:
				cout << setw(40) << "Enter a new book name: ";
				cin >> _name;
				itr.current->val.name = _name;
				break;
			case 3:
				cout << setw(40) << "Enter a new author name: ";
				cin >> _name;
				itr.current->val.author = _name;
				break;
			case 4:
				cout << setw(40) << "Enter the new price: ";
				double prc;
				cin >> prc;
				itr.current->val.price = prc;
				break;
			default:
				system("cls");
				cout << setw(60) << "Entent error.";
				system("pause");
				break;
			}
		}
		++itr;
	}
	return false;
}

void Library::InFileToBook(const char* filename)
{
	std::ofstream fout(filename, ios::out);  //写入文件
	if (!fout.is_open()) {
		cerr << "Can't open " << filename << endl;
		exit(EXIT_SUCCESS);
	}
	if (!list.IsEmpty()) {
		for (const auto& x : list) {
			fout << x.idnum << '\t' << x.name << '\t' << x.author << '\t' << x.price << '\t' << x.room << '\t' << x.booksum
				<< '\t' << x.sum << '\t' << x.BorrowCount << '\t' << x.borrowdate << '\t' << x.returndate << endl;
		}
	}
	fout.close();			//关闭文件流
}

bool Library::outFileToBook(const char* filename)   
{
	ifstream fin(filename, ios::in);


	if (!fin.is_open()) {
		cerr << "Can't open " << filename << endl;
		return false;
	}
	string oneline;
	while (fin.peek()!=EOF)
	{
		fin >> node.idnum >> node.name >> node.author >> node.price >> node.room >> node.booksum >> node.sum >> node.BorrowCount
			>> node.borrowdate >> node.returndate;
		getline(fin, oneline);		//删掉末尾的换行符
		list.push_back(node);      //保存到链表中
	}
	fin.close();
	return true;
}

void Library::InFileToStudent(const char* filename)
{
	ofstream fout(filename, ios::out | ios::trunc);
	if (!fout.is_open()) {
		cerr << "Can't open " << filename << endl;
		exit(EXIT_SUCCESS);
	}
	if (!slist.IsEmpty()) {
		for (const auto& itr : slist) {
			fout << itr.name << '\t' << itr.ID << '\t' << itr.menmber << '\t' << itr.amount << '\t' << itr.returnbook
				<< ' ' << itr.borrowday << '\t' << itr.returnday << endl;
		}
	}
	fout.close();
}

bool Library::outFileToStudent(const char* filename)
{
	ifstream fin(filename, ios::in);
	if (!fin.is_open()) {
		fin.close();
		cerr << "Can't open " << filename << endl;
		return false;
	}
	string oneline;
	while (!fin.eof())
	{
		fin >> stu.name >> stu.ID >> stu.menmber >> stu.amount >> stu.returnbook
			>> stu.borrowday >> stu.returnday;
		getline(fin, oneline);
		slist.push_back(stu);
	}
	fin.close();
	return true;
}

bool Library::Add(const int n)
{
	if (n <= 0)
	{
		cout << "Unvalidated Input.\a\n";
		return false;
	}
	for (int x = 0; x != n; ++x)
	{
		cout << "please enter book ID:";
		cin >> node.idnum;

		cout << "\nplease enter book name:";
		cin >> node.name;

		cout << "\nplease enter book author:";
		cin >> node.author;

		cout << "\nplease enter book price:";
		cin >> node.price;

		cout << "\nplease enter book sum:";
		cin >> node.sum;

		cout << "\nplease enter book room:";
		cin >> node.room;

		list.push_front(node);
		system("cls");
	}
	InFileToBook(InFileBook);
	show();								//添加完毕以后打印一遍数据
	return true;
}

void Library::show()
{
	system("cls");
	if (list.IsEmpty())
	{
		cout << "No data.\a\n";
		return;
	}
	//_unlink("D:/Book.txt");						//删除文件
	InFileToBook(InFileBook);						//从新写入文件
	cout << "BokID\t" << "name\t" << "author\t" << "price\t" << "room\t"
		<< "booksum\t" << "BorrowCount\t" << "borrowdate\t\t" << "returndate\n";
	for (const auto& x : list)
	{
		cout << x.idnum << '\t' << x.name << '\t' << x.author << '\t' << x.price << '\t' << x.room
			<< '\t' << x.booksum << '\t' << x.BorrowCount << "\t\t" << x.borrowdate
			<< "\t" << x.returndate << '\n';
	}
	cout << "\n";
}

void Library::BorrowBook()
{
	int n = 0;
	int flag = 0;
	int meber = 0;
	system("cls");
	cout << "Please enter the number of borrowers:  ";
	cin >> n;
	for (int x = 0; x != n; ++x)
	{
		cout << "Borrowing to student ID: ";
		cin >> stu.ID;
		cout << "Borrowing to student name: ";
		cin >> stu.name;
		show();														//打印图书情况
		cout << "please enter Book ID: ";
		cin >> meber;
		auto itr = list.begin();
		while (itr != list.end())
		{
			if (itr.current->val.idnum == meber)
			{
				flag = 1;
				cout << "Borrow books amount(Not more than 10): ";
				cin >> stu.amount;									//借阅数量
				node.BorrowCount += stu.amount;						//图书借阅数量
				if (stu.amount > 10)
				{
					stu.amount = 0;									//清零
					cout << "Not more than 10 !!!\a";
					return;
				}
				else
				{
					//获取时间
					itr.current->val.borrowdate = stu.borrowday = Time();
					stu.menmber = itr.current->val.idnum;			 //书本ID
					itr.current->val.booksum -= stu.amount;			 //减去相应的借阅数量
					itr.current->val.BorrowCount += stu.amount;		 //借阅量
					slist.push_front(stu);
					InFileToStudent(InFileStu);						 //写入文件
					cout << "Borrowing to complete.\n";
					system("pause");
					return;
				}
			}
			++itr;
		}
	}
	if (flag == 0) {
		cout << "Not find book ID: " << n << endl;
		system("pause");
		return;
	}
}

void Library::ReturnBook()
{
	int flag = 0;
	int borID = 0;
	if (slist.IsEmpty()) {
		cout << "Not Data.\n";
		system("pause");
		return;
	}
	Traverse(); //打印借阅情况
	cout << "please enter return the number : ";
	cin >> borID;
	auto itr = slist.begin();
	char choose = '\0';
	while (itr != slist.end())
	{
		if (itr.current->val.menmber == borID)
		{
			cout << "Do you confirm the return(y/n)? ";
			cin >> choose;
			choose = toupper(choose);
			if (choose == 'Y')
			{
				cout << "enter return amount: ";
				int n = 0;
				cin >> n;
				if (n > stu.amount)
				{
					cout << "Error: More than the number borrowed.the book failed to return.\a\n";
					return;
				}
				else
				{
					flag = 1;
					stu.amount -= n;									    //减去相应的还书数量
					stu.returnbook = stu.amount;
					itr.current->val.returnday = Time();				    //归还时间
					stu.flag = 1;
					InFileToStudent(InFileStu);							    //将数据写入文件
					for (auto& x : list) {
						if (x.idnum == borID) {
							x.returndate = itr.current->val.returnday;		//到书库中修改归还时间
						}
					}
					return;
				}
			}
		}
		++itr;
	}
	if (flag == 0) {
		cout << "Return the book failed...\a\n";
		return;
	}
}

void Library::Traverse()
{
	system("cls");
	if (slist.IsEmpty())
	{
		cout << "Not Data.\a\n";
		return;
	}
	print();
	InFileToStudent(InFileStu);
	for (const auto& itr : slist)
	{
		cout << itr.name << '\t' << itr.ID << '\t' << itr.menmber << '\t' << itr.amount << '\t'
			<< itr.returnbook << "\t" << itr.borrowday << '\t' << itr.returnday << endl;
	}
}
