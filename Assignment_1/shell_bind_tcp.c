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
    srvFd.sin_family = AF_INET;							//family for IP address
    srvFd.sin_port = htons(8888);						//port number (msb first)
    srvFd.sin_addr.s_addr = htonl(INADDR_ANY);			//accepts connections to all the IPs of the machine
 	
	//Sys Call - create socket descriptor
    int srvSoc = socket(AF_INET, SOCK_STREAM, 0);
 	
	//Sys Call - assign address/port to socket
    bind(srvSoc, (struct sockaddr *) &srvFd, 16);
	 	
	//Sys Call - accept incoming conection - just let max number of connections = 1 
    listen(srvSoc, 1);
 	
	//Sys Call -  allow incoming connection attempt on a socket
    int clientSoc = accept(srvSoc, NULL, NULL);
 
	//Sys Call - redirect stdout to the socket - when /bin/ls is executed output will use this socket instead of the standard file descriptors.
    dup2(clientSoc, 1);
	 	
	//Sys Call - execute /bin/ls, execvc("address of where /bin/ls", "address of array of arg strings")
	char *argv[] = {"/bin/ls",NULL};
    execve(argv[0], &argv[0], NULL);
	
    return 0;
}
