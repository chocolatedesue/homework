#include"bits/stdc++.h"
#include"Library.h"
#include"cmdline.h"
#include "main.h"


using namespace std;


//程序主循环参考函数
//while (true) {
//	//todo: 提示性输出  获取输入 判断步骤
//	switch (1)
//	{
//	case quit:
//		cout << "程序结束" << endl;
//		flag = false;
//	}
//	if (!flag)break;
//}



//#define _DEVELOP  // 如果不用命令行参数检测，请注释掉该行









//判断程序是否该退出
bool flag = true;


int main(int argc, char* argv[]) {


#ifndef _DEVELOP
	Model model = commandline_parse(argc, argv, library);
#endif // _DEVELOP


	//登录对象是login
	if (model == READER) {
		reader_loop();
	}
	else {
		// admin界面的函数
		//admin opt;
		admin_loop();

	}



	return 0;
}







inline void admin_loop()
{

	while (true) {
		cout << "\n" << "*********************" << "\n";
		cout << "请选择操作" << "\n"
			<< "1. 插入图书" << "\n"
			<< "2. 删除图书" << "\n"
			<< "3. 查询未借出图书" << "\n"
			<< "4. 用id查询已借出图书" << "\n"
			<< "5. 用名字查询已借出图书" << '\n'
			<< "6. 修改图书" << "\n"
			<< "7. 增加读者" << "\n"
			<< "8. 删除读者" << "\n"
			<< "9. 查询读者" << "\n"
			<< "10. 查询图书馆整体情况" << "\n"
			<< "11. 保存操作结果，并退出" << endl;
		int opt;
		scanf("%d", &opt);
		switch (opt)
		{

		case INSERT_BOOK:
		{
			cout << "请输入要增添的书名和增添的数目" << endl;
			string name; int num;
			cin >> name >> num;
			//library.book_num++;

			book temp(name, library.book_num + 1, num);
			admin_opt::insert_book(temp);
			break;
		}
		case DROP_BOOK:
		{
			cout << "请输入要删除的书的id" << endl;
			int id;
			cin >> id;
			admin_opt::drop_book(id);
			break;
		}

		case QUERY_BOOK_BY_REMAIN:
		{
			admin_opt::query_book_by_remain();
			break;
		}

		case QUERY_BOOK_BY_ID:
		{
			cout << "请输入待查询的书的id" << endl;
			int id;
			cin >> id;
			admin_opt::query_book_by_id(id);
			break;
		}

		case QUERY_BOOK_BY_NAME:
		{
			cout << "请输入待查询的书的名字" << endl;
			string name;
			cin >> name;
			admin_opt::query_book_by_name(name);
			break;
		}

		case UPDATE_BOOK:
		{
			cout << "请输入要变更的书的id和数目" << endl;
			int id, num;
			cin >> id >> num;
			admin_opt::update_book(id, num);
			break;
		}

		case INSERT_USER:
		{
			cout << "请输入要插入的用户名" << endl;
			string name;
			cin >> name;
			library.reader_num++;
			admin_opt::insert_reader(library.reader_num, name);
			break;
		}
		case DROP_USER:
		{
			int id;
			cout << "请输入要删除的的用户id" << endl;
			cin >> id;
			admin_opt::drop_reader(id);
			break;
		}

		case QUERY_USER:
		{
			admin_opt::query_user();
			break;
		}
		case QUERY_WHOLE_INFO:
		{
			admin_opt::query_whole();
			break;

		}
		case QUIT_ADMIN:
		{
			close_session();
			cout << "应用结束" << endl;
			exit(0);
		}
		default:
			cout << "输入序数错误，请重新输入" << endl;
			break;
		}
		system("timeout /nobreak /t 2 ");
		cout << "\n" << "*********************" << "\n";
	}

}

