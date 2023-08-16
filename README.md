# CPP_Study
cpp_project and learningnote
# C++

## 第3章. 对象与基本类型

第三节: 复合类型

指针

指向地址头，&代表取地址

可以指向不同对象:

`int main()`

`{`

    `int x = 42;`

    `int y = 56;`

    `int* p = &x;`

    `p = &y`

`}`

指针具有相同的尺寸:

```cpp
#include<iostream>
int main()
{
	int x = 42;
	char y = 33;

	std::cout << sizeof(x) << std::endl;
	std::cout << sizeof(y) << std::endl;
	
	int* p1 = &x;
	char* p2 = &y;
	
	std::cout << sizeof(p1) << std::endl;
	std::cout << sizeof(p2) << std::endl;

}
```

相关操作:

与 &,  作用：位置提取

```cpp
int x = 42;
std::cout << (&x) << std::endl;
```

解引用 *

```cpp
int x = 42;
int* p = &x;
std::cout << *p << std::endl;//输出是一个地址，**读取p目标内存的存储值，读取的长度取决于zeile2
//的int*类型*
```

指针的定义: int* = &val

fig1, 2 ,19:44 全局初始化，缺省初始化，解引用分别为0与随机。 加直接/拷贝初始化

```cpp
#include<iostream>

int *p1; //  全局初始化是0地址

int main()
{
	int x = 42;
	int* p;//  缺省初始化是随机地址

	std::cout << *p1 << std::endl;//解引用0地址无效，直接报错
	std::cout << *p << std::endl; //解引用为随机地址，虽然可能每次大多是1，(endl 换行，清空RAM缓存，输出到屏幕; /n 换行)
}
```

NULL等价与0

int *x = 0; 存在类型转换(bad)*

引入nullptr(指针类型为nullptr_t, 表示空指针)

指针与bool的隐式转换

int main()

{

int*p = nullptr;

//

if(p)  // 非空指针ture

{

}

else

}

```cpp
#include<iostream>
int main()

{
int x = 42;
int* p = &x;
std::cout << p << std::endl; //endl 换行，清空RAM缓存，输出到屏幕; /n 换行.

p = p + 1;
std::cout << p << std::endl;
p = p - 1;
std::cout << p << std::endl;

}
```

void* 指针

由于指针尺寸相同。void* 用来定义接口，(不关注指针类型，只关注是一个指针，可以转换为任何指针)

`void fun (void* param)`

`{`

`//…`

`}`

`int main()`

`{`

`int* r = nullptr;`

`char* k = nullptr;`

`fun(r);`

`fun(k);`

`}`

45min void*非法操作: void字节长度不可预知的，void*作为指针类型无法进行移动操作（klang编译会报错，gcc不会报错，但打印出来的是随机地址）

```cpp
#include<iostream>

void fun(void* param)
{
	std::cout << (param + 1) << std:: endl; // 非法操作
	// *param = *param + 1;
}

int main()
{
	int x = 42;
	int* r = &x;
	std::cout << r << std::endl;
	std::cout << (r + 1) << std::endl; // 移动一个int*长度4
	fun(r);
}
```

利用指针来传参

```cpp
#include<iostream>

void fun(int* param)
{
	*param = *param + 1;
}
int main()

{
	int x = 42;
	int* p = &x;
	fun(p);
	std::cout << x << std::endl;

}
```

problem: 对于缺省初始化的随机地址和空地址，指针无意义或报错

solve: 引用(双修 )

类型后加 & eg : int&（不可以缺省初始化，在一个生命周期它只能被定义一次）

引用的非法操作：变量生命周期之外的引用

```cpp
#include<iostream>

int& fun()
{
	int x;
	return x; // fun函数返回了x的引用后生命周期结束
}

int main()
{
	int& res = fun(); // res为x的引用，x已经被销毁，res变成随机引用（读写不确定）
}
```

引用的本质还是指针

```cpp
int main()
{
	int x= 3;
	int* ptr = &x;

	int*& ref = ptr,//(引用了一个指向int值的指针（指针的引用）)
}

（不存在引用的引用// int& & 错！）（&&右值引用）

验证一下引用的指针行不行！！
不行 int& * 引用不是对象。
```

第四节常量表达式 `const`

