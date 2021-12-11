## boost_format
format没有snprintf快，但它是类型安全的。它使用streams构建输出，所以不会存在内存溢出的情况。

format有两种使用风格，一种类似于 printf，另一种使用占位符，类似于c#。

##### 浮点数格式

```cpp
const double almostpi = 22.0 / 7.0;
 
// Printf
printf("Pi is %f\n", almostpi);
 
// Boost format with printf syntax
boost::format printf_formatting("Pi is %f\n");
std::cout << printf_formatting % almostpi;
 
// Boost format with positional syntax
boost::format position_formatting("Pi is %1%\n");
std::cout << position_formatting % almostpi;
 
// Output:
// Pi is 3.142857
// Pi is 3.142857
// Pi is 3.14286
```

format的使用与printf类似，使用 %f 格式化一个浮点数，默认的精度是6位小数。

使用更大的数据可以验证这个结论，如：

```cpp
const double almostpi = 22.0 / 7.0;
const double distancetosun = 149600000000.0;    // meters
const double earthorbitlength = 2 * almostpi * distancetosun;
 
// Printf
printf("Earth orbit distance is %f meters\n", earthorbitlength);
 
// Boost format with printf syntax
boost::format printf_formatting("Earth orbit distance is %f meters\n");
std::cout << printf_formatting % earthorbitlength;
 
// Boost format with positional syntax
boost::format position_formatting("Earth orbit distance is %1% meters\n");
std::cout << position_formatting % earthorbitlength;
 
// Output:
// Earth orbit distance is 940342857142.857180 meters
// Earth orbit distance is 940342857142.857180 meters
// Earth orbit distance is 9.40343e+011 meters
```

使得 **%1%** 占位符时，当数值较大时，会使用科学计数法（大概6-7个字符长度时会使用）。

##### 关于科学计数法

```cpp
boost::format scinotation("Do we use scientific? '%1%'\n");// %llu时也会显示科学计数法
 
for (size_t n=0; n<15; ++n)
{
    double value = 1 * pow(10, n) + 0.5;
    std::cout << scinotation % value;
}
 
// Output:
// Do we use scientific? '1.5'
// Do we use scientific? '10.5'
// Do we use scientific? '100.5'
// Do we use scientific? '1000.5'
// Do we use scientific? '10000.5'
// Do we use scientific? '100001'
// Do we use scientific? '1e+006'
// Do we use scientific? '1e+007'
// Do we use scientific? '1e+008'
// Do we use scientific? '1e+009'
// Do we use scientific? '1e+010'
// Do we use scientific? '1e+011'
// Do we use scientific? '1e+012'
// Do we use scientific? '1e+013'
// Do we use scientific? '1e+014'
```

另外，**在实际使用中，如果使用了不匹配的标记符时，如使用了%llu, 而实际数值却是double时，也会以科学计数法显示。**

可以使用 %e 显示指定以科学计数法显示。

##### 格式控制

格式控制的语法为：`%[N$][flags][width][.precision]type-char`。如：

#### 常用示例

```cpp
// 直接输出
cout << boost::format("%s") % "this is what i want" << endl; 

// 结合 string
string s;
s = str(boost::format("%s") % "this is what i want");
cout << s << endl;

// 使用 formater
boost::format fmt("%s");
fmt % "this is what i want";
string s = fmt.str();
cout << s << endl;

// 占位符
cout << boost::format("%1%") % "this is what i want" << endl;
```

#### 异常处理

format 异常时会throw 异常信息，所以要使用try语句块处理异常，否则程序默认会终止。如：

```cpp
try
{
	cout << boost::format("%d%d") % 1 << endl;
}
catch (std::exception const &e)
{
	cout << e.what() << endl;
}
catch (...)
{
	cout << "format error" << endl;
}

// output
// boost::too_few_args: format-string refered to more arguments than were passed
```





### 比较多个生成器序列的性能

