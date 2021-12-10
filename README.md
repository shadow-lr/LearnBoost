# LearnBoost
Learn boost c++

## boost::split
���ڳ�����string s = "123456"����"3","4"�з֣�Ĭ������£�boost::token_compress_off�����зֽ��Ϊ12���գ�56��ע�⣬����Ŀղ��ǿո񡣶���"3"��"4"֮��Ŀա��������Ҫ����գ�ָ��boost::token_compress_on�����ˡ�
boost::token_compress_on����˼����˵����"3"��"4"���з֣�������34��ʱ�򣬾Ͱ�34ѹ�������壬��"34"�з֡�

```cpp

#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
 
using namespace std;
int main()
{
    string test = "i am a student,you are a teacher!";
    vector<string> vec;
    boost::split(vec, test,boost::is_any_of(" ,"), boost::token_compress_on);
    for(int i = 0; i < vec.size(); ++i)
    {
        cout<<vec[i]<<endl;
    }
    return 0;
}
```