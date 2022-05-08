#pragma once

// todo:��ö���������������case���Ŀɶ���
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


// ---------------------------------��ģ��-------------------------------//




//������
Library library;

//��¼����Ϣ
Login login;

class admin_opt {
public:
	void static query_book_by_remain() {
		cout << "ʣ�����" << endl << "id" << "---" << "name" << "---" << "num" << endl;
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
				cout << "���д��飬��ʹ�ø��²���" << endl;
				flag = false;
			}
		}
		if (flag) {
			library.book_num++;
			library.remain_book_list.insert(src);
			cout << "��" << src.name << "����ӳɹ�,idΪ" << src.id << endl;
		}

		return;

	}
	void static drop_book(int id) {
		auto& tar = library.remain_book_list;
		auto get = lower_bound(tar.begin(), tar.end(), book("asd", id, 1));
		if (get != tar.end() && (*get).id == id) {
			string name = (*get).name;
			tar.erase(get);

			cout << "�����ɹ�����ɾ��" << name << endl;
		}
		else cout << "���޴��飬ɾ������" << endl;

	}

	void static update_book(int id, int num) {
		auto& tar = library.remain_book_list;
		auto get = lower_bound(tar.begin(), tar.end(), book("_", id, 1));
		if (get != tar.end() && (*get).id == id) {
			tar.erase(get);
			auto temp = *get;
			if (temp.num + num <= 0) {
				cout << "���´��󣬼���Ƿ񳬳�����Ŀ�ķ�Χ" << endl;
			}
			else {
				temp.num += num;
				tar.insert(temp);
				cout << "���³ɹ�," << temp.name << "���" << num << "��" << endl;
			}
			//cout << "�����ɹ�����ɾ��" << src.name << endl;
		}
		else cout << "���޴��飬�޸Ĵ������" << endl;

	}

	void static insert_reader(int id, string name) {
		auto& tar = library.reader_list;
		tar.insert({ id,name });
		cout << "����" << name << "����ɹ�. idΪ" << id << endl;
	}

	void static drop_reader(int id) {
		auto& tar = library.reader_list;
		auto ans = lower_bound(tar.begin(), tar.end(), reader{ id,"_" });
		if (ans != tar.end()) {
			cout << (*ans).name << "�Ѿ�ɾ��" << endl;
			tar.erase(ans);
			auto book_name = library.id_booklist[id].name;
			library.id_booklist.erase(id);
			library.name_book_id.erase(book_name);
		}
		else {
			cout << "���޴��ˣ���������" << endl;
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
		cout << "ͼ��ܵ�ǰͼ����ĿΪ:" << library.book_num << endl;
		cout << "ͼ��ݹ���Ա����Ϊ:" << library.admin_num << endl;
		cout << "ͼ��ݵ�ǰ�û�����Ϊ" << library.reader_num << endl;

	}

	void static query_book_by_id(int id) {
		if (id > library.book_num) {
			cout << "�����ڴ��飬��������" << endl;
		}
		else {
			auto& tar = library.lent_book;

			if (!tar.count(id)) {
				cout << "����δ���" << endl;
			}
			else {
				auto& res = tar[id];
				cout << "�������Ķ���Ϊ:";
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
			cout << "���޴�����߸���δ�����" << endl;
		}
		else {
			int book_id = tar[name];
			query_book_by_id(book_id);
		}

	}
};



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

		if (mark == -1) {
			cout << "���޴���,��������" << endl;
		}

		else {
			tar.lent_book.erase(mark + tar.lent_book.begin());
			cout << "�ѹ黹ͼ��" << library.id_booklist[id].name << "," << "��idΪ" << id << endl;
			bool flag = true;
			for (auto& item : library.remain_book_list) {

				if (item.id == id) {
					auto temp = item;
					temp.num++;
					//���޷�������Ǳ�ڷ���
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
			cout << "���" << name << "�ɹ�!" << endl;
			//library.lent_book[login.id].push_back(id);

			library.id_reader[login.id].lent_book.push_back(id);
			library.lent_book[id].push_back(login.id);

		}
		else cout << "���޴���" << endl;

	}


	void static query_remain_book() {
		cout << "ʣ�����" << endl << "id" << "---" << "name" << "---" << "num" << endl;
		for (auto& item : library.remain_book_list) {
			cout << item.id << " " << item.name << " " << item.num << endl;

		}
	}

	void static query_borrowed_book() {
		cout << "���Ľ���ͼ���idΪ:" << endl;
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


void admin_loop();

void reader_loop();

Model commandline_parse(int argc, char* argv[], Library& library);

void close_session();
