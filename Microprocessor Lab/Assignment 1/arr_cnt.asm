Section .data
title: db "Count of positive and negavite Numbers in an array" ,0x0A
title_len: equ $-title
pos_msg : db "Positive count: " ,0x0A
pos_len: equ $-pos_msg
neg_msg : db "Negative count :" ,0x0A
neg_len: equ $-neg_msg
newline: db 0x0A

array: dw 1000H, -121H,0045H, 34H,-12H,121H, -4543H,98H, -8999H  ;array declaration and initialization
arrcnt: equ 9 ;static array count
pcnt: dw 0   ;positive number count
ncnt dw 0	;negative number count

Section .bss
dis_buffer :resb 2

Section .text

;displaying title
mov rax, 1
mov rdi, 1
mov rsi, title
mov rdx, title_len
syscall

;initalizing array  start address
mov rsi, array
mov rcx, arrcnt
UP:
bt word[rsi], 15  ; 15 is sign bit || bt- bit test
JNC PNEXT
inc byte[ncnt]
JMP PSKIP

PNEXT: inc byte[pcnt]

PSKIP: 
inc rsi
inc rsi
loop UP

;Positive count msg display 
mov rax, 1
mov rdi,1
mov rsi, pos_msg
mov rdx,pos_len
syscall

 mov bl,[pcnt]

CALL HEX_ASCII

;newline
mov rax, 1
mov rdi,1
mov rsi, newline
mov rdx,1
syscall

mov rax, 1
mov rdi, 1
mov rsi, neg_msg
mov rdx, neg_len
syscall

mov bl,[ncnt]
CALL HEX_ASCII

;newline
mov rax, 1
mov rdi,1
mov rsi, newline
mov rdx,1
syscall

mov rax, 60
mov rdi, 0
syscall



;hex to ascii procedure
HEX_ASCII:
mov rcx, 2
mov rdi ,dis_buffer
dup:
rol bl, 04
mov al,bl
and al, 0fh
cmp al,09h
jbe next
add al, 07h
next:
add al,30h
mov [rdi],al
inc rdi
;dec rcs
loop dup

mov rax, 1
mov rdi, 1
mov rsi, dis_buffer
mov rdx, 2
syscall

ret

