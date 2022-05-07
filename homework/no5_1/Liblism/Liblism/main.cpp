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
		reader_loop();
	}
	else {
		// admin界面的函数
		//admin opt;
		admin_loop();

	}



	return 0;
}








// ---------------------------------子模块-------------------------------//
class reader_opt {
public:
	void static return_book(int id) {
		auto& tar = library.id_reader[login.id];
		//auto res = lower_bound(tar.lent_book.begin(), tar.lent_book.end(), id);
		//bool flag = true;
		int mark = -1;
		for (int i = 0; i < tar.lent_book.size(); ++i) {
			if (tar.lent_book[i] == id) {
				mark = i;
				break;
			}

		}
		
		if (mark==-1) {
			cout << "查无此书,请检查输入" << endl;
		}

		else {
			tar.lent_book.erase(mark+tar.lent_book.begin());
			cout << "已归还图书" << library.id_booklist[id].name << "," << "其id为" << id << endl;
			bool flag = true;
			for (auto& item : library.remain_book_list) {
				
				if (item.id == id) {
					auto temp = item;
					temp.num++;
					//有无法迭代的潜在风险
					library.remain_book_list.erase(item);
					library.remain_book_list.insert(temp);
					remove_relation_book_lent_reader(id);

					flag = false;
					break;
				}
			}
			if (flag) {
				book temp = library.id_booklist[id];
				temp.num = 1;
				library.remain_book_list.insert(temp);
				remove_relation_book_lent_reader(id);
			}
		}


	}

	void static borrow_book(int id) {
		auto& tar = library.remain_book_list;
		auto res = lower_bound(tar.begin(), tar.end(), book{ "_",id ,1 });
		if (res != tar.end()) {
			bool flag = false;
			if ((*res).num != 1) {
				//tar.erase(res);
				flag = true;
			}
			//else (*res).num -= 1;
			string name = (*res).name;
			tar.erase(res);
			if (flag) {
				auto temp = *res;
				temp.num--;
				tar.insert(temp);
			}
			cout << "借出" << name << "成功!" << endl;
			//library.lent_book[login.id].push_back(id);
			
			library.id_reader[login.id].lent_book.push_back(id);
			library.lent_book[id].push_back(login.id);

		}
		else cout << "查无此书" << endl;

	}


	void static query_remain_book() {
		cout << "剩余的书" << endl << "id" << "---" << "name" << "---" << "num" << endl;
		for (auto& item : library.remain_book_list) {
			cout << item.id << " " << item.name << " " << item.num << endl;

		}
	}

	void static query_borrowed_book() {
		cout << "您的借阅图书和id为:" << endl;
		for (auto item : library.id_reader[login.id].lent_book) {
			cout << library.id_booklist[item].name << " " << library.id_booklist[item].id << endl;
		}
	}

private:
	void static remove_relation_book_lent_reader(int id) {
		auto& relation = library.lent_book[id];
		for (int i = 0; i < relation.size(); ++i) {
			if (relation[i] == login.id) {
				relation.erase(relation.begin() + i);
				break;
			}
		}
	}
};


class admin_opt {
public:
	void static query_book_by_remain() {
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
			library.book_num++;
			library.remain_book_list.insert(src);
			cout << "书" << src.name << "已添加成功,id为" << src.id << endl;
		}

		return;

	}
	void static drop_book(int id) {
		auto& tar = library.remain_book_list;
		auto get = lower_bound(tar.begin(), tar.end(), book("asd", id, 1));
		if (get != tar.end() && (*get).id == id) {
			string name = (*get).name;
			tar.erase(get);

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
		cout << "读者" << name << "插入成功. id为" << id << endl;
	}

	void static drop_reader(int id) {
		auto& tar = library.reader_list;
		auto ans = lower_bound(tar.begin(), tar.end(), reader{ id,"_" });
		if (ans != tar.end()) {
			cout << (*ans).name << "已经删除" << endl;
			tar.erase(ans);
			auto book_name = library.id_booklist[id].name;
			library.id_booklist.erase(id);
			library.name_book_id.erase(book_name);
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
	void static query_whole() {
		cout << "图书管当前图书数目为:" << library.book_num << endl;
		cout << "图书馆管理员人数为:" << library.admin_num << endl;
		cout << "图书馆当前用户人数为" << library.reader_num << endl;

	}

	void static query_book_by_id(int id) {
		if (id > library.book_num) {
			cout << "不存在此书，请检查输入" << endl;
		}
		else {
			auto& tar = library.lent_book;
			
			if (!tar.count(id)) {
				cout << "此书未借出" << endl;
			}
			else {
				auto& res = tar[id];
				cout << "该书借给的读者为:";
				for (int idx : (res)) {
					auto& get = library.id_reader[idx];
					cout << " " << get.name;
				}
				cout << endl;
			}
		}
	}
	void static query_book_by_name(string name) {
		auto& tar = library.name_book_id;
		if (!tar.count(name)) {
			cout << "查无此书或者该书未被借出" << endl;
		}
		else {
			int book_id = tar[name];
			query_book_by_id(book_id);
		}

	}
};


void admin_loop()
{

	while (true) {
		cout << "\n" << "*********************" << "\n";
		cout << "请选择操作" << "\n"
			<< "1. 插入图书" << "\n"
			<< "2. 删除图书" << "\n"
			<< "3. 查询未借出图书" << "\n"
			<<"4. 用id查询已借出图书"<<"\n"
			<<"5. 用名字查询已借出图书"<<'\n'
			<< "6. 修改图书" << "\n"
			<< "7. 增加读者" << "\n"
			<< "8. 删除读者" << "\n"
			<< "9. 查询读者" << "\n"
			<< "10. 查询图书馆整体情况" << "\n"
			<< "11. 退出程序" << endl;
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
		_sleep(1000);
		cout << "\n" << "*********************" << "\n";
	}

}

void reader_loop()
{
	//处理用户界面的函数
	while (true) {
		cout << "\n" << "*********************" << "\n";
		cout << "1. 借书" << "\n"
			<< "2. 还书" << "\n"
			<< "3. 查询可借书籍" << '\n'
			<< "4. 查询已借图书" << '\n'
		<< "5. 结束程序" << endl;
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
		_sleep(1000);
		cout << "\n" << "*********************" << "\n";
	}

}
//将数据序列化
//todo: 修正
void close_session() {

	FILE* fp = fopen(R"(./data/admin_table.csv)", "w");
	//fputs("sad", fp);
	if (fp)
	{
		for (auto& item : library.admin_list) {
			string res = to_string(item.id) + "," + item.name + "," + item.passwd+"\n";
			//cout <<res<<" "<< res.c_str() << endl;
			fputs(res.c_str(), fp);
		}
	}
	fclose(fp);

	fp = fopen(R"(./data/reader_table.csv)", "w");
	if (fp) {
		for (auto& item : library.reader_list) {
			string res = to_string(item.id) + "," + item.name+"\n";
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
				string res = to_string(Reader.id) + "," + to_string(t_book.id) + "," + t_book.name+"\n";
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
			string res = to_string(item.id) + "," + item.name + "," + to_string(item.num)+"\n";
			fputs(res.c_str(), fp);
		}

	}
	fclose(fp);



	fp = fopen(R"(./data/config.csv)", "w");
	if (fp) {

		string res = to_string(library.book_num) + "," + to_string(library.admin_num) + "," + to_string(library.reader_num)+"\n";

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