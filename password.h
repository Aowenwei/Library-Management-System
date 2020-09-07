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
	//ɾ��Ĭ�Ϻ���
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
				continue;				 //���ʵ���������һ�У�������
			if (user == temp)
				flag = 1;				 //flag=1˵���û����Ѿ���ע����
		}
		fin.close();					 //�ر��ļ���
		if (flag)
		{
			cerr << "The account has been registered.\n";
			return false;					 //֮ǰ���ظ����˻���
		}
		else							 //û��ע���
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
		ifstream extract(filename, ios::in); //��ȡ�ļ���Ϣ
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
					if (temp == in_psw)		//��ȡ���ļ�����������Ƚ�
					{
						system("cls");		//windows ��������
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
				extract.seekg(1, ios::cur); //��һ�����ʵ�ĩβ�ú�һ���ַ�
			}
			flag = 0;						//�û���ƥ��ʧ��
		}
		if (flag == 0)
		{
			cout << "The user name match failed.\a\n";
			return false;	  		       //��ֹ����
		}
		return true;
	}
};

#endif //PASSWORD_H_