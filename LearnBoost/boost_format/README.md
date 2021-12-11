## boost_format
formatû��snprintf�죬���������Ͱ�ȫ�ġ���ʹ��streams������������Բ�������ڴ�����������

format������ʹ�÷��һ�������� printf����һ��ʹ��ռλ����������c#��

##### ��������ʽ

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

format��ʹ����printf���ƣ�ʹ�� %f ��ʽ��һ����������Ĭ�ϵľ�����6λС����

ʹ�ø�������ݿ�����֤������ۣ��磺

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

ʹ�� **%1%** ռλ��ʱ������ֵ�ϴ�ʱ����ʹ�ÿ�ѧ�����������6-7���ַ�����ʱ��ʹ�ã���

##### ���ڿ�ѧ������

```cpp
boost::format scinotation("Do we use scientific? '%1%'\n");// %lluʱҲ����ʾ��ѧ������
 
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

���⣬**��ʵ��ʹ���У����ʹ���˲�ƥ��ı�Ƿ�ʱ����ʹ����%llu, ��ʵ����ֵȴ��doubleʱ��Ҳ���Կ�ѧ��������ʾ��**

����ʹ�� %e ��ʾָ���Կ�ѧ��������ʾ��

##### ��ʽ����

��ʽ���Ƶ��﷨Ϊ��`%[N$][flags][width][.precision]type-char`���磺

#### ����ʾ��

```cpp
// ֱ�����
cout << boost::format("%s") % "this is what i want" << endl; 

// ��� string
string s;
s = str(boost::format("%s") % "this is what i want");
cout << s << endl;

// ʹ�� formater
boost::format fmt("%s");
fmt % "this is what i want";
string s = fmt.str();
cout << s << endl;

// ռλ��
cout << boost::format("%1%") % "this is what i want" << endl;
```

#### �쳣����

format �쳣ʱ��throw �쳣��Ϣ������Ҫʹ��try���鴦���쳣���������Ĭ�ϻ���ֹ���磺

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





### �Ƚ϶�����������е�����

��Щ���ܲ�����һϵ�в�ͬ��Ŀ�ĸ�ʽΪ���ģ�����`double` ʹ�ò�ͬ��ͷ�����2 ��������������Ƚ�����Щʾ��������ִ��ʱ�䡣���ǱȽ� using `sprintf`��C++ iostreams�� [Boost.Format](https://www.boost.org/doc/libs/1_52_0/libs/format/index.html)�� *Spirit.Karma*��

�й����ܲ��Ե�����Դ���룬��μ��˴���[format_performance.cpp](https://www.boost.org/doc/libs/1_52_0/libs/spirit/optimization/karma/format_performance.cpp)�����в�������ͨ��`1e6` ��ÿ�ָ�ʽ���ͽ��е�������ɵģ�NUMITERATIONS ����Ϊ`1e6`����

���ں��� sprintf ���ܵĴ��룺

```cpp
char buffer[256];
for (int i = 0; i < NUMITERATIONS; ++i) {
    sprintf(buffer, "[%-14.3f%-14.3f]", 12345.12345, 12345.12345);
}
```

���ں�����׼ iostream ���ܵĴ��룺

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

���ں���[Boost.Format](https://www.boost.org/doc/libs/1_52_0/libs/format/index.html)���ܵĴ��룺

```cpp
std::string generated;
boost::format outformat("[%-14.3f%-14.3f]");
for (int i = 0; i < NUMITERATIONS; ++i)
    generated = boost::str(outformat % 12345.12345 % 12345.12345);
```

���´�����ʾ������*Spirit.Karma* ���ܲ���ʹ�õ�ͨ�ö��壬�������У�

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

���� ʹ����ͨ�ַ�����������*Spirit.Karma*���ܵĴ��룺

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

�±���ʾ��ʹ�ò�ͬ������ʱ�ռ����������ܽ��������ʱ�����`1e6`������ƽ̨��Windows7��Intel Core Duo(tm) ��������2.8GHz��4GByte RAM����������Ϊ��λ���йؽ���ĸ��߿ɶ��ԵıȽϣ���μ���[ͼ](https://www.boost.org/doc/libs/1_52_0/libs/spirit/doc/html/spirit/karma/performance_measurements/numeric_performance/format_performance.html#spirit.karma.format_performance)��

**�� 7. �����Ŀ���е����ܱȽϣ�����ʱ�䶼�� [s]��`1e6` ������**

| Library                                                      | gcc 4.4.0 (32 bit) | VC++ 10 (32 bit) | Intel 11.1 (32 bit) | gcc 4.4.0 (64 bit) | VC++ 10 (64 bit) | Intel 11.1 (64 bit) |
| ------------------------------------------------------------ | ------------------ | ---------------- | ------------------- | ------------------ | ---------------- | ------------------- |
| sprintf                                                      | 1.725              | 1.892            | 1.903               | 1.469              | 1.608            | 1.493               |
| iostreams                                                    | 4.827              | 5.287            | 4.444               | 3.112              | 3.319            | 2.877               |
| [Boost.Format](https://www.boost.org/doc/libs/1_52_0/libs/format/index.html) | 5.881              | 7.089            | 5.801               | 5.455              | 5.254            | 4.164               |
| *Spirit.Karma*                                               | 1.942              | 1.242            | 0.999               | 1.334              | 0.758            | 0.686               |

**ͼ 5. �����Ŀ���е����ܱȽ�**

![�����Ŀ���е����ܱȽ�](https://www.boost.org/doc/libs/1_52_0/libs/spirit/doc/html/images/format_performance.png)

Դ�ԣ�https://www.boost.org/doc/libs/1_52_0/libs/spirit/doc/html/spirit/karma/performance_measurements/numeric_performance/format_performance.html

https://blog.csdn.net/guotianqing/article/details/100698323