```cpp
#include<iostream>
****
int main()
{
	const int x = 4;
	x = 6;
}

#include<iostream>
int main()

{
	int x = 42;
	const int& ref = x;
	x = 43;
	std::cout << x << std::endl;

}

#include<iostream>

int main()
{
	
}

```

常量引用

常量引用函数形参

```cpp
struct Str
{
	// ...
}

void fun(const Str& param)
{
	 param = ... // 若fun不加const param会改变，并传入main中
}

int main()
{
	Str x;
	fun(x);
}
```

常量引用是否非法，看类型是否匹配

```cpp
#include<iostream>
int main()

{
	int x;
	std::cin << x;

const int y1 = x; // (编译阶段无法判断正误)
const int y2 = 3;

if(y1 == 3) // (编译阶段无法判断正误)
{
//...
}
if(y2 == 3)// (编译阶段可以判断正误,一定为真，此行编译阶段可以删除 )
{
//...
}

}
```

常量表达式 `constexpr`

```cpp
#include<iostream>
int main()

{
	int x;
	std::cin >> x;

const int y1 = x; // 编译阶段无法判断正误
constexpr int y2 = 3;//明y2是编译器常量

if(y1 == 3) // 编译阶段无法判断正误
{
//...
}
if(y2 == 3)// 编译阶段可以判断正误,一定为真，此行编译阶段可以删除 
{
//...
}

}
```

类型别名

```cpp
typedef int MyInt;
// or using MyInt = int; 为了增加可读性
int main()

MyInt = x;

//size_t define type which has any size.

typedef char MyCharArr[4];
using MyCharArr = char[4];

const int *Ptr = &x;// 对比下面的

using IntPtr = int*;
int main()
{
	int x = 3;
	const IntPtr ptr = &x;
}

//使用 auto 避免类型转换

int main()
{
int x = 3.5 + 12l;
auto y = 3.5 + 12l;

std::cout << x <<\n'; 
std::cout << y <<\n';
}

//auto带来的类型退化(常发生在右值使用中)
#include <type_traits>
int main()
{
int x1 = 3; 
int& ref = x1;
auto y = ref;// int& 退化成int

std::cout << std:: is_same_v<decltype y, ref>
}

//36min const auto x = 3 

```

auto& 会优先转换为全部的类型名

```cpp
const int x = 3;
auto& y = x;
std::cout<< std:: is_same_v<de

//数组退化为指针

int x[3] = {1,2,3};
auto& y = x;
std::cout<< std:: is_same_v
```

`decltype`无类型退化

```cpp
int x= 3;
int& y1 = x;
auto y2 = y1;
decltype(y1) y3 = y1;

std::cout<< std:: is_same_v<decltype(y2), int> << std:: endl;

```

`decltype`左值加引用，左值是变量名称，就直接无退化推导，左值是非变量名称比如解引用`*ptr`，为无退化推导加引用

```cpp
#include<iostream>
#include <type_traits>
int main()
{
	int x = 3;
	int* ptr = &x;
	(x) = 5;

	const int y1 = 3;
	const int& y2 = y1;
	std::cout << std::is_same_v<decltype (3.5 + 15l), double> << std:: endl;
	std::cout << std::is_same_v<decltype(*ptr), int&> << std::endl;
	std::cout << std::is_same_v<decltype(ptr), int*> << std::endl;
	std::cout << std::is_same_v<decltype(x), int> << std::endl;
	std::cout << std::is_same_v<decltype((x)), int&> << std:: endl;
	std::cout << std::is_same_v<decltype(y1), const int> << std:: endl;
	std::cout << std::is_same_v<decltype(y2), const int&> << std:: endl;
	std::cout << std::is_same_v<decltype((y1)), const int&> << std:: endl;
	std::cout << std::is_same_v<decltype((y2)), const int&> << std:: endl;
}
// 输出全为1
```

17 域(scope)与对象的生命周期

[]()

## 4. 数组，vektor 与字符串

