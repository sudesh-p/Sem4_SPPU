;==========================================================================================
;=================Bubble Sort Program to sort BYTE numbers from a file=====================
;==========================================================================================
%macro cmn 4
	mov rax,%1
	mov rdi,%2
	mov rsi,%3
	mov rdx,%4
	syscall
%endm

%macro fread 3 
	mov rax,0		;read
	mov rdi,%1		;filehandle
	mov rsi,%2		;buffer
	mov rdx,%3		;buffer length
	syscall
%endm

%macro fopen 1
	mov rax,2		;open
	mov rdi,%1		;filename
	mov rsi,2		;mode R/W
	mov rdx,0777o		;permissions
	syscall
%endm

%macro fwrite 3
	mov rax,1
	mov rdi,%1
	mov rsi,%2
	mov rdx,%3
	syscall
%endm

%macro fclose 1
	mov rax,3
	mov rdi,%1
	syscall
%endm

%macro exit 0
	mov rax,60
	mov rdi,0
	syscall
%endm




;=========================================================
section .data
	
	;Strings to be displayed	
	
	welcome db "WELCOME TO BUBBLE SORT PROGRAM ",0ah
	welcomelen equ $-welcome
	
	dash db "==========================================",0ah
	dashlen equ $-dash	
	
	self db "Vidyabhushan Adhav - COSA 088",0ah
	selflen equ $-self

	errmsg1 db "Source file not found",0ah
	errmsglen1 equ $-errmsg1

	errmsg2 db 0ah,"Destination file not found",0ah
	errmsglen2 equ $-errmsg2
	
	newline db " ",0ah
	newlinelen equ $-newline

	inputmsg1 db "Enter SOURCE FILE name : ",20h
	inputmsglen1 equ $-inputmsg1

	inputmsg2 db "Enter DESTINATION FILE name : ",20h
	inputmsglen2 equ $-inputmsg2

	completee db "CONTENT HAS BEEN SORTED..!!!",0ah
	completeelen equ $-completee

	completee1 db "Check your Destination file",0ah
	completeelen1 equ $-completee1

	errr db "SOMETHING WENT WRONG.!!",0ah
	errrlen equ $-errr

;=========================================================

section .bss

	filename1 resb 20		;source file name
	filename2 resb 20		;destination file name
	
	filehandle resq 1		;file handler
	abuflen resq 1			;Actual buffer length after reading a file
	
	filedata resb 4096		;buffer memory for data of source file
	filedatalen equ $-filedata	;source file buffer length
	filedata2 resb 4096		;for destination file
	filedatalen2 resq 1		;length for destination file
	

	lenn resb 1			;No of elements stored in array

	array resb 20			;Memory for array
	cntr resb 1			;Counter for bubblesort
	cntr2 resb 1			;Counter for bubblesort
	ptr resb 1			;Pointer for bubblesort
	

;===================================================
section .text


;===================================================

global _start
_start:
	
	cmn 1,1,dash,dashlen
	cmn 1,1,welcome,welcomelen		;Prints message
	cmn 1,1,dash,dashlen
	cmn 1,1,self,selflen
	cmn 1,1,dash,dashlen
	cmn 1,1,inputmsg1,inputmsglen1		;Prints message
	cmn 0,0,filename1,20			;Takes file name in filename1
	
	dec al				
	mov byte[filename1+rax],0				;This is for fopen to get exact file name eg.- file1xxxxxxxx

	xor rax,rax				
	fopen filename1						;opens source file

	cmp rax,-1h						;If any exception
	jle fileexception1
	
	mov [filehandle],rax					;acquires file handler

	fread [filehandle],filedata,filedatalen ;		;Reads file with followed parameters
	dec rax							
	mov [abuflen],rax					;Get actual buffer length
	
	fclose [filehandle]					;Closes source file
	call BufferToArray					;call to procedure to convert buffered ascii text to equivalent hex 
								;number and put it into array
	
	call BubbleSort						;calls procedure bubblesort
	
	
	call ArrayToBuffer					;calls procedure to convert sorted hex data into ascii text
	
	
	xor rax,rax
	cmn 1,1,dash,dashlen

	cmn 1,1,inputmsg2,inputmsglen2
	
	cmn 0,0,filename2,20					;Acquires destination file
	
	dec al			
	
	mov byte[filename2+rax],0				;Get exact filename eg. file2xxxxxxx

	fopen filename2						;opens destination file
	
	cmp rax,-1h						;Exception if any eg. File not found
	jle fileexception2
	
	mov [filehandle],rax					;file handler
	
	fwrite [filehandle],filedata2,[filedatalen2]			;Writes content in block filedata2 to destination file
	
	fclose [filehandle]					;Closes destination file

	cmn 1,1,completee,completeelen
	cmn 1,1,completee1,completeelen1
	cmn 1,1,dash,dashlen
	exit							;call to exit
	
	fileexception1:
	cmn 1,1,errmsg1,errmsglen1				;Exception handling block
	
	exit
	fileexception2:
	cmn 1,1,errmsg2,errmsglen2				;Exception handling block
	exit



