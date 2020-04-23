%macro scall 4
mov rax,%1
mov rdi,%2
mov rsi,%3
mov rdx,%4
syscall
%endmacro

Section .data
title: db 0x0A,"----Commands -----", 0x0A
	db "Numbers are :  ",0x0A
	db "102.56, 104.25, 235.26, 205.04, 326.01", 0x0A
title_len: equ $-title
dot:db "."
meanmsg: db 0x0A,"Mean is: ",0x0A
meanmsg_len:equ $-meanmsg
varmsg:db 0x0A, "Variance is : ",0x0A
varmsg_len: equ $-varmsg
sdmsg: db 0x0A,"Standard Deviation is :", 0x0A
sdmsg_len: equ $-sdmsg
array: dd 102.56,104.25,235.26,205.04,326.01
arraycnt: dw 05
hesc: dq 100
cnt2: db 02H

Section .bss
buffer: rest 1 
disbuffer: resb 2
mean:resd 1
variance:resd 1

Section .text
global _start
_start:
scall 1,1,title,title_len
;========= Mean Calculation ==================
mov rcx, 00
mov cx, word[arraycnt] ;//total count of numbers
FINIT		;initialize 80367 ndp
FLDZ		;load 0 to stack
mov rsi,array	;starting location
UP:
FADD dword[rsi]
add rsi,4	;-_- double word= 4 bytes
loop UP

FIDIV word[arraycnt] ;divide by total
FST dword[mean]		;store to mean
scall 1,1,meanmsg,meanmsg_len
CALL DISPLAY

;========= Variance Calculation ==================
scall 1,1,varmsg,varmsg_len
;mov dword[variance],00
FLDZ
mov rcx,00
mov cx, word[arraycnt]
mov rsi,array
VUP:
FLD dword[rsi]	
FSUB  dword[mean] 	;(number-mean)
FST ST1			;store to ST1
FMUL ST0,ST1		; squaring above result
FADD dword[variance]	;add to previous iteration answer
FST dword[variance]	;store that ans to variance
add rsi,4		;-_- double word= 4 bytes
loop VUP
FLD dword[variance]
FIDIV word[arraycnt]

FST dword[variance]
CALL DISPLAY

;========= Standard Deviation Calculation ==================
scall 1,1, sdmsg,sdmsg_len
FLD dword[variance]
FSQRT	;use square root instruction
CALL DISPLAY

EXIT:
mov rax,60
mov rdi,0
syscall

;========= Display Procedure ==================
DISPLAY:
FIMUL dword[hesc] ;multiply by 100 to remove decimal point.Point will be printed explicitely
FBSTP [buffer] ;bcd store and pop to buffer
xor rcx,rcx 	;clear rxs or use mov rcx,00
mov cx,9 	; for displaying digits(18) on RHS of decimal point
mov rsi,buffer+9 ;GO to MSB  Byte
TOP:
push rcx ;push beacause value will be changed in HtoA method
push rsi

mov bl,byte[rsi] ;Load 1 byte=2 digits for ascii conversion
call HtoA	 ;convert and print
pop rsi
dec rsi
pop rcx
dec rcx
jnz TOP
scall 1,1,dot,1 ;PRINT DECIMAL POINT

;printing digits after decimal point
mov rsi,buffer
mov bl,byte[rsi]	
call HtoA
ret

;------HEX TO ASCII CONVERSION METHOD ----------------
HtoA:	;hex_no to be converted is in bx //result is stored in rdi/user defined variable
mov rdi,disbuffer
mov byte[cnt2],2H
aup:
rol bl,04
mov cl,bl
and cl,0FH
cmp cl,09H
jbe ANEXT
ADD cl,07H
ANEXT: 
add cl, 30H
mov byte[rdi],cl
INC rdi
dec byte[cnt2]
JNZ aup
scall 1,1,disbuffer,2
ret