```cpp
int a;
int b[10]; //int[10] 
std:: cout << std:: is_name_v<decltype(b), int[10]> <<std:: endl;

int x:
std:: cin >>x;
int b[x];// 不合法，编译阶段无法读取cin类型.g++会提示错误

constexpr x; 定义可以，因为是const

Google >> verious array

数组的初始化
缺省初始化》
int b[3];存的是三个随机值（函数中）
         存的是000（全局域中）

聚合初始化>>

int b[3] = {1,2,3};
          ={1}; (100)

int b[] = {1,2,3,4,5}

!!!
1.不能用auto推导数组类型
auto b = {1,2,3};
b的类型不是数组类型，可用#include<tpyeinfo>检查类型，应该是初始化列表（initializer_list）
2. 数组之间不可复制
int b[3] ={1,2,3}
int a[3] = b;(false)

若把数组赋值给auto b，b为一系列指针而不是数组。(退化)
int a[3] = {1,2,3};
auto b = a;
// decltype(b) 为int*(指向数组头)
//所以std::cout << b[1]就是2
//std:: cout << *(a+1) <<std:: endl;也输出2，a单拿出来输出的时候，a就退化为指向数组头部的指针。之后*a, *(a),都输出1，以此类推。

//a[2]也可以写成2[a]

字符串数组
#include<typeinfo>
int main()
{
	char str[] = "hello";(类型是char6，后面有\0)
//char str[] = {'h','e','l','l','o','\0'}(与上面等价)
}

数组的复杂声明
int main()
{
	int x1;
	int x2;
	int x3; 
	int *a[3];// (指针数组)(int *[3])
int (*a)[3];// (数组的指针)（int（*）[3])
}

引用的数组不可用

	int x1;
	int x2;
	int x3; 
	int& a[3] = {x1,x2,x3}(数组必须包含对象，而不能是对象的别名，使用声明int&，本身是错的)

数组是一个左值(L-value),在c++中，左值是:locator value，比如const int，不可放在等号左边进行赋值更改，但是也是左值，因为...

数组到指针的转换,

a是一个数组
auto b = a;// 数组到指针的隐式转换，丢失了数组长度信息

auto& b = a;// 引用不会产生退化！
//指针有自己的地址空间信息，存储的是指向的地址信息

数组的声明
extern int arrary[4]; //在main函数外部

extern int* arrary[];// 不可以，因为arrary不可以当做指针使用
ertern int arrary[]; //正确，是一个unknown bounded arrary
int main()
{
	std::cout << arrary << std:: endl;
}

int a[3] = {1,2,3};
&(a[0])与 cbegin(a), &(a[3])与 cend(a) c是const的意思，begin与end只能用于明确定义长度的数组的指针获取，unknown bounded array不可以（不仅数组，vektor和strength也可以用）

指针的算数

int a[3] = {1,2,3};
auto ptr = a;
ptr = ptr + 1;//指针的增加
== != > < //指针的比较，不同数组之间不要这样比
ptr之间相减是80减去64，然后再除以ptr的指针的类型，显示的是两个指针之间的元素的个数。

指针的长度

int a[3];

sizeof(a)/sizeof(int);//编译期方法

size(a);//编译期方法 

std::cend(a) - std::cbegin(a); //y运行期方法，因为cbegin cend，a在运行时才开辟内存。

元素遍历

int a[4] = {2,3,4,5};

for(int x:a); //cpp11可编译

while(cbegin(a)!= cend(a))

size_t index < std:: size(a)

for(int x :a) //range for 操作 cpp11可编译
{
	std::cout << x << std::endl; 
}

C字符串
char str[] = "hello";// cahr[6]
auto ptr = str; //char*
std::cout << strlen(str) << std:: endl;// 当char定义是逐个定义，最后一位后面不一定是\n,strlen可能出错 
std::cout << strlen(ptr) << std:: endl;

多维数组

int x2[3][4];// 四个一堆，3堆

一个int 是4
sizeof(x2[0])是16
多位数组只能省略最高位
int a[][2][4];

多维数组的遍历

30min while循环实现 行向（内存连续性更优，减少内存到cash的读写）和列向遍历

多维数组的退化
多维数组也是数组，其最高维度退化为指针
int a[2][4];
auto ptr = a;// ptr类型为指针int [*ptr][4]

也可写成
using A = int[4];
int main()
{
A x2[3];
int a[3][4];//等价
}

vektor
int a[3];
int b = a://数组不可复制，报错

std>>vektor<int> x;//元素个数为0
std>>vektor<int> y;
y = x; //vektor可以复制
也可在运行期改变元素的个数

vetkor初始化

聚合初始化
std::vektor<int> x = {1,2,3};
std::vektor<int> x(3);
std::vektor<int> x(3,1);//三个元素，全为1 
x.size() x.empty()

插入删除
x.push_back(2);//插入
x.pop_back();// 从尾部删除元素

#include <iostream>
#include <vector>

int main() {
    std::vector<char> charVector;

    charVector.push_back('H');
    charVector.push_back('e');
    charVector.push_back('l');
    charVector.push_back('l');
    charVector.push_back('o');

    // 遍历vector并输出字符
    for (const auto& ch : charVector) {
        std::cout << ch;
    }
    std::cout << std::endl;

    return 0;
}

vektor的大小比较默认比较第一个元素值，如果相等，往后比（字典排序）

x.at(2)和x[2]相同含义

也可用std::begin(x) std::end(x); 
auto a = x.begin() or x.end() //vektor中叫 迭代器，类似指针的行为，两个迭代器或者指针的比较必须指向一个vektor或者vektor

对vektor进行添加和删除会使begin end操作失效

多维vekotr
std::vektor<std::vektor<int>>x{{...},{....}};

.与->

x.size()
x->size()

string
4:20 很搞笑 
y = y + "q";

两个连续内建字符串不可以相加。只要中间隔一个string就行。

.c_str()

std::string x("hello");
auto ptr = x.c_str(); //c风格的指针
std::cout << ptr << std::endl;//直接输出了指针指向的对象
	
//C风格字符串（以null结尾的字符数组）在C++中的输出时，不需要解引用是因为std::cout流对象的重载运算符<<已经针对C风格字符串进行了特殊处理。

//std::cout是C++标准库中的标准输出流对象。它提供了对不同类型数据的输出功能。为了方便输出C风格字符串，C++标准库重载了<<运算符，使其能够接受以null结尾的字符数组作为参数。

//当您将C风格字符串作为参数传递给std::cout的<<运算符时，它会自动识别传递的参数是一个C风格字符串，并按照字符串的内容进行输出。这是因为C风格字符串的特殊性，它以null字符（'\0'）作为字符串的结束标志，而不需要指定长度。

//因此，在输出C风格字符串时，不需要对指针进行解引用操作。std::cout会自动根据指针指向的字符数组的内容输出字符串，直到遇到null字符为止。这是C++标准库为了方便输出字符串而设计的特殊行为。

		··
```

