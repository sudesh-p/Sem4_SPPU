%macro scall 4
mov rax,%1
mov rdi,%2
mov rsi,%3
mov rdx,%4
syscall
%endmacro

Section .data
 
title: db 0x0A,"----ASSIGNMENT 5 -----", 0x0A
title_len: equ $-title
openmsg: db "File Opened Successfully",0x0A
openmsg_len: equ $-openmsg
errormsg: db "Failed to open file", 0x0A
errormsg_len: equ $-errormsg

fname: db 'A.txt', 0

Section .bss
global cnt1,cnt2,cnt3,buffer,bufferlen,fdis
cnt1: resb 8
cnt2: resb 8
cnt3: resb 8
bufferlen: resb 8
buffer: resb 200
fdis: resb 8	;for storing file descriptor value

Section .text
global main
extern CSPACE,CNEWLINE,CCHAR
main:
scall 1,1,title,title_len
scall 2,fname,2,777  ;Opening file

mov qword[fdis],rax 	;RAX contains file descriptor value
bt rax,63	;63rd bit is +ve(0) if file is successfull opened else it is -ve (1)
jc next

scall 1,1,openmsg,openmsg_len
jmp next1

next:
	scall 1,1,errormsg,errormsg_len
	jmp EXIT

next1:
	scall 0,[fdis],buffer,200	;reading contents of file in buffer
	;rax contains actual number of bytes read
	mov qword[bufferlen],rax
	mov qword[cnt1],rax ;cnt1 for using in cspace procedure
	mov qword[cnt2],rax ;;cnt2 for using in cnewline procedure
	mov qword[cnt3],rax ;;cnt3 for using in cchar procedure


 call CCHAR
 call CSPACE
;scall 1,1,title,title_len
 call CNEWLINE

;scall 1,1, title,title_len
 
mov rax,3
mov rdi,fname
syscall 

EXIT:
mov rax,60
mov rdi,0
syscall
