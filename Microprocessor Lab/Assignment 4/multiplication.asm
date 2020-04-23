%macro scall 4                    ;macro for system call execution
        mov rax,%1
        mov rdi,%2
        mov rsi,%3
        mov rdx,%4
        syscall
%endmacro

Section .data
title: db "1. Multiplication using successive addition", 0x0A
	db "2. Using ADD and SHIFT ",0x0A
	db "3. Exit", 0x0A	
	db "Enter your choice: ",0x0A
len: equ $-title
msg1:db "Enter 1st Number: ",0x0A
len1: equ $-msg1
msg2: db "Enter 2nd Number: ", 0x0A
len2: equ $-msg2
ans_msg: db "Answer: ", 0x0A
ans_len: equ $-ans_msg
cnt :db 00H
cnt2:db 00H
newline:db 0x0A
bye: db 0x0A,"***GOOD BYE***",0x0A
bye_len:equ $-bye
;----------------------------------------------------------
Section .bss
choice resb 4
num1 resb 4
num2 resb 4
hnum1: resb 4
hnum2:resb 4
result: resb 4
;----------------------------------------------------------
Section .text
global main
main:
;print menu by macro scall
scall 1,1,title,len

;read choice
scall 0,0,choice,2

;compare choices to act as a switch case
cmp byte[choice],'1'  
JE  SUADD
cmp byte[choice],'2'
je  ADDSHIFT

cmp byte[choice],'3'
jae EXIT


;=========================================================
SUADD:
scall 1,1, msg1,len1

scall 0,1,num1,3


mov rsi,num1 ;;no1 to converted in hex
call AtoH
mov [hnum1],bl

;num 2 accept and conversion to hex
scall 1,1,msg2,len2

scall 0,0,num2,3

mov rsi,num2 ;;no to converted
call AtoH
mov [hnum2],bl

;addition process starteed
mov bl,[hnum1]
mov cl,[hnum2]
mov ax,00H
sup:add al,bl
dec cl;
jnz sup

;convert result from hex to ascii
mov dx,ax
mov rdi, result
call HtoA

scall 1,1,ans_msg,ans_len

scall 1,1,result,2

scall 1,1,newline,1

jmp main
;==========================================================
ADDSHIFT:
scall 1,1,msg1,len1
scall 0,1,num1,4
mov rsi,num1 ;;no1 to converted in hex
call AtoH
mov [hnum1],bl

;num 2 accept and conversion to hex
scall 1,1,msg2,len2
scall 0,0,num2,4
mov rsi,num2 ;;no to converted
call AtoH
mov [hnum2],bl

mov byte[cnt],08
mov al,00
mov bl,[hnum1]
mov cl,[hnum2]
TOP:
SHL al,1
ROL bl,1
JNC BELOW
ADD al,cl
BELOW:
dec byte[cnt]
JNZ TOP

;convert result from hex to ascii
mov dx,ax
mov rdi, result
call HtoA

scall 1,1,ans_msg,ans_len

scall 1,1,result,2
scall 1,1,newline,1
jmp main

EXIT:  
scall 1,1,bye,bye_len
mov rax,60		;exit code
mov rdi,0
syscall


AtoH:		;result hex no is in bx
mov byte[cnt],02H
mov bl,00H
hup:
rol bl,04
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

HtoA:		;hex_no to be converted is in dx //result is stored in rdi/user defined variable
mov byte[cnt2],02H
aup:
rol dl,04
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



