%macro scall 4
mov rax,%1
mov rdi,%2
mov rsi,%3
mov rdx,%4
syscall
%endmacro

Section .data
title: db 0x0A,"***** BuBbLe SoRt *****", 0x0A
title_len: equ $-title
openmsg: db "File Opened Successfully",0x0A
openmsg_len: equ $-openmsg
closemsg: db "File Closed Successfully",0x0A
closemsg_len: equ $-closemsg
errormsg: db "Failed to open file", 0x0A
errormsg_len: equ $-errormsg
sortmsg: db "After Sorting "
sortmsg_len: equ $-sortmsg
f1name: db 'file.txt', 0

Section .bss
buffer: resb 200
bufercpy: resb 200
bufferlen:resb 8
cnt1:resb 8
cnt2: resb 8
fdis:resb 8

Section .text
global _start
_start:
	scall 1,1,title,title_len
	scall 2,f1name,2,777  ;Opening file

	mov qword[fdis],rax 	;RAX contains file descriptor value
	bt rax,63	;63rd bit is +ve(0) if file is successfull opened else it is -ve (1)
	jc ERROR

	scall 1,1,openmsg,openmsg_len
	jmp next1

ERROR:
	scall 1,1,errormsg,errormsg_len
	jmp EXIT

next1:
	scall 0,[fdis],buffer,200	;reading contents of file in buffer
	;rax contains actual number of bytes read
	mov qword[bufferlen],rax ;for rounds
	mov qword[cnt1],rax 
	mov qword[cnt2],rax 

	
BUBBLE:
mov al,byte[cnt2]
	mov byte[cnt1],al
	dec byte[cnt1]

mov rsi,buffer
mov rdi,buffer+1

loop:
mov bl,byte[rsi]
mov cl,byte[rdi]
	cmp bl,cl
	ja SWAP
	inc rsi
	inc rdi
	dec byte[cnt1]
	jnz loop
dec byte[bufferlen]
jnz BUBBLE
jmp END
SWAP:
	;mov al,byte[rsi]
	mov byte[rsi],cl
	mov byte[rdi],bl
	inc rsi
	inc rdi
	dec byte[cnt1]
	jnz loop
dec byte[bufferlen]
jnz BUBBLE

END:
scall 1,1,sortmsg,sortmsg_len
scall 1,1, buffer,qword[cnt2]

;scall 1,qword[fdis],buffer,qword[cnt2]  ;writing to file.txt ==>original array
scall 1,qword[fdis],sortmsg,sortmsg_len  ;writing to file.txt
scall 1,qword[fdis],buffer,qword[cnt2]  ;writing to file2.txt

	;Closing file2
	mov rax,3
	mov rdi,f1name
	syscall
	scall 1,1,closemsg,closemsg_len
EXIT:
	mov rax,60
	mov rdi,0
	syscall
