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

//资源类
public:
	int reader_num, admin_num, book_num;
	//通过id 查找书
	std::map<int, book> id_booklist;

	//通过id找读者
	std::map<int, reader> id_reader;

	//通过读者名字找读者id (不允许重名)
	std::map<std::string, int> name_reader_id;

	//通过书名找书id
	std::map<std::string, int> name_booklistname_id;

	//通过书id找借给的人的id(借走的书）
	std::map<int, int> lent_book;

	
	//管理员信息
	std::set<admin>admin_list;
	
	//读者信息
	std::set<reader>reader_list;
	//剩下的书
	//1. user 借书，还书, 查询自己的书     2. admin 图书录入 
 	std::set<book>remain_book_list;



//加载类
private:
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
		admin_list.insert(admin{ admin_id,admin_name,admin_passwd });
	}
	void remain_book_parser(string mess) {
		regex pat(R"(,)");
		sregex_token_iterator pos(mess.begin(), mess.end(), pat, -1);
		sregex_token_iterator end;
		int	book_id = stoi(pos->str());
		pos++;
		string book_name = pos->str();
		pos++;
		int  book_num = stoi(pos->str());
		remain_book_list.insert(book{book_name,book_id,book_num});

	}


	void add_lent_book(int user_id, int book_id)
	{
		
			lent_book[book_id]=user_id;
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
			id_booklist[book_id].num+=1;
		}
	}

	void user_info_parser(string mess) {
		regex pat(R"(,)");
		sregex_token_iterator pos(mess.begin(), mess.end(), pat, -1);
		sregex_token_iterator end;
		int id = stoi(pos->str());
		pos++;
		string name = pos->str();
		reader_list.insert(reader(id, name));
	}


	void data_loader()
	{
		system("if not exist data (mkdir data)");
		config_load();
		info_loader();
		admin_loader();
		reader_loader();
		book_loader();
	}

	void config_load() {

		//格式书的个数，admin的个数，用户的个数
		FILE* fp = fopen("./data/config.txt", "r");
		if (!fp)
		{

			cout << "程序加载失败，请检查是否存在初始化文件config.txt" << endl;
			fp = fopen("./data/config.txt", "w");
			fputs("1 1 1", fp);
			fclose(fp);
		}

		{
			
			ifstream inFile("./data/config.txt");
			string temp;
			//getline(cin, temp);
			getline(inFile, temp);
			cout << temp +"  "<<temp.size() << endl;
			book_num = temp[0], admin_num = temp[2], reader_num = temp[4];

		}

		fclose(fp);

	}

	void reader_loader() {
		FILE* fp = fopen("./data/reader_table.csv", "r");
		if (!fp)
		{

			cout << "程序加载失败，请检查是否存在初始化文件reader_table.csv" << endl;
			std::cout << "自动生成初始化文件reader_table.csv中" << std::endl;
			//freopen("info_table.csv", "w", stdout);
			fp = fopen("./data/reader_table.csv", "w");
			fputs("1,user", fp);

			fclose(fp);
		}

		{
			/*freopen("info_table.csv", "r", stdin);*/
			ifstream inFile("./data/reader_table.csv");
			string temp;
			while (getline(inFile, temp))
			{
				cout << temp << endl;
				user_info_parser(temp);
			}
			inFile.close();
		}

		fclose(fp);


	}
	void book_loader() {
		FILE* fp = fopen("./data/remain_book_table.csv", "r");
		if (!fp)
		{

			cout << "程序加载失败，请检查是否存在初始化文件remain_book_table.csv" << endl;
			std::cout << "自动生成初始化文件remain_book_table.csv中" << std::endl;
			//freopen("info_table.csv", "w", stdout);
			fp = fopen("./data/remain_book_table.csv", "w");
			fputs("1,星星之火可以燎原,1", fp);

			fclose(fp);
		}

		{
			/*freopen("info_table.csv", "r", stdin);*/
			ifstream inFile("./data/remain_book_table.csv");
			string temp;
			while (getline(inFile, temp))
			{
				cout << temp << endl;
				remain_book_parser(temp);
			}
			inFile.close();
		}

		fclose(fp);
	}

	void info_loader()
	{
		FILE* fp = fopen("./data/info_table.csv", "r");
		if (!fp)
		{

			cout << "程序加载失败，请检查是否存在初始化文件info_table.csv" << endl;
			std::cout << "自动生成初始化文件info_table.csv中" << std::endl;
			//freopen("info_table.csv", "w", stdout);
			fp = fopen("./data/info_table.csv", "w");
			fputs("1,user,1,星星之火可以燎原", fp);

			fclose(fp);
		}

		{
			/*freopen("info_table.csv", "r", stdin);*/
			ifstream inFile("./data/info_table.csv");
			string temp;
			while (getline(inFile, temp))
			{
				cout << temp << endl;
				info_parser(temp);
			}
			inFile.close();
		}

		fclose(fp);
	}

	void admin_loader()
	{
		
		FILE* fp = fopen("./data/admin_table.csv", "r");
		//ifstream fp("admin_table.csv")
		if (fp == NULL)
		{
			cout << "程序加载失败，请检查是否存在初始化文件admin_table.csv" << endl;
			std::cout << "自动生成初始化文件admin_table.csv中" << std::endl;
			fp = fopen("./data/admin_table.csv", "w");
			fputs("1,admin,123456", fp);
			//cout << "1,admin,123456" << endl;
			fclose(fp);
		}

		{
			//freopen("admin_table.csv","r",stdin);
			ifstream inFile("./data/admin_table.csv");

			string temp;
			while (getline(inFile, temp))
			{
				cout << temp << endl;
				admin_parser(temp);
			}
			inFile.close();
		}
		fclose(fp);
	}







//初始化类
public:
	Library()
	{
		cout << "欢迎使用图书管理系统,数据加载中" << endl;
		data_loader();
		cout << "数据加载结束" << endl;
	}

	bool check_valid_admin(const int& id, const string& name, const string& passwd) {
		admin login = admin(id, name, passwd);
		auto res = *(lower_bound(admin_list.begin(), admin_list.end(), login));
		if (res == login) {
			return true;
		}
		else return false;

	}
	bool check_valid_reader(const int& id, const string& name) {
		reader login = reader(id, name);
		auto res = *(lower_bound(reader_list.begin(), reader_list.end(), login));
		if (res == login) {
			return true;
		}
		else return false;
	}

};

#endif // LIBSIM_LIBRARY_H