这些性能测量以一系列不同项目的格式为中心，包括`double` 使用不同库和方法的2 个浮点数。下面比较了这些示例的总体执行时间。我们比较 using `sprintf`、C++ iostreams、 [Boost.Format](https://www.boost.org/doc/libs/1_52_0/libs/format/index.html)和 *Spirit.Karma*。

有关性能测试的完整源代码，请参见此处：[format_performance.cpp](https://www.boost.org/doc/libs/1_52_0/libs/spirit/optimization/karma/format_performance.cpp)。所有测量都是通过`1e6` 对每种格式类型进行迭代来完成的（NUMITERATIONS 设置为`1e6`）。

用于衡量 sprintf 性能的代码：

```cpp
char buffer[256];
for (int i = 0; i < NUMITERATIONS; ++i) {
    sprintf(buffer, "[%-14.3f%-14.3f]", 12345.12345, 12345.12345);
}
```

用于衡量标准 iostream 性能的代码：

```cpp
std::stringstream strm;
for (int i = 0; i < NUMITERATIONS; ++i) {
    strm.str("");
    strm << '['
      << std::setiosflags(std::ios::fixed)
      << std::left
      << std::setprecision(3)
      << std::setw(14)
      << 12345.12345
      << std::setw(14)
      << 12345.12345
      << ']';
}
```

用于衡量[Boost.Format](https://www.boost.org/doc/libs/1_52_0/libs/format/index.html)性能的代码：

```cpp
std::string generated;
boost::format outformat("[%-14.3f%-14.3f]");
for (int i = 0; i < NUMITERATIONS; ++i)
    generated = boost::str(outformat % 12345.12345 % 12345.12345);
```

以下代码显示了所有*Spirit.Karma* 性能测量使用的通用定义，如下所列：

```cpp
template <typename T>
struct double3_policy : boost::spirit::karma::real_policies<T>
{
    //  we want to generate up to 3 fractional digits
    static unsigned int precision(T) { return 3; }
};

typedef boost::spirit::karma::real_generator<double, double3_policy<double> >
    double3_type;
double3_type const double3 = double3_type();
```

用于 使用普通字符缓冲区测量*Spirit.Karma*性能的代码：

```cpp
char buffer[256];
for (int i = 0; i < NUMITERATIONS; ++i) {
    char *p = buffer;
    generate(p
      , '[' << left_align(14)[double3] << left_align(14)[double3] << ']'
      , 12345.12345, 12345.12345);
    *p = '\0';
}
```

下表显示了使用不同编译器时收集的整体性能结果。所有时间均以`1e6`迭代（平台：Windows7、Intel Core Duo(tm) 处理器、2.8GHz、4GByte RAM）测量的秒为单位。有关结果的更具可读性的比较，请参见此[图](https://www.boost.org/doc/libs/1_52_0/libs/spirit/doc/html/spirit/karma/performance_measurements/numeric_performance/format_performance.html#spirit.karma.format_performance)。

**表 7. 多个项目序列的性能比较（所有时间都在 [s]，`1e6` 迭代）**

| Library                                                      | gcc 4.4.0 (32 bit) | VC++ 10 (32 bit) | Intel 11.1 (32 bit) | gcc 4.4.0 (64 bit) | VC++ 10 (64 bit) | Intel 11.1 (64 bit) |
| ------------------------------------------------------------ | ------------------ | ---------------- | ------------------- | ------------------ | ---------------- | ------------------- |
| sprintf                                                      | 1.725              | 1.892            | 1.903               | 1.469              | 1.608            | 1.493               |
| iostreams                                                    | 4.827              | 5.287            | 4.444               | 3.112              | 3.319            | 2.877               |
| [Boost.Format](https://www.boost.org/doc/libs/1_52_0/libs/format/index.html) | 5.881              | 7.089            | 5.801               | 5.455              | 5.254            | 4.164               |
| *Spirit.Karma*                                               | 1.942              | 1.242            | 0.999               | 1.334              | 0.758            | 0.686               |

**图 5. 多个项目序列的性能比较**

![多个项目序列的性能比较](https://www.boost.org/doc/libs/1_52_0/libs/spirit/doc/html/images/format_performance.png)

源自：https://www.boost.org/doc/libs/1_52_0/libs/spirit/doc/html/spirit/karma/performance_measurements/numeric_performance/format_performance.html

https://blog.csdn.net/guotianqing/article/details/100698323