inline void reader_loop()
{
	//处理用户界面的函数
	while (true) {
		cout << "\n" << "*********************" << "\n";
		cout << "1. 借书" << "\n"
			<< "2. 还书" << "\n"
			<< "3. 查询可借书籍" << '\n'
			<< "4. 查询已借图书" << '\n'
			<< "5. 保存操作结果，并退出" << endl;
		int opt;
		cin >> opt;
		switch (opt)
		{
		case BORROW_BOOK:
		{
			cout << "请输入要借图书的id:" << endl;
			int id;
			cin >> id;
			reader_opt::borrow_book(id);
			break;
		}

		case RETURN_BOOK:
		{
			cout << "要归还图书id:" << endl;
			int id;
			cin >> id;
			reader_opt::return_book(id);
			break;
		}
		case QUERY_REMAIN_BOOK:
		{

			reader_opt::query_remain_book();
			break;
		}
		case QUERY_BORROWED_BOOK:
		{
			reader_opt::query_borrowed_book();
			break;
		}
		case QUIT_USER:
		{
			cout << "程序结束" << endl;
			close_session();
			exit(0);
		}
		default:
			cout << "输入序数错误，请重新输入" << endl;
			break;
		}
		system("timeout /nobreak /t 2");
		cout << "\n" << "*********************" << "\n";
	}

}

// 判断输入命令合法性
Model commandline_parse(int argc, char* argv[], Library& library)
{

	//处理命令行参数 判断用户
	cmdline::parser parser;
	parser.add<string>("type", 't', "the type of user，one of {Admin,Reader}", true, "", cmdline::oneof<string>("Admin", "Reader"));
	parser.add<string>("name", 'n', "your name", true);
	parser.add<int>("id", 'i', "your id", true);
	parser.add<string>("passwd", 'p', "the passwd of admin if login as admin", false, "");
	parser.parse_check(argc, argv);



	cout << "----------------------------" << endl;
	string type = parser.get<string>("type"), name = parser.get<string>("name"), passwd = parser.get<string>("passwd");
	int id = parser.get<int>("id");
	login.name = name;
	login.id = id;

	Model model;

	if (type == "Admin") {
		model = ADMIN;
		if (library.check_valid_admin(id, name, passwd)) {
			cout << "欢迎管理员" << name << "登录" << endl;
		}
		else {
			cout << "信息错误，请检查信息" << endl;
			exit(0);
		}
	}
	else {
		model = READER;
		if (library.check_valid_reader(id, name))
		{
			cout << "欢迎读者" << name << "登录" << endl;
		}
		else {
			cout << "信息错误，请检查信息" << endl;
			exit(0);
		}

	}



	return model;
}

//将数据序列化
void close_session() {

	FILE* fp = fopen(R"(./data/admin_table.csv)", "w");
	//fputs("sad", fp);
	if (fp)
	{
		for (auto& item : library.admin_list) {
			string res = to_string(item.id) + "," + item.name + "," + item.passwd + "\n";
			//cout <<res<<" "<< res.c_str() << endl;
			fputs(res.c_str(), fp);
		}
	}
	fclose(fp);

	fp = fopen(R"(./data/reader_table.csv)", "w");
	if (fp) {
		for (auto& item : library.reader_list) {
			string res = to_string(item.id) + "," + item.name + "\n";
			fputs(res.c_str(), fp);
		}
	}
	fclose(fp);

	fp = fopen(R"(./data/info_table.csv)", "w");
	if (fp) {
		for (auto& item : library.id_reader) {
			const auto& Reader = item.second;
			for (auto& id : Reader.lent_book) {
				const auto& t_book = library.id_booklist[id];
				string res = to_string(Reader.id) + "," + to_string(t_book.id) + "," + t_book.name + "\n";
				fputs(res.c_str(), fp);
			}
			//book b1 = library.id_booklist[item.first];
			///*reader r1 = library*/
			//reader r1 = library.id_reader[item.first];

			//string res = to_string(r1.id) + "," + r1.name + "," + to_string(b1.id) + "," + b1.name + ",";
			//fputs(res.c_str(), fp);

		}

	}

	fclose(fp);

	fp = fopen(R"(./data/remain_book_table.csv)", "w");
	if (fp) {
		for (auto& item : library.remain_book_list) {
			string res = to_string(item.id) + "," + item.name + "," + to_string(item.num) + "\n";
			fputs(res.c_str(), fp);
		}

	}
	fclose(fp);



	fp = fopen(R"(./data/config.csv)", "w");
	if (fp) {

		string res = to_string(library.book_num) + "," + to_string(library.admin_num) + "," + to_string(library.reader_num) + "\n";

		fputs(res.c_str(), fp);

	}
	fclose(fp);
}




