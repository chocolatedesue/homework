#pragma once
//
// Created by choco on 10/4/2022.
//

#ifndef LIBSIM_BASIC_MEMBER_H
#define LIBSIM_BASIC_MEMBER_H

#pragma once
#include "bits/stdc++.h"
using namespace std;




class reader {
public:
	reader(int id, const std::string& name) : id(id), name(name) {}
	reader() {}
	std::string name;
	int id;
	bool operator==(reader temp)const {
		return temp.id == id && temp.name == name;
	}
	bool operator<(reader temp) const {
		return id < temp.id;
	}



};


class book {
public:
	std::string name;
	//书的编号和书的数目
	int id, num;


public:
	bool operator < (const book& temp)const {
		return id < temp.id;
	}
	book(const std::string& name, int id, int num) : name(name), id(id), num(num) {}
	book() {}
};


//拓展用,admin_group
class admin {


public:
	int id;
	std::string name;
	std::string passwd;

	//set<admin>admin_list;

public:
	bool operator<(const admin& temp)const {
		return id < temp.id;
	}
	bool operator==(admin temp)const {
		return temp.id == id && temp.name == name && temp.passwd == temp.passwd;

	}
	admin(const int& id, const std::string& name, const std::string& passwd) : id(id), name(name), passwd(passwd) {}
	admin() {}




};

class Login {

public:
	std::string name;
	int id;
	Login() :name(""), id(0) {};
};


#endif //LIBSIM_BASIC_MEMBER_H
