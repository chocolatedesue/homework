#include"bits/stdc++.h"
#include"Library.h"
#include"cmdline.h"
#include "main.h"

using namespace std;

Library library;

//登录者信息
Login login;

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
		//处理用户界面的函数
		;
	}
	else {
		// admin界面的函数
		//admin opt;
		admin_loop();

	}



	return 0;
}






// ---------------------------------子模块-------------------------------//


class admin_opt {
public:
	void static query_book() {
		cout << "剩余的书" << endl << "id" << "---" << "name" << "---" << "num" << endl;
		for (auto& item : library.remain_book_list) {
			cout << item.id << " " << item.name << " " << item.num << endl;

		}

	}


	void static insert_book(const book& src) {
		//auto& tar = library.remain_book_list;
		//auto get = lower_bound(tar.begin(), tar.end(), book("asd", src, 1));
		bool flag = true;
		for (auto& item : library.remain_book_list) {
			if (item.name == src.name) {
				/*auto temp = item;
				temp.num++;
				library.remain_book_list.erase(item);
				library.remain_book_list.insert(temp);
				flag = false;*/
				cout << "已有此书，请使用更新操作" << endl;
				flag = false;
			}
		}
		if (flag) {
			library.remain_book_list.insert(src);
			cout << "书" << src.name << "已添加成功,id为" << src.id << endl;
		}

		return;

	}
	void static drop_book(int id) {
		auto& tar = library.remain_book_list;
		auto get = lower_bound(tar.begin(), tar.end(), book("asd", id, 1));
		if (get != tar.end() && (*get).id == id) {
			tar.erase(get);
			string name = (*get).name;
			cout << "操作成功，已删除" << name << endl;
		}
		else cout << "查无此书，删除错误" << endl;

	}

	void static update_book(int id, int num) {
		auto& tar = library.remain_book_list;
		auto get = lower_bound(tar.begin(), tar.end(), book("_", id, 1));
		if (get != tar.end() && (*get).id == id) {
			tar.erase(get);
			auto temp = *get;
			if (temp.num + num <= 0) {
				cout << "更新错误，检查是否超出书数目的范围" << endl;
			}
			else {
				temp.num += num;
				tar.insert(temp);
				cout << "更新成功," << temp.name << "变更" << num << "本" << endl;
			}
			//cout << "操作成功，已删除" << src.name << endl;
		}
		else cout << "查无此书，修改错误错误" << endl;

	}

	void static insert_reader(int id, string name) {
		auto& tar = library.reader_list;
		tar.insert({ id,name });
	}

	void static drop_reader(int id) {
		auto& tar = library.reader_list;
		auto ans = lower_bound(tar.begin(), tar.end(), reader{ id,"_" });
		if (ans != tar.end()) {
			cout << (*ans).name << "已经删除" << endl;
		}
		else {
			cout << "查无此人，请检查输入" << endl;
		}
	}

	void static query_user() {
		auto& tar = library.reader_list;
		cout << "id---" << "name" << endl;
		for (auto item : tar) {
			cout << item.id << " " << item.name << endl;
		}

	}

};


void admin_loop()
{

	while (true) {
		cout << "请选择操作" << "\n"
			<< "1. 增加图书" << "\n"
			<< "2. 删除图书" << "\n"
			<< "3. 查询图书" << "\n"
			<< "4. 修改图书" << "\n"
			<< "5. 增加读者" << "\n"
			<< "6. 删除读者" << "\n"
			<< "7. 查询读者" << "\n"
		<< "8. 退出程序" << endl;
		int opt;
		scanf("%d", &opt);
		switch (opt)
		{

		case INSERT:
		{
			cout << "请输入要增添的书名和增添的数目" << endl;
			string name; int num;
			cin >> name >> num;
			library.admin_num++;
			book temp(name, library.admin_num, num);
			admin_opt::insert_book(temp);
			break;
		}
		case DROP:
		{
			cout << "请输入要删除的书的id" << endl;
			int id;
			cin >> id;
			admin_opt::drop_book(id);
			break;
		}

		case QUERY:
		{
			admin_opt::query_book();
			break;
		}
		case UPDATE:
		{
			cout << "请输入要变更的书的id和数目" << endl;
			int id, num;
			cin >> id >> num;
			admin_opt::update_book(id, num);
			break;
		}

		case INSERTUSER:
		{
			cout << "请输入要插入的用户名" << endl;
			string name;
			cin >> name;
			library.reader_num++;
			admin_opt::insert_reader(library.reader_num, name);
			break;
		}
		case DROPUSER:
		{
			int id;
			cout << "请输入要删除的的用户id" << endl;
			cin >> id;
			admin_opt::drop_reader(id);
			break;
		}

		case QUERYUSER:
		{
			admin_opt::query_user();
			break;
		}

		case QUIT:
		{
			close_session();
			cout << "应用结束" << endl;
			exit(0);
		}
		default:
			break;
		}


	}

}

//将数据序列化
void close_session() {

	FILE* fp = fopen(R"(./data/admin_table.csv)", "w");
	//fputs("sad", fp);
	if (fp)
	{
		for (auto& item : library.admin_list) {
			string res = to_string(item.id) + "," + item.name + "," + item.passwd;
			//cout <<res<<" "<< res.c_str() << endl;
			fputs(res.c_str(), fp);
		}
	}
	fclose(fp);

	fp = fopen(R"(./data/reader_table.csv)", "w");
	if (fp) {
		for (auto& item : library.reader_list) {
			string res = to_string(item.id) + "," + item.name;
			fputs(res.c_str(), fp);
		}
	}
	fclose(fp);

	fp = fopen(R"(./data/info_table.csv)", "w");
	if (fp) {
		for (auto& item : library.lent_book) {
			book b1 = library.id_booklist[item.first];
			/*reader r1 = library*/
			reader r1 = library.id_reader[item.second];

			string res = to_string(r1.id) + "," + r1.name + "," + to_string(b1.id) + "," + b1.name + ",";
			fputs(res.c_str(), fp);

		}

	}

	fclose(fp);

	fp = fopen(R"(./data/remain_book_table.csv)", "w");
	if (fp) {
		for (auto& item : library.remain_book_list) {
			string res = to_string(item.id) + "," + item.name + "," + to_string(item.num);
			fputs(res.c_str(), fp);
		}

	}
	fclose(fp);



	fp = fopen(R"(./data/config.txt)", "w");
	if (fp) {
		
		string res = to_string(library.book_num) + " " + to_string(library.admin_num) + " " + to_string(library.reader_num);
		
		fputs(res.c_str(), fp);

	}
	fclose(fp);
}


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