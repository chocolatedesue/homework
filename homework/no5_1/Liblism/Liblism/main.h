#pragma once

// todo:用枚举替代常量，增加case语句的可读性
enum Choice_admin {
	INSERT = 1,
	DROP,
	QUERY,
	UPDATE,
	//QUIT
	INSERTUSER,
	DROPUSER,
	QUERYUSER,
	//quit = 10,


	QUIT,
};

enum Model {
	ADMIN = 0, READER = 1
};

void close_session();

Model commandline_parse(int argc, char* argv[], Library& library);

void admin_loop();