## 第五章: 表达式

```cpp
int x;
x = 3;

//表达式由一到多个操作数组成，可以求值并 ( 通常会 ) 返回求值结果。

操作符的优先级与结合性:
优先级，比如乘法高于加法
结合性:比如多个加减操作符，默认left to right 或者相反，小括号结合等

左值和右值 > 等号左边还是右边

随着c发展，左右值完全混乱了。。。

xvalue（亡值）:在一个main中可以使用std::move()把参数结束掉

const int x = 3;
x是一个标识符，是常量，
x = 4;(错)//典型的左值不可放在左边的例子

struct Str{};
int main()
{
	Str x = Str();
}

int x = 3;
int y = x;//左值可以变为右值
x + y;

struct Str{
	int x;
};

int main();
{
	Str().x;//纯右值str加'.'变将亡值
}

再论decltpye！

decltype可以传入实体或者表达式
实体:
decltype(3) x;//3为纯右值，dec 产生T&&

表达式:
int x; 
decltype ((x)) y=x;//x是左值，dec产生T&

int x;
decltype(std:: move(x)) y=x;//报错，右值引用不可以放到左值
decltype(std:: move(x)) y=std::move(x);//int && y = std::move(x); y是右值引用

算数操作符：

一元操作符，加 减 负号(优先级最低)
乘 除 百分号（求余）（次优先）

7* +3

ptr = ptr + 1;//一元运算可用于动态数据类型转换

e.g：
int a[3] = {1,2,3};
const auto& x = +a;//引用之后本没有转换，通过一元运算强制动态数据类型转换成 int *const & x = +a;

```

### 逻辑与关系操作符

cppreference operator的 8~10 可以接受算数或者指针的运算操作

