#include <iostream>
#include <fstream>
#include<cstring>

using namespace std;
const int buffer_size = 1 << 10;
const int compact_size = 3;


class zip_tool {

public:

    void init_buffer(unsigned char *&in_buffer, unsigned char *&out_buffer) {
        in_buffer = new unsigned char[Size];
        out_buffer = new unsigned char[Size];
        memset(in_buffer,0, Size);
        memset(out_buffer,0,Size);
    }

    void release_buffer(unsigned char *&in_buffer, unsigned char *&out_buffer) {
        delete[] in_buffer;
        delete[] out_buffer;
        in_buffer = nullptr;
        out_buffer = nullptr;
    }

    int encode(unsigned char *in_buffer,int srcLeft, unsigned char *out_buffer) {
//        int srcLeft = strlen(reinterpret_cast<const char *>(in_buffer));
        int encSize = 0;
        while (srcLeft > 0) {
            int cnt = 0;
            if (judge_size(in_buffer, srcLeft)) {
                if (encSize + compact_size > buffer_size) {
                    return -1;
                } else {
                    cnt = count_duplicate(in_buffer, srcLeft);
                    // 获取重复字数 并以char保存  取低7位 最多只能压缩2^7-1个字符
                    out_buffer[encSize++] = cnt | 0x80;
                    out_buffer[encSize++] = *in_buffer;
                    in_buffer += cnt;
                    srcLeft -= cnt;
                }

            } else {
                cnt = count_no_duplicate(in_buffer, srcLeft);
                if (encSize + cnt + 1 > buffer_size) {
                    return -1;
                }
                out_buffer[encSize++] = cnt;
                for (int i = 0; i <= cnt; ++i) {
                    out_buffer[encSize++] = *in_buffer;
                    in_buffer++;
                }
                srcLeft -= cnt;
            }

        }
        return encSize;
    }

    int decode(unsigned char *in_buffer,int src_size, unsigned char *out_buffer) {
        int decSize = 0;
//        int src_size = strlen((char *) in_buffer);


        while (decSize < src_size) {
            unsigned char sign = *in_buffer;
            in_buffer++;
            //获取低7位
            int cnt = sign & 0x7f;
            if (decSize + cnt > buffer_size) {
                return -1;
            }
            //对应压缩数据
            if ((sign & 0x80) == 0x80) {
                for (int i = 0; i <= cnt; ++i) {
                    out_buffer[decSize++] = *in_buffer;
                }
                in_buffer++;
            } else {
                for (int i = 0; i <= cnt; ++i) {
                    out_buffer[decSize++] = *in_buffer;
                    in_buffer++;
                }
            }
        }
        return decSize;
    };

private:
    int Size = buffer_size;

    bool judge_size(unsigned char *src, int srcLeft) {
        if (srcLeft < compact_size) {
            return false;
        }
        for (int i = 1; i < compact_size; ++i) {
            if (*src != *(src + 1)) {
                return false;
            }
            src++;
        }
        return true;

    }

    int count_duplicate(unsigned char *src, int srcLeft) {
            int repeated = *src;
            int length = 1;
            while (length<srcLeft && length<0x7f && src[length]==repeated){
                length++;
            }
            return length;
    }

    int count_no_duplicate(unsigned char *src, int srcLeft) {
        if (srcLeft<3){
            return srcLeft;
        }
        int pre = src[0],now = src[1],length = 2;
        while (length<srcLeft && length<0x7f && (pre!=now || now !=src[length])){
            pre = now;
            now = src[length];
            length++;
        }
        return length;

    }
};


int main(int argc, char **argv) {
    zip_tool zip;
    ifstream input;
    ofstream output;
    unsigned char *in_buffer;
    unsigned char *out_buffer;


    zip.init_buffer(in_buffer, out_buffer);

    try {
        if (argc == 4) {
            input = ifstream(argv[1], ios::in);
            // ios::trunc 如果文件已存在则先删除该文件
            output = ofstream(argv[3], ios::out  | ios::trunc);

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
    input.read((char *) in_buffer, buffer_size);
//    cout << strlen(reinterpret_cast<const char *>(in_buffer)) << endl;
    int in_buffer_size = strlen(reinterpret_cast<const char *>(in_buffer))-1;
    char opt = argv[2][1];
    int res = 0;
    if (opt == 'c') {
        res = zip.encode(in_buffer,in_buffer_size, out_buffer);
    } else {
        res = zip.decode(in_buffer, in_buffer_size,out_buffer);
    }

    if (res == -1) {
        cout << "文件过大，缓冲区溢出" << endl;
    } else {
        cout << "执行完毕,请查看文件" << argv[3] << endl;
    }

    output.write((char*)out_buffer,res);
    zip.release_buffer(in_buffer, out_buffer);
    return 0;
}


