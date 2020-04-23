%macro scall 4                    ;macro to take input and output
        mov rax,%1
        mov rdi,%2
        mov rsi,%3
        mov rdx,%4
        syscall
%endmacro

Section .data
msg1:db "Enter 5 Digit BCD Number: ",0x0A
len1: equ $-msg1
msg2: db "Hex Number: ",0x0A
len2:equ $-msg2
cnt :db 00H
cnt2:db 00H

Section .bss
num:resb 6
ans: resb 4
result:resb 8

Section .text
global main
main:
scall 1,1,msg1,len1
scall 0,0,num,6

mov rsi,num
call AtoH

mov edx,ebx ;copy conveted number to edx


MOV eax,00H
mov ebx,00H
mov al,dl

AND AL,0FH
mov Bl,01H
MUL Bl
ADD dword[ans],eax
ROR EDX,4

MOV EAX,00H
mov ebx,00H
MOV AL,DL
AND AL,0FH
MOV BL,0AH
MUL BL
ADD DWORD[ans],EAX
ROR EDX,4

MOV EAX,00H
mov ebx,00H
MOV AL,DL
AND AL,0FH
MOV BL,64H
MUL BL
ADD DWORD[ans],EAX
ROR EDX,4

MOV EAX,00H
mov ebx,00H
MOV AL,DL
AND AL,0FH
MOV BX,03E8H
MUL BX
ADD DWORD[ans],	EAX
ROR EDX,4

MOV EAX,00H
mov ebx,00H
MOV AL,DL
AND AL,0FH
MOV BX,2710H  ;FIFTH DIGIT (100000 dECIMAL)
MUL BX
ADD DWORD[ans],EAX
	
MOV EDX, DWORD[ans]
MOV RDI,result
call HtoA

scall 1,1,msg2,len2
scall 1,1,result,8
mov rax,60
mov rdi,0
syscall

AtoH:		;result hex no is in ebx
mov byte[cnt],05H
mov ebx,00H
hup:
rol ebx,04
mov al,byte[rsi]
cmp al,39H
JBE HNEXT
SUB al,07H
HNEXT:
sub al,30H
add bl,al
INC rsi
DEC byte[cnt]
JNZ hup
ret

HtoA:	;hex_no to be converted is in dx //result is stored in rdi/user defined variable
mov byte[cnt2],08H
aup:
rol EDX,04
mov cl,dl
and cl,0FH
CMP CL,09H
jbe ANEXT
ADD cl,07H
ANEXT: 
add cl, 30H
mov byte[rdi],cl
INC rdi
dec byte[cnt2]
JNZ aup

;mov rax,1
;mov rdi,1
;mov rcx,result
;mov rdx,4
;syscall
ret