```cpp
int x = 3;
3 && x; //x转换为ture（两者为指针也可以）

非操作符 “！”先计算！左边的算式（右结合）

逻辑与的短路特性
与逻辑第一个判断为false，之后的行为将不再判断（短路），即使后面的定义是错误的
int* ptr = nullptr;
if(ptr && (*ptr ==3))// 左结合

逻辑或的短路特性
a || b；//当a为真，b不再判断 

&&优先级高于|| （查找cppreference operator）

多个逻辑运算操作串联不可以
int a = 1;
int b = 2;
int c = 3;
std::cout<<(a<b<c)<<std:;endl;//返回false，因为a<b返回bool 
int a = 3;
if(a == ture) 返回false// int值和bool进行比较的时候，bool会转换为int型 1

sapcship <=>
auto res = (a <=> b); //strong(有equivalent和equal)/weak(有equivalent，无equal)/partial(比weak多一个unordered，无法排序，NaN，not a number)  ordering 
if(res>0)
{
}
else if(res<0)
{
}
else if(res==0)
{
}

double f = 5.0;
auto res = (sqrt(-1)<=> f);
std::cout << (res > 0) << std::endl;
std::cout << (res < 0) << std::endl;
std::cout << (res == 0) << std::endl;
std::cout << (res == std::partial_ordering::unordered) << std::endl;// partial(比weak多一个unordered，无法排序，NaN，not a number) ordering 打印结果：0001

位操作符：
unsigned char x = 3;
std:: cout<< ~x << std::endl; //按位取反 00000011到11111100， 输出-4，第一个1是负
x & y //有0则0 11才1
x | y //有1则1，,00才0
x ^ y //异或 相同为1
x << 1 // 00000011变成00000110
x >> 1 // 00000011到00000001
x = -4;
x >> 1 //11111100到11111110（左侧补的还是1）打印的时候整体加括号

一定情况下，左移等价于乘2（左边有空位），右移除以二（右边有空位），执行速度更快相算数运算

补码操作符
unsigned char x = 0xff; //11111111  255
//000...000011111111 //整形提升，有符号按照符号位提升。无符号按照0提升，右移可以保证符号，左移不一定 int默认都是有符号类型
//111...111100000000   256
auto y = ~x
std:: << cout << y <<std::endl: // 256

赋值操作符（二元操作符，一左一右的操作数，左参必须可变，右参类型可转化为左参的类型）
x = 3;
x = y = 3; //求值结果为左操作数，即y为3，y是左操作数

收缩转换
short x;
x = 0x80000003
std:: << x << std:: endl; // short 2byte,十六进制用4位表示， 

引入大括号（初始化列表）防止（丢失信息的收缩转换）会报错
constexpr int y = 3;
short x;
x = {y};// 不会报错，输出3，因为1，constexpr通过编译期运算右值得到y为常量3，,2，,3收缩转换后仍为3没有改变

const int y = 3;
short x;
x = {y};// 会报错，因为编译期不会将y作为固定值3，导致右值不是常量，报错。

x += 2;// x = x+2
x *= 3;// x = x*3

x^=y^=x^=y; //x打印为3，y为2

优先使用前缀形式
自增运算++i //自身加1，返回i的变换后的值。返回的就是i，返回的是左值 （x=x+1）
自减运算--i

int i = 5;
int a = ++i; // i先递增为6，然后a被赋值为6

后缀自增i++ //自身加1.返回i的原始值。返回的是临时变量不可被改变，是右值。 
后缀自减i--

int i = 5;
int a = i++; // a被赋值为5，然后i递增为6

其他操作符:

1.成员访问操作符（用于结构体和类中）

"." 操作符:
struct Str
{
	int x;
};
int main()
{
	Str a;
	a.x;

	Str* ptr = &a;
	(*ptr).x;
	ptr->x;
}

decltype()读取数据类型，括号中可以是实体和类
decltype(a.x) y; // 编译之后 int y ，因为a.x被视为实体
decltype((a.x)) y; //编译之后 y的类型是一个引用 ，因为加括号的a.x被视为左值表达式，decltype产生类型退化，左值表达式退化为类型的引用，即int&，但是int&需要进行初始化，所以会报错
decltype((a.x)) y = a.x; 加入初始化，编译结果:int & y = a.x;
a.x中的a，即点的左操作数是一个左值，所以返回左值

在这个例子中，str a; 定义了一个名为 a 的结构体变量。因为它具有名称并且是一个变量，所以它是一个左值。你可以对它进行赋值操作或者取地址。
而 str(); 是一个右值。它是一个匿名的临时结构体对象，没有持久的标识符或名称。你不能对它进行赋值操作，因为它没有标识符来引用它。\

decltype((Str().x)) y = a.x;
当decltype括号中是一个右值(因为点操作数是一个右值，返回将亡值)，规定将亡值的decltype是右值引用

条件操作符：（转化bool ? 相同类型1 : 相同类型2）布尔为真，求第一个，布尔为false，求第二个
是一个唯一的三元操作符 

int x = 2;
int y= 3;
true ? (++x) : (++y);

当两个类型存在右值，则条件操作符返回右值，只有全为左值才返回左值。
int x = 3;
true ? x : 1;
多个条件操作符串联，右结合。 

"," 逗号操作符:
左结合操作符！
只输出逗号右侧的值。

int x;
int y;
++x, ++y; //先算++x，再算++y
fun(++x, ++y); //随机算

sizeof操作符: 返回字节数
siezof（类型（int）和表达式x）
sizeof (int);
sizeof (x);

域解析操作符 "::"

namespace ABC
{
	int x;	
}

int main()
{
	int x;
	int y = ABC::X;// 名字空间只可以使用::,不可以用.
}

函数调用操作符()
索引操作符[]
抛出异常操作符 throw

```

