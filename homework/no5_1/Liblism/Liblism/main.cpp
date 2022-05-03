#include"bits/stdc++.h"
#include"Library.h"
#include"cmdline.h"

using namespace std;

Library library;

enum Model {
	ADMIN = 0, READER = 1
};
//��¼����Ϣ
Login login;

//������ѭ���ο�����
//while (true) {
//	//todo: ��ʾ�����  ��ȡ���� �жϲ���
//	switch (1)
//	{
//	case quit:
//		cout << "�������" << endl;
//		flag = false;
//	}
//	if (!flag)break;
//}



//#define _DEVELOP  // ������������в�����⣬��ע�͵�����




// todo:��ö���������������case���Ŀɶ���
enum Choice {
	INSERT = 1,
	DROP,
	QUERY,
	UPDATE,
	//quit = 10,
};




//�жϳ����Ƿ���˳�
bool flag = true;



Model commandline_parse(int argc, char* argv[], Library& library)
{

	//���������в��� �ж��û�
	cmdline::parser parser;
	parser.add<string>("type", 't', "the type of user��one of {Admin,Reader}", true, "", cmdline::oneof<string>("Admin", "Reader"));
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
			cout << "��ӭ����Ա" << name << "��¼" << endl;
		}
		else {
			cout << "��Ϣ����������Ϣ" << endl;
			exit(0);
		}
	}
	else {
		model = READER;
		if (library.check_valid_reader(id, name))
		{
			cout << "��ӭ����" << name << "��¼" << endl;
		}
		else {
			cout << "��Ϣ����������Ϣ" << endl;
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
				cout << "���д��飬��ʹ�ø��²���" << endl;
				flag = false;
			}
		}
		if (flag) {
			library.remain_book_list.insert(src);
			cout << "��" << src.name << "�����ӳɹ�,idΪ" << src.id<<endl;
		}

		return;

	}
	void static drop_book(int id) {
		auto& tar = library.remain_book_list;
		auto get = lower_bound(tar.begin(), tar.end(), book("asd", id, 1));
		if (get != tar.end() && (*get).id == id) {
			tar.erase(get);
			string name = (*get).name;
			cout << "�����ɹ�����ɾ��" << name << endl;
		}
		else cout << "���޴��飬ɾ������" << endl;

	}

	void static update_book(int id, int num) {
		auto& tar = library.remain_book_list;
		auto get = lower_bound(tar.begin(), tar.end(), book("_",id,1));
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

};


int main(int argc, char* argv[]) {


#ifndef _DEVELOP
	Model model = commandline_parse(argc, argv, library);
#endif // _DEVELOP


	//��¼������login
	if (model == READER) {
		//�����û�����ĺ���
		;
	}
	else {
		// admin����ĺ���
		//admin opt;
		////admin.
		//admin_opt::insert_book({ "x",1,1 });
		while (true) {
			cout << "��ѡ�����" << "\n"
				<< "1. ����ͼ��" << "\n"
				<< "2. ɾ��ͼ��" << "\n"
				<< "3. ��ѯͼ��" << "\n"
				<< "4. �޸�ͼ��" << "\n";
			int opt;
			scanf("%d", &opt);
			switch (opt)
			{

			case INSERT:
			{
				cout << "������Ҫ��������������������Ŀ" << endl;
				string name; int num;
				cin >> name >> num;
				book temp(name, 1, num);
				admin_opt::insert_book(temp);
				break;
			}
			case DROP:
			{
				cout << "������Ҫɾ�������id" << endl;
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
				cout << "������Ҫ��������id����Ŀ" << endl;
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
