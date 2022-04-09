#include<bits/stdc++.h>
using namespace  std;

//高精运算只好处理正数运算, 将符号位额外处理
//对于+-法，将符号位和数值为分开，转化为绝对值运算
//string为载体存储 1234-》“1234”


string Minusbigdata(const string& a,const string& b){
    if (a.size()<b.size()){
        return Minusbigdata(b,a);
    }
    else{
        if (a.size()==b.size() && a<b)
            return Minusbigdata(b,a);
        string res;
        int t = 0;//t用来表示减法的借位
        for (int i=a.size()-1, j = b.size()-1;i>=0;--i,--j){
            t =a[i]-'0'-t;
            if (j>=0)t-=b[j]-'0';
            res.push_back((t+10)%10+'0');
            if (t<0)t=1;
            else t=0;
        }
        while (res.size()>1 && res.back()=='0')res.pop_back();
        reverse(res.begin(),res.end());
//            reverse_copy()
        return res;


    }

}

string Addbigdata(const string &a, const string &b){
    if (a.size()<b.size())return Addbigdata(b,a);
    string res ;
    int t = 0;
    int i = a.size()-1,j = b.size()-1;
    for (;i>=0;--i,--j){
        t += a[i]-'0';
        //error 1
        if (j>=0)t+=b[j]-'0';
        res.push_back((t%10+'0'));
        t = t/10;
    }
    //判断首位是否进位
    if (t){
        res.push_back(t+'0');
    }

    reverse(res.begin(),res.end());
    return res;
}

//判断运算结果是否为负数，如果是返回true,否则为false;
bool my_cmp(const string& a,const string& b,bool& flag) {

    if (a[0]=='+' && b[0]=='+')return false;
    else if (a[0]=='-' && b[0]=='-')return true;
    else if (b[0]=='-'){
        return my_cmp(b,a,flag);
    }
    else {
        flag = true;
        if (a.size()>b.size()){
            return true;
        }
        else if (a.size()<b.size()){
            return false;
        }
        else {
            //利用字符串同长度下比较规则与整数比较一致的便利
            return a.substr(1)>=b.substr(1);
        }
    }


}


void input_handler(string &a, string &b, bool &sym, bool &judge) {
    cout << "请输入两个正整数和标识符（除2以外为加法，2为减法，以空格间隔）" << endl;
    string x, y;
    int flag;
    cin >> x >> y >> flag ;
    if (flag==2){
        if (y[0]=='-'){
            y = y.substr(1);
        }
        else {
            y = "-"+y;
        }
    }
    //补填充位

    if (x[0]!='-'){
        x = "+"+x;
    }
    if (y[0]!='-'){
        y = "+"+y;
    }

    if (my_cmp(x,y,judge)){
        sym = true;
    }
    a = x.substr(1),b= y.substr(1);
}





int main() {
    string a,b;
    //控制符号位输出
    bool sym= false;
    //判断绝对值是做差还是相加
    bool judge= false;

    input_handler(a, b, sym, judge);
    string res;
    if (judge)
        res = Minusbigdata(a,b);
    else
        res = Addbigdata(a,b);
    string opt;
    if (res!="0")
        if (sym)
            opt='-';
    cout<<"结果为"<<opt<<res<<endl;
}
