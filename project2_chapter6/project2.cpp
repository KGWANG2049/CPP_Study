#include <iostream>
#include <string>
#include <fstream>
#include <algorithm> 

using namespace std;

struct MyStruct
{
    string sign;
    string num;
};
string otherToten(int a, string str)
{
    long long num = 0;
    if (a > 10)
    {
        for (int i = str.size() - 1; i >= 0; i--)
        {
            int x = str[i] - '0';
            if (str[i] >= 'A' && str[i] <= 'Z') {
                x = str[i] - 'A' + 10;
            }

            int n = str.size() - i - 1;

            num = num + x * pow(a, n);

        }
    }
    else if (a <= 10)
    {
        for (int i = str.size() - 1; i >= 0; i--)
        {
           
            int n = str.size() - i - 1;
            int x = str[i] - '0';
            num = num + x * pow(a, n);
        }
    }
    string str1 = to_string(num);
    return str1;
}

string Tentoother(int b, string str)
{
    if (b <= 10)
    {
        long long num = stoll(str);
        string res = "";
        while (num)
        {
            string el = to_string(num % b);
            res = res + el;
            num = num / b;
        }
        reverse(res.begin(), res.end());
        return res;
    }
    else if (b > 10)
    {
        long long num = stoll(str);
        string res = "";
        while (num)
        {
            char el;
            if (num%b >= 10)
            {
                el = 'A' + num % b - 10;
                res = res + el;
            }
            else
            {
                res = res + to_string(num % b);
            }
            
            num = num / b;
        }
        reverse(res.begin(), res.end());
        return res;
    }
}

string jian(string a, string b)
{
    string s1 = a;
    string s2 = b;
    if (s1 == s2) {
        return "0";
    }
    string s3;
    bool flag = false;
    if (s1.length() < s2.length() || (s1.length() == s2.length() && s1 < s2)) {
        std::string s = s1;
        s1 = s2;
        s2 = s;
        flag = true;
    }
    else {
        s3 = "";
    }
    while (s2.length() < s1.length()) {
        s2 = "0" + s2;
    }
    int k, down = 0;
    for (int i = s1.length() - 1; i >= 0; i--) {
        k = s1[i] - s2[i] + down;
        if (k < 0) {
            down = -1;
            k = 10 + k;
        }
        else {
            down = 0;
        }
        s3 = (char)('0' + k) + s3;
    }
    k = 0;
    while (s3[k] == '0') {
        k++;
    }
    s3 = s3.substr(k);
    if (flag)
        s3 = "-" + s3;
    return s3;
}

string addStrings(string num1, string sign1, string num2, string sign2)
{

    string res = "";
    if (sign1[0] != '-' && sign2[0] != '-')
    {
        int i = num1.size() - 1, j = num2.size() - 1, carry = 0;
        while (i >= 0 || j >= 0 || carry) {
            int sum = 0;
            if (i >= 0) sum += (num1[i--] - '0');
            if (j >= 0) sum += (num2[j--] - '0');
            sum += carry;
            carry = sum / 10;
            sum %= 10;
            res += to_string(sum);
        }
        reverse(res.begin(), res.end()); // 反转字符串
        int k = 0;
        while (res[k] == '0') {
            k++;
        }
        res = res.substr(k);
        return res;
    }
    else if (sign1[0] == '-' && sign2[0] != '-')
    {
        return jian(num2, num1);
        }
   
    else if (sign1[0] != '-' && sign2[0] == '-')
    {
        return jian(num1, num2); 
        }
    else
    {
        int i = num1.size() - 1, j = num2.size() - 1, carry = 0;
        while (i >= 0 || j >= 0 || carry) {
            int sum = 0;
            if (i >= 0) sum += (num1[i--] - '0');
            if (j >= 0) sum += (num2[j--] - '0');
            sum += carry;
            carry = sum / 10;
            sum %= 10;
            res += to_string(sum);
        }
        reverse(res.begin(), res.end()); // 反转字符串
        int k = 0;
        while (res[k] == '0') {
            k++;
        }
        res = res.substr(k);
        res.insert(0, "-");

        return res;
    }
}

MyStruct opeater_sub(string a) 
{
    MyStruct stru;
    if (a[0] == '+' || a[0] == '-')
    {
        stru.sign = a[0];
        stru.num = a.substr(1);
    }
    else 
    {
        stru.sign = "";
        stru.num = a;
    }
        
    return stru;
 }

void test02()
{
    int a;
    int b;
    string result = "";
    cout << "Project2 Num_comp_and_conv(please define bit of input)";
    cin >> a;
    cout << "Project2 Num_comp_and_conv(please define bit of output):";
    cin >> b;
    ifstream fin;
    fin.open("numbers.txt", ios::in);
    if (!fin.is_open())
    {
        cout << "无法找到这个文件！" << endl;
        return;
    }

    string num1, num2;
    MyStruct num1stru, num2stru, restru;
    if (!getline(fin, num1) || !getline(fin, num2))
    {
        cout << "读取数字失败！" << endl;
        return;
    }

    fin.close();
    
    num1stru = opeater_sub(num1);
    num2stru = opeater_sub(num2);
    cout << "FUHAO: " << num1stru.sign << num2stru.sign << endl;
    num1 = otherToten(a, num1stru.num);
    cout << "otherToten: " << num1 << endl;
    num2 = otherToten(a, num2stru.num);
    cout << "otherToten: " << num2 << endl;
    result = addStrings(num1, num1stru.sign, num2, num2stru.sign);
    cout << "addStrings: " << result << endl;
    restru = opeater_sub(result);
    result = restru.sign + Tentoother(b, restru.num);
    cout << "Tentoother: " <<result << endl;
}


  
int main() {
    test02();

}