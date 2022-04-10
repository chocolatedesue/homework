#pragma once
//
// Created by choco on 10/4/2022.
//

#ifndef LIBSIM_LIBRARY_H
#define LIBSIM_LIBRARY_H

#pragma once

#include "bits/stdc++.h"
#include "basic_member.h"
#include <regex>

using namespace std;
// using namespace std;

class Library
{
	//通过id 查找书
	std::map<int, book> id_booklist;

	//通过id找读者
	std::map<int, reader> id_reader;

	//通过读者名字找读者id (不允许重名)
	std::map<std::string, int> name_reader_id;

	//通过书名找书id
	std::map<std::string, int> name_booklistname_id;

	//通过书名找借给的人的id
	std::map<int, std::vector<int>> lent_book;

	std::map<int, admin> admin_list;

	void info_parser(string mess)
	{
		regex pat(R"(,)");
		sregex_token_iterator pos(mess.begin(), mess.end(), pat, -1);
		sregex_token_iterator end;
		int user_id = stoi(pos->str());
		pos++;
		string user_name = pos->str();
		pos++;
		int book_id = stoi(pos->str());
		pos++;
		string book_name = pos->str();
		add_id_book_list(book_id, book_name);
		add_id_reader(user_id, user_name);
		add_lent_book(user_id, book_id);
	}

	void admin_parser(string mess)
	{
		regex pat(R"(,)");
		sregex_token_iterator pos(mess.begin(), mess.end(), pat, -1);
		sregex_token_iterator end;
		int admin_id = stoi(pos->str());
		pos++;
		string admin_name = pos->str();
		pos++;
		string admin_passwd = pos->str();
		admin_list[admin_id] = admin{ admin_id, admin_name, admin_passwd };
	}

	void add_lent_book(int user_id, int book_id)
	{
		if (!lent_book.count(book_id))
		{
			lent_book[book_id] = vector<int>(1, user_id);
		}
		else
			lent_book[book_id].push_back(user_id);
	}

	void add_id_reader(int user_id, const string& user_name)
	{
		if (!id_reader.count(user_id))
		{
			id_reader[user_id] = reader{ user_id, user_name };
			name_reader_id[user_name] = user_id;
		}
		else
		{
			cout << "读者id重复，添加失败" << endl;
		}
	}

	void add_id_book_list(int book_id, const string& book_name)
	{
		if (!id_booklist.count(book_id))
		{
			id_booklist[book_id] = book{ book_name, book_id, 1 };
			name_booklistname_id[book_name] = book_id;
		}
		else
		{
			id_booklist[book_id].setNum(id_booklist[book_id].getNum() + 1);
		}
	}

	void data_loader()
	{
		info_loader();
		admin_loader();
	}

	void info_loader()
	{
		FILE* fp = fopen("info_table.csv", "r");
		if (!fp)
		{

			cout << "程序加载失败，请检查是否存在初始化文件info_table.csv" << endl;
			std::cout << "自动生成初始化文件info_table.csv中" << std::endl;
			//freopen("info_table.csv", "w", stdout);
			fp = fopen("info_table.csv", "w");
			fputs("1,user,1,星星之火可以燎原", fp);
	
			fclose(fp);
		}

		{
			/*freopen("info_table.csv", "r", stdin);*/
			ifstream inFile("info_table.csv");
			string temp;
			while (getline(inFile,temp))
			{
				cout << temp << endl;
				info_parser(temp);
			}
			inFile.close();
		}
	}

	void admin_loader()
	{

		FILE* fp = fopen("admin_table.csv", "r");

		if (fp == NULL)
		{
			cout << "程序加载失败，请检查是否存在初始化文件admin_table.csv" << endl;
			std::cout << "自动生成初始化文件admin_table.csv中" << std::endl;
			fp = fopen("admin_table.csv", "w");
			fputs("1,admin,123456", fp);
			//cout << "1,admin,123456" << endl;
			fclose(fp);
		}

		{
			//freopen("admin_table.csv","r",stdin);
			ifstream inFile("admin_table.csv");

			string temp;
			while (getline(inFile,temp))
			{
				cout << temp << endl;
				admin_parser(temp);
			}
			inFile.close();
		}
	}








public:
	Library()
	{
		cout << "欢迎使用图书管理系统,数据加载中" << endl;
		data_loader();
		cout << "数据加载结束" << endl;
	}
};

#endif // LIBSIM_LIBRARY_H