;======================================Converts File ascii text to hex number==========================================
BufferToArray:
	
	mov dl,00h						
	mov byte[lenn],dl					;set array length to 0
	mov cl,byte[abuflen]					;Gets total no of byte present in source file 
	mov rsi,filedata					;points to memory where data of file is stored i.e filedata
	mov rdi,array						;points to array's starting location

	cont:	
	xor rax,rax
	cont1:
	xor rbx,rbx	
	mov bl,byte[rsi]					;Gets first number in bl register
	cmp bl,20h						; Checks if there is space (space=20h)
	je nextnum						; If yes jumps to nextnum
	cmp bl,0ah						; Checks if there is New Line (newline=0ah)
	je nextnum						; If yes jumps to nextnum
	cmp bl,39h						;Checks if number is below 9
	jbe digit
	sub bl,07h						;If numbers are A,B,C,D,E,F substracts 07 from ascii
	digit:
	sub bl,30h						;Substracts to get hex equivalent
	rol rax,04						;Rotates left bl with 4 bit to get current value in LSB 
	and al,0f0h						;Sets LSB to 0
	add al,bl						;adds al with bl
	inc rsi							;points to next memory
	dec cl							;decrements size of length
	jnz cont1
	nextnum:
	mov byte[rdi],al					;Gets first hex equivalent in array location
	inc rdi							;Increments array Location
	inc byte[lenn]						;Increments length of array
	inc rsi
	cmp cl,00h						;Checks to see if counter is 0
	je stop
	dec cl
	jnz cont
	stop:
	mov word[rdi],0ffffh					; Sets array+1 to ff so that if (FF) is compared then it will be swapped
								; FF itself
	ret

;======================================Bubble sort Logic applied on array memory block==========================================
BubbleSort:
	
	mov rdi,array						;pointer to starting of array
	mov byte[ptr],00h					; set this variable to 00
	mov cl,byte[lenn]					;set cl with array length
	mov byte[cntr],cl					;set this variable with array length
	
	up1 :
	mov rdi,array						;Points to start
	mov al,byte[cntr]					;
	mov bl,byte[ptr]
	sub al,bl						; n-i (Rather to increase i, Decrements n)
	mov byte[cntr2],al					; j pointer in bubble sort
	up2:
		mov al,byte[rdi]				;Get [j] in al
		mov bl,byte[rdi+1]				;Get [j+1]in bl
		cmp al,bl
		jb skip						;Compares
		mov [rdi+1],al					;If larger swapped
		mov [rdi],bl
		skip:
		   inc rdi					;Else continues to next number
		   dec byte[cntr2]
		   jnz up2
			
	dec byte[cntr]						;Decrements n (Rather to increase i)
	jnz up1
	ret


;======================================Converts sorted hext number to ascii text==========================================
ArrayToBuffer:
	

	mov rsi,filedata2					;Points to memory for file2
	mov cl,byte[lenn]					;gets total no array in cl
	mov dh,00h						
	mov rdi,array						;Pointer to array

	nextnumber:
	xor rax,rax						;Set rax=0
	mov dl,02h						;Counter to how many time to rotate left
	mov al,byte[rdi]					;Gets 1st no in al
	currentnum:
	xor ah,ah						;Sets ah to 00
	rol rax,04						;rotates left rax to 4 bit	
	cmp ah,09h						;checks if nibble came from al to ah a digit or not
	jbe dig
	add ah,07h						;If Letters adds 7
	dig:
	add ah,30h						;Add 30 to convert to ascii
	mov byte[rsi],ah					;Stores this value to destination file data memory
	inc rsi							;increments memory location of destination file
	inc dh							
	dec dl							;Decrement for next nibble
	jnz currentnum
	
	mov byte[rsi],20h					;If first number in array completly converted to hex then adds space _
	inc rsi							;Increments pointer
	inc rdi
	inc dh
	dec cl
	jnz nextnumber
	mov byte[filedatalen2],dh				;Moves total number of bytes to written
	ret
	
	
	
	
	







	







	