## 第六章 语句

```cpp
复合语句，换行不敏感，只看分号划分, 对缩进不敏感。
{}定义了一个语句，初始化的变量会在货号结束的时候消亡。
int main()
{
	int grade = 65;
	if (grade < 60)
}

非顺序语句:
在执行过程引入跳转。
if （）goto label;
label:
	......

togo 不能实现跨函数跳转，前向跳转也不可以跳过label中含有的变量初始化语句，后向跳转可能出现对象销毁和重新初始化

分支语句 —— if

if constexpr()// 括号里的条件必须是常量表达式
常量可以在编译期可以确定那些语句可以被执行,运行期前，程序被优化。（下例中若为if，则全被运行，if constexpr只运行两行）
int main()
{
	constexpr int grade = 80;
	//if constexpr (grade < 60)
	//{
		//std::cout << "fail\n"
	//}
	//else
	//{
		std::cout << "pass\n" //被运行
			//if constexpr (grade ==100)
			//{
				//std::cout << "excellent\n";
			//}
			//else
			//{
				std:: cout << "notbad\n" 、、被运行
			}
}
cpp17之后，if和constexpr if 括号中可以添加初始化语句，if分支语句结束之后可以立即释放内存。
int main()
{
	int x = 3;
	if(int y = x * 3; y > 100)
	{
	}
	else
	{
	}
	int y = 4;//合法定义，x已被释放
}

分支语句 —— switch
switch();// 整形和枚举类型的条件，可使用case和default标签。

case标签:
std:: cin >> x; //执行输入和输入之后的case，在case后面加入break标签可以打断
switch(x)
{
case 1:
	....... 
	break;
caes 2:
	.......
}

default标签

std:: cin >> x; //如果x不是1或者2，执行default后续的代码
switch(x)
{
case 1:
	......
	break;
caes 2:
	......
	break;
default:
	......
	break;
}

switch中的case和default中如果有初始化操作，则无法调到这个case/default后面的分支
解决方案：
分支加大括号
std:: cin >> x;
switch(x)
{
case 1:
	......
	break;
caes 2:
	{
		int y = 2; //case2分支加大括号
		......
		break;
	}
default:
	......
	break;
}

多个分支可以在一起书写，让不同标签实现相同功能
std:: cin >> x; 
switch(x)
{
case 1:
	......
	break;
caes 2:
caes 3: //多个分支可以在一起书写，让不同标签实现相同功能
	......
	break;
default:
	......
	break;
}

		[[fallthought]]; 属性 //当希望执行多个分支自动向下执行，

{
case 1:
	......
	[[fallthought]]; //当希望执行case1后，分支自动向下执行。
caes 2:
	{
		int y = 2; 
		......
		break;
	}
default:
	......
	break;
}

由于switch的条件是常量表达式，codepreject.articales 100473 something you may not know...解释了优化操作

循环语句—— while

while() //括号里加条件,这个条件不包含额外的初始化
int x = 3;
{
	while (x )
}

循环语句—— do while //先do一遍，在while

int x = 3;
do
{
	......
	
}while (x)

```

