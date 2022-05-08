#include <bits/stdc++.h>

using namespace std;

//�߾�����ֻ�ô�����������, ������λ���⴦��
//����+-����������λ����ֵΪ�ֿ���ת��Ϊ����ֵ����
// stringΪ����洢 1234-����1234��
bool state = true;

string Minusbigdata(const string &a, const string &b) {
    if (a.size() < b.size()) {
        return Minusbigdata(b, a);
    } else {
        if (a.size() == b.size() && a < b)
            return Minusbigdata(b, a);
        string res;
        int t = 0; // t������ʾ�����Ľ�λ
        for (int i = a.size() - 1, j = b.size() - 1; i >= 0; --i, --j) {
            t = a[i] - '0' - t;
            if (j >= 0)
                t -= b[j] - '0';
            res.push_back((t + 10) % 10 + '0');
            if (t < 0)
                t = 1;
            else
                t = 0;
        }
        while (res.size() > 1 && res.back() == '0')
            res.pop_back();
        reverse(res.begin(), res.end());
        //            reverse_copy()
        return res;
    }
}

string Addbigdata(const string &a, const string &b) {
    if (a.size() < b.size())
        return Addbigdata(b, a);
    string res;
    int t = 0;
    int i = a.size() - 1, j = b.size() - 1;
    for (; i >= 0; --i, --j) {
        t += a[i] - '0';
        // error 1
        if (j >= 0)
            t += b[j] - '0';
        res.push_back((t % 10 + '0'));
        t = t / 10;
    }
    //�ж���λ�Ƿ��λ
    if (t) {
        res.push_back(t + '0');
    }

    reverse(res.begin(), res.end());
    return res;
}

//�ж��������Ƿ�Ϊ����������Ƿ���true,����Ϊfalse;
bool my_cmp(const string &a, const string &b, bool &flag) {

    if (a[0] == '+' && b[0] == '+')
        return false;
    else if (a[0] == '-' && b[0] == '-')
        return true;
    else if (b[0] == '-') {
        return my_cmp(b, a, flag);
    } else {
        flag = true;
        if (a.size() > b.size()) {
            return true;
        } else if (a.size() < b.size()) {
            return false;
        } else {
            //�����ַ���ͬ�����±ȽϹ����������Ƚ�һ�µı���
            return a.substr(1) >= b.substr(1);
        }
    }
}

void input_handler(string &a, string &b, bool &sym, bool &judge) {
    cout << "�������ʶ��������������1Ϊ�ӷ���2Ϊ�������Կո���������һ��0Ϊ�˳���" << endl;
    string x, y;
    int flag;
    cin >> flag;

    if (flag != 0) {
        cin >> x >> y;
        if (flag == 2) {
            cout << x << "��" << y << "�Ĳ�";
            if (y[0] == '-') {
                y = y.substr(1);
            } else {
                y = "-" + y;
            }
        } else
            cout << x << "��" << y << "�ĺ�";
    } else {
        state = false;
        return;
    }

    //�����λ

    if (x[0] != '-') {
        x = "+" + x;
    }
    if (y[0] != '-') {
        y = "+" + y;
    }

    if (my_cmp(x, y, judge)) {
        sym = true;
    }
    a = x.substr(1), b = y.substr(1);
}

int main() {

    while (true) {
        // string c,d;
        string a, b;
        //���Ʒ���λ���
        bool sym = false;
        //�жϾ���ֵ����������
        bool judge = false;

        input_handler(a, b, sym, judge);
        if (!state) {
            break;
        }

        string res;
        if (judge)
            res = Minusbigdata(a, b);
        else
            res = Addbigdata(a, b);
        string opt;
        if (res != "0")
            if (sym)
                opt = '-';
        cout << "�Ľ��Ϊ" << opt << res << endl;
    }

    cout << "�������" << endl;
    return 0;
}
