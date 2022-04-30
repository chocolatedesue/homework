#include"bits/stdc++.h"
#include"Library.h"
#include"cmdline.h"

using namespace std;


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
	quit = 10,
};




//判断程序是否该退出
bool flag = true;



Model commandline_parse(int argc, char* argv[], Library& library)
{

	//处理命令行参数 判断用户
	cmdline::parser parser;
	parser.add<string>("type", 't', "the type of user，one of {Admin,Reader}", true, "", cmdline::oneof<string>("Admin", "Reader"));
	parser.add<string>("name", 'n', "your name", true);
	parser.add<int>("id",'i',"your id",true);
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

		cout << "欢迎读者" << name << "登录" << endl;



	}



	return model;
}



int main(int argc, char* argv[]) {
	Library library;

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


	}



	return 0;
}
