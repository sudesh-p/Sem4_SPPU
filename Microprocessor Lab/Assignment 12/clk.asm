.MODEL TINY
.286
ORG 100H


CODE SEGMENT
     ASSUME CS:CODE,DS:CODE,ES:CODE
        OLD_IP DW 00
        OLD_CS DW 00
JMP INIT

MY_TSR:
        PUSH AX
        PUSH BX
        PUSH CX
        PUSH DX
        PUSH SI
        PUSH DI
        PUSH ES

        MOV AX,0B800H				;Address of Video RAM
        MOV ES,AX
        MOV DI,2000

        MOV AH,02H			;To Get System Clock
        INT 1AH				;CH=Hrs, CL=Mins,DH=Sec 					
        MOV BX,CX

        MOV CL,2
LOOP1:  ROL BH,4
        MOV AL,BH
        AND AL,0FH
        ADD AL,30H
        MOV AH,17H
        MOV ES:[DI],AX
        INC DI
        INC DI
        DEC CL
        JNZ LOOP1

        MOV AL,':'
        MOV AH,97H
        MOV ES:[DI],AX
        INC DI
        INC DI

        MOV CL,2
LOOP2:  ROL BL,4
        MOV AL,BL
        AND AL,0FH
        ADD AL,30H
        MOV AH,17H
        MOV ES:[DI],AX
        INC DI
        INC DI
        DEC CL
        JNZ LOOP2

        MOV AL,':'
        MOV AH,97H
        MOV ES:[DI],AX

        INC DI
        INC DI

        MOV CL,2
        MOV BL,DH

LOOP3:  ROL BL,4
        MOV AL,BL
        AND AL,0FH
        ADD AL,30H
        MOV AH,17H
        MOV ES:[DI],AX
        INC DI
        INC DI
        DEC CL
        JNZ LOOP3

        POP ES
        POP DI
        POP SI
        POP DX
        POP CX
        POP BX
        POP AX

        

INIT:
        MOV AX,CS				;Initialize data
        MOV DS,AX

        CLI				;Clear Interrupt Flag

        MOV AH,35H			;Get Interrupt vector Data address and 								store it
        MOV AL,08H
        INT 21H

        MOV OLD_IP,BX
        MOV OLD_CS,ES

        MOV AH,25H			;Set new Interrupt vector address
        MOV AL,08H
        LEA DX,MY_TSR
        INT 21H

        MOV AH,31H			;Make program Transient
        MOV DX,OFFSET INIT
        STI
        INT 21H

CODE ENDS

END

