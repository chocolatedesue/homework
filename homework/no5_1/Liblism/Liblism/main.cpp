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




// todo:用枚举替代常量，增加case语句的可读性
enum Choice {
	quit = 10,
};

enum Model {
	admin = 0, reader = 1
};



//判断程序是否该退出
bool flag = true;




int main(int argc, char* argv[]) {


#ifndef _DEVELOP
	Model model = commandline_parse(argc, argv);
#endif // _DEVELOP

	
	if (model == reader) {
		//处理用户界面的函数
		;
	}
	else {
		// 1. 判断管理密码正确的函数  2. admin界面的函数

		
	}



	return 0;
}

Model commandline_parse(int argc, char* argv[])
{

	//处理命令行参数 判断用户
	cmdline::parser parser;
	parser.add<string>("type", 't', "the type of user，one of {admin,reader}", true, "", cmdline::oneof<string>("admin", "reader"));
	parser.add<string>("passwd", 'p', "the passwd of admin", false, "");
	parser.parse_check(argc, argv);


	//启动类加载资源
	Library library;

	string type = parser.get<string>("type"), passwd = parser.get<string>("passwd");
	Model model;
	if (type == "admin") {
		model = admin;
	}
	else model = reader;


	return model;
}
