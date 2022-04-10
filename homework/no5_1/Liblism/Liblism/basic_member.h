#pragma once
//
// Created by choco on 10/4/2022.
//

#ifndef LIBSIM_BASIC_MEMBER_H
#define LIBSIM_BASIC_MEMBER_H

#pragma once
#include "bits/stdc++.h"
//using namespace std;


class reader {

public:
    const std::string& getName() const {
        return name;
    }

    void setName(const std::string& name) {
        reader::name = name;
    }

    int getId() const {
        return id;
    }

    void setId(int id) {
        reader::id = id;
    }

private:
    int id;
public:
    reader(int id, const std::string& name) : id(id), name(name) {}

private:
    std::string name;
public:

    reader() {}
};


class book {
public:
    const std::string& getName() const {
        return name;
    }

    void setName(const std::string& name) {
        book::name = name;
    }

    int getId() const {
        return id;
    }

    void setId(int id) {
        book::id = id;
    }

    int getNum() const {
        return num;
    }

    void setNum(int num) {
        book::num = num;
    }

private:
    std::string name;
    //书的编号和书的数目
    int id, num;
public:
    book(const std::string& name, int id, int num) : name(name), id(id), num(num) {}
    book() {}
};


//拓展用,admin_group
class admin {


private:
    int id;
public:
    admin(int id, const std::string& name, const std::string& passwd) : id(id), name(name), passwd(passwd) {}
    admin() {}
private:
    std::string name;
    std::string passwd;

};



#endif //LIBSIM_BASIC_MEMBER_H
