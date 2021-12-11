#include <iostream>
#include <string>

#include <boost/version.hpp>
#include <boost/config.hpp>

using namespace std;

template<class T>
void print_line(T && line)
{
	cout << line << endl;
}

//int main()
//{
//	string boost_version = "BOOST_VERSION : " + to_string(BOOST_VERSION);
//	string boost_lib_version = "BOOST_LIB_VERSION" + static_cast<string>(BOOST_LIB_VERSION);
//	string boost_platform = "BOOST_PLATFORM : " + static_cast<string>(BOOST_PLATFORM);
//	string boost_compiler = "BOOST_COMPILER" + static_cast<string>(BOOST_COMPILER);
//	string boost_stdlib = "BOOST_STDLIB" + static_cast<string>(BOOST_STDLIB);
//
//	print_line(boost_version);
//	print_line(boost_lib_version);
//	print_line(boost_platform);
//	print_line(boost_compiler);
//	print_line(boost_stdlib);
//
//	// select all file
//	// choose option 
//	// add content in this
//	// run code
//}