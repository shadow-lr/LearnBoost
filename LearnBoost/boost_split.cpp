#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>

using namespace std;

void Content()
{
	string test = "i am a student,you are a teacher!";
	vector<string> vec;
	boost::split(vec, test, boost::is_any_of("t,"), boost::token_compress_on);
	cout << "****** token_compress_on ******" << "\n";
	for (auto num : vec)
	{
		cout << num << endl;
	}
	vec.clear();
	cout << "****** token_compress_off ******" << "\n";
	boost::split(vec, test, boost::is_any_of("t,"), boost::token_compress_off);
	for (auto num : vec)
	{
		cout << num << endl;
	}
}