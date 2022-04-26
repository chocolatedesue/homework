#include <iostream>
#include <fstream>
#include "sstream"

using namespace std;
const int MAXN = 1 << 10;

int flag = 0;
unsigned char in_buffer[MAXN];
unsigned char out_buffer[MAXN];

int decode();

int encode();

int main(int argc, char **argv) {

    ifstream input;
    ofstream output;

    try {
        if (argc == 4) {
            input = ifstream(argv[1], ios::in | ios::binary);
            // ios::trunc 如果文件已存在则先删除该文件
            output = ofstream(argv[3], ios::out | ios::binary | ios::trunc);

            if (!input.is_open() || !output.is_open()) {
                throw ("文件打开失败,请检查第一个文件是否存在");
            }
        } else {
            throw ("参数数量不对，请检查参数");
        }
    }
    catch (const char *&msg) {
        cout << msg << endl;
        return -1;
    }
    input.read((char *) in_buffer, MAXN);

    char opt = argv[2][1];
    int res = 0;
    if (opt == 'c') {
        res = encode();
    } else {
        res = decode();
    }

    if (res == -1) {
        cout << "文件过大，缓冲区溢出" << endl;
    }

    else{
        cout<<"执行完毕,请查看文件"<<argv[3]<<endl;
    }

    return 0;
}

int encode(){


}

int decode(){

};