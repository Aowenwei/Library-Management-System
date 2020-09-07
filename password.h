#pragma once
#ifndef PASSWORD_H_
#define PASSWORD_H_

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class password
{
private:
	string user, word;
	//删除默认函数
	bool operator!=(const password& rhs) = delete;
	password& operator=(const password& rhs) = delete;

public:
	password(string u = "\0", string ps = "\0") : user(u), word(ps) {};
	~password() {}
	bool regest(const char* filename)
	{
		cout << "please enter user: ";
		cin >> user;
		int i = 0;
		int flag = 0;
		string temp = "\0";
		ifstream fin(filename, ios::in);
		ofstream fout(filename, ios::app | ios::out);
		if (!fout.is_open())
		{
			cerr << "Can't open user.txt\n";
			exit(EXIT_SUCCESS);
		}
		while (fin >> temp)
		{
			i++;
			if (i % 2 == 0)
				continue;				 //访问的是密码这一行，跳出。
			if (user == temp)
				flag = 1;				 //flag=1说明用户名已经被注册了
		}
		fin.close();					 //关闭文件流
		if (flag)
		{
			cerr << "The account has been registered.\n";
			return false;					 //之前有重复的账户名
		}
		else							 //没被注册过
		{
			cout << "plear enter password: ";
			cin >> word;
			fout << user << ' ' << word << '\n';
			fout.close();
			return true;
		}
		return true;
	}

	bool login(const char* filename)
	{
		ifstream extract(filename, ios::in); //抽取文件信息
		if (!extract.is_open())
		{
			cerr << "Can't open user.txt\n";
			exit(EXIT_SUCCESS);
		}
		string in_user, in_psw, temp;
		cout << "Please input user name: ";
		cin >> in_user;
		int flag = 0;
		int n = 3;
		while (extract >> temp)
		{
			if (temp == in_user)
			{
				flag = 1;
				extract >> temp;
				for (int x = 0; x != 3; ++x)
				{
					cout << "Please enter your password: ";
					cin >> in_psw;
					if (temp == in_psw)		//抽取的文件数据与输入比较
					{
						system("cls");		//windows 清屏函数
						cout << "login successfully: ";
						extract.close();
						return true;
					}
					else
					{
						system("cls");
						cout << "Wrong password. residue degree: " << --n << endl;
						if (n == 0)
						{
							system("cls");
							extract.close();
							return false;
						}
					}
				}
				extract.seekg(1, ios::cur); //第一个单词得末尾得后一个字符
			}
			flag = 0;						//用户名匹配失败
		}
		if (flag == 0)
		{
			cout << "The user name match failed.\a\n";
			return false;	  		       //终止程序
		}
		return true;
	}
};

#endif //PASSWORD_H_