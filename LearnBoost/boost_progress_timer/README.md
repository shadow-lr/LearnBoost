### progress_timer

progress_timer也是一个计时器，继承自timer,会在析构时自动输出时间，省去了timer手动调用elapsed()的工作。

```cpp
#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/timer.hpp>
#include <boost/progress.hpp>
using namespace std;
using namespace boost;

int main()
{  
	//测试progress_timer
    progress_timer pt;

    return 0;
}
```

这样，程序退出main函数作用域导致pt析构时，会自动输出流逝的时间。

缺点：精度不够，Linux下单位为s。



### date_time

date_time类，可以满足绝大多数程序对时间的要求，但是不能处理1400年以前的时间，但是它的优点是很明显的，它允许我们更加自由地去操纵时间。

date_time实一个全面且灵活的日期时间库，基于公历（格里高利历法）。可以提供与时间相关的各种所需功能，date_time库还支持无限时间和无效时间在生活中有用的概念，还能与C语言中时间结构tm进行转换。

date_time库中用枚举special_values定义了特殊的时间概念，并位于命名空间boost::date_time中，以下一些枚举值：

not_a_date_time : 表示无效时间

neg_infin : 表示负的无限大

pos_infin : 表示正的无限大

min_date_time ：可表示的最小日期

max_date_time ：可表示的最大日期

not_special : 表示正常日期

NumSpecialValues: 表示数值特殊值

date_time类的日期基于格里高利历，支持的日期范围为“1400-01-01”到“9999-12-31”

首先来看一下date类，date类时date_time处理日期的核心类，以天为单位表示时间点概念。它的类如下：

```cpp
template<class T, class calendar, class duration_type_>
class mydate{
    public:
    //constructor
    constexpr date(year_type y, month_type m, day_type d);
    constexpr date(const ymd_type& ymd);
    //let the compiler write copy, assignment, and destructor
    //return the year month or day
    constexpr year_type        year() const;
    constexpr month_type       month() const;
    constexpr day_type         day() const;
    constexpr day_of_week_type day_of_week() const;
    constexpr ymd_type         year_month_day() const;
    //date compare operator
    constexpr bool operator<(const date_type& rhs)  const;
    constexpr bool operator==(const date_type& rhs) const;
    //! check to see if date is a special value
    constexpr bool is_special()const;
    //! check to see if date is not a value
    constexpr bool is_not_a_date()  const;
    //! check to see if date is one of the infinity values
    constexpr bool is_infinity()  const;
    //! check to see if date is greater than all possible dates
    constexpr bool is_pos_infinity()  const;
    //! check to see if date is greater than all possible dates
    constexpr bool is_neg_infinity()  const;
    //! return as a special value or a not_special if a normal date
    constexpr special_values as_special()  const;
    //day operator
    constexpr duration_type operator-(const date_type& d) const;
    constexpr date_type operator-(const duration_type& dd) const;
    constexpr date_type operator-=(const duration_type& dd);
    constexpr date_rep_type day_count() const;
    //allow internal access from operators
    constexpr date_type operator+(const duration_type& dd) const;
    constexpr date_type operator+=(const duration_type& dd);
    //see reference
  protected:
    constexpr explicit date(date_int_type days) ;
    constexpr explicit date(date_rep_type days) ;
    date_int_type days_;
};
```

测试用例：

```cpp
#include <iostream>
#include <ctime>
#include <cstring>
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;
int main(int argc,char *argv[])
{
    //cretate date
    date d1; //not a date time
    std::cout << d1 << std::endl;
    date d2(2020,01,02);
    date d3(2020,Jan,20);
    date d4(d3);
    //from string
    date d5 = from_string("1998-03-24");
    std::cout << d5 << std::endl;
    //from underlimited string no split char
    date d6(from_undelimited_string("20111102"));
    std::cout << d6 << std::endl;
    //get current day
    date d7(day_clock::local_day_ymd());
    std::cout << d7 << std::endl;
    std::cout << "local day : " << day_clock::local_day() <<
    " univeral day : " << day_clock::universal_day() << std::endl;
    //to string
    std::cout << "----------to string------------" << std::endl;
    std::cout << "simple string : " <<to_simple_string(d2) << std::endl;
    std::cout <<  "iso  string : "<<to_iso_string(d2) << std::endl;
    std::cout << "sql string : " << to_sql_string(d2) << std::endl;
    std::tm ctm = to_tm(d2);
    std::cout <<  "c style tm :"<< asctime(&ctm) << std::endl;
    //operator
    std::cout << "----------operator---------" << std::endl;
    years year(4);
    months m(1);
    days day(1);
    std::cout << d2 <<std::endl;
    d2 += year;
    d2 += m;
    d2 += day;
    std::cout << d2 <<std::endl;
    d2 -= m;
    d2 += day;
    std::cout << d2 <<std::endl;
    //year month and day
    std::cout << "---------------output---------" << std::endl;
    std::cout << "year : " << d2.year() << std::endl;
    std::cout << "month : " << d2.month() << std::endl;
    std::cout << "day : " << d2.day() << std::endl;
    std::cout << " the " << d2.day_of_year() << std::endl;
    //week
    std::cout << "the " <<d2.week_number() << " weeks" << std::endl;
    std::cout << "the " << d2.day_of_week() << std::endl;
    //julian_day
    std::cout << "modjulian day : " << d2.modjulian_day() << std::endl;
    std::cout << "julian day : " << d2.julian_day() << std::endl;
    std::cout << "day numbers : " << d2.day_count() << std::endl;
    std::cout << "day numbers : " << d2.day_number() << std::endl;
    //special value
    std::cout << "------------------special date-------------" << std::endl;
    std::vector<date> vd;
    vd.push_back(date(neg_infin));
    vd.push_back(date(pos_infin));
    vd.push_back(date(min_date_time));
    vd.push_back(date(max_date_time));
    vd.push_back(date(not_a_date_time));
    for(auto const& d : vd){
        std::cout << d << std::endl;
    }
    return 0;
}
```

