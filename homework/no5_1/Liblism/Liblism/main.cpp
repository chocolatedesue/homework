#include"bits/stdc++.h"
#include"Library.h"
#include"cmdline.h"

using namespace std;

Library library;

enum Model {
	ADMIN = 0, READER = 1
};
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




// todo:用枚举替代常量，增加case语句的可读性
enum Choice {
	INSERT = 1,
	DROP,
	QUERY,
	UPDATE,
	//quit = 10,
};




//判断程序是否该退出
bool flag = true;



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




class admin_opt {
public:
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
			cout << "书" << src.name << "已添加成功,id为" << src.id<<endl;
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
		auto get = lower_bound(tar.begin(), tar.end(), book("_",id,1));
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

};


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
		////admin.
		//admin_opt::insert_book({ "x",1,1 });
		while (true) {
			cout << "请选择操作" << "\n"
				<< "1. 增加图书" << "\n"
				<< "2. 删除图书" << "\n"
				<< "3. 查询图书" << "\n"
				<< "4. 修改图书" << "\n";
			int opt;
			scanf("%d", &opt);
			switch (opt)
			{

			case INSERT:
			{
				cout << "请输入要增添的书名和增添的数目" << endl;
				string name; int num;
				cin >> name >> num;
				book temp(name, 1, num);
				admin_opt::insert_book(temp);
				break;
			}
			case DROP:
			{
				cout << "请输入要删除的书的id" << endl;
				int id;
				cin >> id;
				admin_opt::drop_book(id);
			}

			case QUERY: 
			{
				;
			}
			case UPDATE:
			{
				cout << "请输入要变更的书的id和数目" << endl;
				int id, num;
				cin >> id >> num;
				admin_opt::update_book(id, num);

			}

			default:
				break;
			}


		}


	}



	return 0;
}
