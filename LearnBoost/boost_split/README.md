## boost::split

对于场景：string s = "123456"，用"3","4"切分，默认情况下（boost::token_compress_off），切分结果为12，空，56，注意，这里的空不是空格。而是"3"，"4"之间的空。如果不想要这个空，指定boost::token_compress_on就行了。
boost::token_compress_on的意思就是说，以"3"，"4"，切分，当出现34的时候，就把34压缩成整体，用"34"切分。

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

