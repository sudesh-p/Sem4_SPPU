%macro scall 4
mov rax,%1
mov rdi,%2
mov rsi,%3
mov rdx,%4
syscall
%endmacro

Section .data
title: db 0x0A,"----Commands -----", 0x0A
	db "1. Copy ",0x0A
	db "2. Type ",0x0A
	db "3. Delete ",0x0A
	db "4. Exit ",0x0A
	db "Enter Your choice", 0x0A
title_len: equ $-title
openmsg: db "File Opened Successfully",0x0A
openmsg_len: equ $-openmsg
closemsg: db "File Closed Successfully",0x0A
closemsg_len: equ $-closemsg
errormsg: db "Failed to open file", 0x0A
errormsg_len: equ $-errormsg
delmsg: db "Deleted File", 0x0A
delmsg_len: equ $-delmsg
typemsg: db "=-----File Contents ----=",0x0A
typemsg_len: equ $-typemsg
;f1name: db 'file1.txt', 0
;f2name: db 'file2.txt', 0
;f3name: db 'file3.txt',0
filenmsg: db "ENter File name: "
filen_len: equ $-filenmsg
Section .bss
buffer: resb 200
bufferlen:resb 8
cnt1:resb 8
fdis:resb 8
choice: resb 2
f1name: resb 20
f2name: resb 20
f3name: resb 20
Section .text
global main
main:
scall 1,1,title,title_len
scall 0,0,choice,2
;------------- CHOOSE OPTION --------------------------
;compare choice here
cmp byte[choice],'1' ;if choice is to display content
je COPY
cmp byte[choice],'2'
je TYPE	
cmp byte[choice],'3'
je DELETE
cmp byte[choice],'4'
je EXIT

COPY:
	scall 1,1,filenmsg,filen_len
	scall 0,0, f1name, 20
	dec rax
	mov byte[f1name+rax],0
	scall 2,f1name,2,777  ;Opening file

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
	mov qword[cnt1],rax 
	
	;Closing file1
	mov rax,3
	mov rdi,f1name
	syscall
	scall 1,1,closemsg,closemsg_len




;-------------------FILE 2 ------------------
	scall 1,1,filenmsg,filen_len
	scall 0,0, f2name, 20
	dec rax
	mov byte[f2name+rax],0

scall 2,f2name,2,777
	mov qword[fdis],rax 	;RAX contains file descriptor value
	bt rax,63	;63rd bit is +ve(0) if file is successfull opened else it is -ve (1)
	jc next3

	scall 1,1,openmsg,openmsg_len
	jmp next21

next3:
	scall 1,1,errormsg,errormsg_len
	jmp EXIT

next21:
	scall 1,qword[fdis],buffer,qword[bufferlen]  ;writing to file2.txt

	mov rax,3
	mov rdi,f2name
	syscall
	scall 1,1,closemsg,closemsg_len
	jmp main

TYPE:scall 1,1,filenmsg,filen_len
	scall 0,0, f2name, 20
	dec rax
	mov byte[f2name+rax],0

	scall 2,f2name,2,777  ;Opening file
	mov qword[fdis],rax 	;RAX contains file descriptor value
	bt rax,63	;63rd bit is +ve(0) if file is successfull opened else it is -ve (1)
	jc tnext

	scall 1,1,openmsg,openmsg_len
	jmp tnext1

tnext:
	scall 1,1,errormsg,errormsg_len
	jmp EXIT

tnext1:
	scall 0,[fdis],buffer,200	;reading contents of file in buffer
	mov qword[bufferlen],rax
	scall 1,1, typemsg,typemsg_len
	scall 1,1, buffer,qword[bufferlen]

	;Closing file2
	mov rax,3
	mov rdi,f2name
	syscall
	scall 1,1,closemsg,closemsg_len
JMP main

DELETE:
scall 1,1,filenmsg,filen_len
	scall 0,0, f3name, 20
	dec rax
	mov byte[f3name+rax],0
	mov rax,87 ;System CALL FOR ULINK
	mov rdi,f3name
	syscall
	scall 1,1, delmsg,delmsg_len
jmp main

EXIT:
	mov rax,60
	mov rdi,0
	syscall
