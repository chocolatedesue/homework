#include"bits/stdc++.h"
#include"Library.h"
using namespace std;

#define _VSSTUDIO

int main(int argc, char* argv[]) {
	//启动类加载资源
	Library library;

	//处理命令行参数 判断用户
	#ifndef _VSSTUDIO
		cmdline::parser parser;
		parser.add<string>("type", 't', "the type of user，one of {admin,reader}", true, "", cmdline::oneof<string>("admin", "reader"));
		parser.add<string>("passwd", 'p', "the passwd of admin", false, "");
		parser.parse_check(argc, argv);
	#endif // !_VSSTUDIO


	while (true) {
		//todo: 提示性输出  获取输入 判断步骤

		break;
	}

	return 0;
}
