%macro scall 4
mov rax,%1
mov rdi,%2
mov rsi,%3
mov rdx,%4
syscall
%endmacro

Section .data

spacemsg:db 0x0A,"Spaces = " 
spacemsg_len: equ $-spacemsg
newlinemsg:db  0x0A, "Return(Enter) chars = "
newlinemsg_len: equ $-newlinemsg
chms:db 0x0A,"Character count: "
chms_len: equ $-chms
chinput: db 0x0A,"Character Input: ",
chinput_len: equ $-chinput
scnt: db 00H
ncnt: db 00H
chcnt: db 00H
hexcnt2: db 00H

Section .bss
extern cnt1,cnt2,cnt3,buffer,bufferlen
spacecount: resb 2
ch1:resb 2
newlinecount: resb 2
chcount: resb 2
Section .text
global main2
global CSPACE, CNEWLINE,CCHAR
main2:

mov rax,60
mov rdi,0
syscall

CSPACE:
 mov rsi,buffer
up:
 mov al,byte[rsi]
 cmp al,20H
 je next2
 inc rsi
 dec qword[cnt1]
 jnz up
 jmp next3

next2:
 inc byte[scnt]
 inc rsi;
 dec qword[cnt1]
 jnz up

next3:
 mov bl, byte[scnt]
 mov rdi, spacecount
 call HtoA
 
 scall 1,1, spacemsg,spacemsg_len
 scall 1,1,spacecount,2

ret

CNEWLINE:
 mov rsi,buffer
up2:
 mov al,byte[rsi]
 cmp al,0x0A
 je next4
 inc rsi
 dec qword[cnt2]
 jnz up2
 jmp next5

next4:
 inc byte[ncnt]
 inc rsi;
 dec qword[cnt2]
 jnz up2

next5:
 mov bl, byte[ncnt]
 mov rdi, newlinecount
 call HtoA
 
 scall 1,1, newlinemsg,newlinemsg_len
 scall 1,1,newlinecount,2

ret

CCHAR:
 scall 1,1,chinput,chinput_len
 scall 0,0,ch1,2
 mov rsi,buffer
up3:
 mov al,byte[rsi]
 cmp al,byte[ch1]
 je nextl
 inc rsi
 dec qword[cnt3]
 jnz up3
 jmp next7

nextl:
 inc byte[chcnt]
 inc rsi;
 dec qword[cnt3]
 jnz up3

next7:
 mov bl, byte[chcnt]
 mov rdi, chcount
 call HtoA
 scall 1,1,chms,chms_len
 scall 1,1,chcount,2

ret
;------HEX TO ASCII CONVERSION METHOD FOR VALUE(2 DIGIT) ----------------
HtoA: ;hex_no to be converted is in ebx //result is stored in rdi/user defined variable
mov byte[hexcnt2],02H
aup1:
rol bl,04
mov cl,bl
and cl,0FH
CMP CL,09H
jbe ANEXT1
ADD cl,07H
ANEXT1: 
add cl, 30H
mov byte[rdi],cl
INC rdi
dec byte[hexcnt2]
JNZ aup1
ret