for 循环：四个声明

初始化语句（必须以分号结束）(只在这个for中生存)

条件（可选）

迭代表达式（可选）

语句

```cpp
int main()
{
	for (int x = 0; x < 6; ++x)
	{
		syd:: cout<< x << std:: endl;
	}
}

for（int x = 0, *p = &i;） //初始化语句可以声明多个名字，名字的基础类型必须相同，int 与 int*
for（ ; ; ）//正确的，初始化，条件与迭代表达式可以为空，条件语句为空，系统默认为true
条件可使用可被隐式转换的等式，例如
char c = cstrin[n], //c为0>false

基于范围的for循环：
int main ()
{
	std:: vektor<int> arr{1,2,3,4,5};
	for (int v : arr) //范围声明: 范围表达式
		std::cout << v << '\n';
}

cpp17中的基于范围的for循环语法糖
{
auto && __range = 范围表达式 ;
for (auto __begin = 首表达式, __end = 尾表达式 ; __begin != __end; ++__begin)
{
范围变量声明 = *__begin;
循环语句
}
}
```

[基于范围的 for 循环 (C++11 起) - cppreference.com](https://zh.cppreference.com/w/cpp/language/range-for)

17到20修改foo.item临时变量被销毁后range后的语句执行为空的bug

```cpp
int main()
{
	std:: vektor<std::string> arr{"h","e","l"}
	for (std::string& v : arr) //for (const std::string& v : arr) //for (cosnt auto& v : arr)
		std::cout << v << '\n';
}

做修改，最好使用万能引用
int main()
{
	std:: vektor<bool> arr{true, false}
	for (auto&& v : arr)
		v = false;
}

//循环语句——break/continue:break 导致循环终止， continue 
continue例子
int main(void)
{
	for (int i = 0;i < 10; i++)
		{
			std::cout << i << ' ';
			if (i != 5) continue;
			std::cout << i << ' ';
		}
} 

// break/continue只能跳出自身循环

togo 可以随意跳出
int main(void)
{
	for (int i = 0;i < 10; i++)
		{
			std::cout << i << ' ';
			if (i != 5) goto label;
			std::cout << i << ' ';
		}
label:
	......
} 
```

达夫设备

图1，OK的

16行的逻辑对的，速度快，14行循环速度很慢；

如何解决14行的问题：循环展开

图2，减少了迭代表达式和条件的判断，如果是10001的话，内存越界

解决方法 图3

但不是最优的，可用指针和switch解决

图4 和5 

但是读者感觉还是很复杂

先让数组处理几个，直到可整除循环

图6 7

再优化：达夫设备

图8

## 第七章 函数

```cpp
如果函数在引用的后面，可以使用声明（函数头加分号）在引用前面。或者通过hearder.h文件里面声明，然后通过引用header.h，在多个文件中声明。

Stack Frame 栈帧结构：
函数之间的罗列，是结构栈存储。（例如main()（bottom）与引用函数A()（top）

可以通过extern“C”，让下面的函数以c语言的法则运行，c中无法函数重构（c只靠函数名确定函数本身，无形参变化）
```

### 函数详解：参数

```cpp
0形参，用void标注
void fun(void) 或者void fun()
{

}

形参可以没有名称，但必须有类型。编译器会使用类型信息进行编译。一般而言，为了预留参数，只是把参数类型写在括号里。
函数中的多个形参的初始化的顺序不定，所以参数实例化时，各参数不要有先后的逻辑计算关系。

int a{};  // a是一个初始化为0的整型变量a被定义为一个int类型的变量，大括号{}会将其初始化为0。
这样的初始化方式有一些优点，如防止窄化转换，因此在许多现代C++代码中更为常见。

void fun(Str par)
{
};
int main 
{
fun (Str{})
};

Str{}是一个临时对象，它将复制到Str par,属于拷贝临时对象。cpp17之后会强制省略这个步骤，17之前是随机省略的。

**函数中的传值与传址与传引用：（实参形参交互）

传址：
void fun(int* par)
{
	++(*par);
};

int main()
{
	int arg = 3;
	fun(&arg);
	std::cout << arg <<'\n';
}

传引用：
void fun(int& par)
{
	++par;
};

int main()
{
	int arg = 3;
	fun(arg);
	std::cout << arg << '\n'
	等价于：
	int& par = arg;
	++par;
}

拷贝初始化的类型退化:

void fun(int par[3])
{
};

int main()
{
	int a[3];
	fun(a);
}

int a[3];
auto b = a; 退化为指针 int*,拷贝初始化中也会出现类似的传参退化，所以void fun(int par[3])中的3不要写，incomplete type：int par[]
int[3][4],拷贝初始化退化为int(*par)[4]

防止拷贝初始化退化问题
如果定义一个引用b，b的类型不会发生退化:
  int a[3]   >>  int (&par)[3])

变长参数：
（1）initializer_list
#include <initializer_list>

void fun(std::initializer_list<int>par)  //传入参数类型必须相同
{
};

int main()
{
	fun([1,2,3,4,5])；
}

（2） 变长模板（以后讲）
（3）省略号表示形参（不好）

函数缺省实参：
void fun(int x =0)

int main()
{
	fun(1);打印出1
	fun();打印出0
}

缺省实参的右侧所有都必须缺省实参（很像python类中的init default）
因为当存在缺省实参的时候，当实例化参数会从左到右的匹配形参。

在函数的定义和声明中缺省实参只能定义一次：
void fun(int x=2, int y, int z=1);  //声明
void fun(int x, int y=4, int z)  //定义
在不同的翻译单元，可以重复定义形参和缺省实参。55min 50

缺省实参为对象时，实参的缺省值会随着对象值的变化而变化
图中打印值为3，若主函数定义x = 4, 打印为4**
```

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/4121b8a2-2696-4315-a02e-8bc62fdfc36d/Untitled.png)

