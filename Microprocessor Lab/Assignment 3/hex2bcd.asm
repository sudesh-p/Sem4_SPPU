%macro scall 4                    ;macro to take input and output
        mov rax,%1
        mov rdi,%2
        mov rsi,%3
        mov rdx,%4
        syscall
%endmacro

Section .data
msg1: db "Enter 4 Digit HEX Number: ",0x0A
len1: equ $-msg1
msg2:db "BCD Number : " 
len2: equ $-msg2
cnt :db 00H

Section .bss
ans resw 8
num resb 8

Section .text
global main
main:
 scall 1,1,msg1,len1
scall 0,0,num,8

mov rsi,num
call AtoH


mov rax,rbx
mov rbx,10 ; 10 in decimal base
mov rdi,ans+7
loop:
mov rdx,0
div rbx
add dl,30h
mov [rdi],dl
dec rdi

cmp rax,0
jne loop



scall 1,1,msg2,len2
scall 1,1,ans,8
;add rax,30
;mov word[ans],ax
;dec cx
;jnz ploop


;scall 1,1,ans,8

mov rax,60
mov rdi,0
syscall



AtoH:		;result hex no is in bx
mov byte[cnt],04H
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

