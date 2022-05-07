#pragma once

// todo:用枚举替代常量，增加case语句的可读性
enum Choice_admin {
	
	INSERT_BOOK = 1,
	DROP_BOOK,
	QUERY_BOOK_BY_REMAIN,
	QUERY_BOOK_BY_ID,
	QUERY_BOOK_BY_NAME,
	UPDATE_BOOK,
	//QUIT_ADMIN
	INSERT_USER,
	DROP_USER,
	QUERY_USER,
	//quit = 10,
	QUERY_WHOLE_INFO,
	QUIT_ADMIN,
};


enum Choice_reader {
	BORROW_BOOK=1,
	RETURN_BOOK ,
	QUERY_REMAIN_BOOK,
	
	QUERY_BORROWED_BOOK,
	QUIT_USER
};

enum Model {
	ADMIN = 0, READER = 1
};

void close_session();

Model commandline_parse(int argc, char* argv[], Library& library);

void admin_loop();

void reader_loop();