函数体

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/8692c0f0-1823-486d-b943-6e84b82eb34f/Untitled.png)

隐式返回，因为使用了void，不返回数值和对象

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/89787b6d-cbc6-4b1c-a90f-7d247fb4d755/Untitled.png)

隐式返回了一个随机值 （g++）

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/217d12db-c7a7-4d8a-82ab-c21808c17402/Untitled.png)

initializer_list 是两个指针，第一个函数的return在 auto x = fun()时被销毁，指针不指向原来的返回值，x为空。

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/94c30bc9-fc31-4928-9455-a0c823f81c85/Untitled.png)

引用绑定别名，x已销毁，返回值不确定，很危险

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/13780f1c-cd93-418f-8e74-8359e58f41be/Untitled.png)

x的地址指向x，在main中，第二行x被销毁，指针指向被销毁的对象。

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/79923d33-da5a-42c9-be8b-d8de5747f26d/Untitled.png)

static局部对象会保存到整个程序结束

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/e457f145-0eb6-4bc1-8ee3-dbe2903ebe1b/Untitled.png)

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/8fab1414-74ca-4a15-8de0-99c81d9cbc1c/Untitled.png)

加入修改编译器规则后关闭了返回值优化，会打印拷贝构造两次，如果不关闭，则fun中的操作都将在res所在地址进行操作，无拷贝操作。

RVO（返回值优化在c++17中是无法关闭的，临时变量的拷贝构造都会被强制优化，如果是非临时变量则不会被优化）

函数的返回类型：

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/0c628cef-6a0a-418c-b2a6-cab20b2b187c/Untitled.png)

c++11引入的声明方式，返回类型写在函数头的后部。这样操作函数的返回类型可以进行自动推导

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/9a8fd2f9-d5a6-4432-83af-4f28ac44c71e/Untitled.png)

constexpr 在编译器中把未执行的部分直接优化掉，使得程序可以返回类型对象

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/fd59b3e5-897b-444d-8938-d38e551f503f/Untitled.png)

c++17结构化绑定！（e.g 结构体的结构化绑定）

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/c660abe6-10bd-4d77-8fd4-19187ea01014/Untitled.png)

[[nodiscard]]（c++17）可以检查函数是否使用返回值。如果没有使用会报警告。
