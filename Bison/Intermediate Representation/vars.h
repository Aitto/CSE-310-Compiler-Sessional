
string pDec=R"(SHOW PROC
     push ax
     push bx
     push cx
     push dx

    ;PRINT ARRAY NUMBERS
    ;TELEMENTS CONTAINS TOTAL ELEMENTS 
    ;TEMP CONTAINS VARIABLE TEMPORARILLY
    ;INITIALIZING INDEX TO ITERATE ARRAY FROM ZERO TO TOP
    
    MOV CX,0
    PRINT_NUM:
        MOV FLAG,0      ;INITIALIZING FLAG VARIABLE
        MOV AX,printVar
        
        CMP AX,0
        JGE GO3         ;CHECKING FOR NEGATIVE NUMBER
        NEG AX
        MOV FLAG,1      ;TRACKING IF NUMBER IS NEGATIVE
        
        GO3:
        MOV DX,0
        MOV DIGITS,0    ;COUNTING HOW MANY DIGITS IN THE NUMBER
        
        PUSH CX
        
        WHILE:
            
            MOV BX,10
            
            DIV BX
            
            ;MOV TEMP,AX
            ;MOV AH,2
            ;ADD DL,30H
            ;INT 21H
            PUSH DX
            
            ;MOV AX,TEMP
            INC DIGITS
            MOV DX,0 
            CMP AX,0
            JE END_WHILE
            JMP WHILE
            
        END_WHILE:
        
        ;MOV TEMP, CX
        
        MOV CX,DIGITS
        MOV AH,2
        CMP FLAG,1
        JNE PWHILE
        MOV DL,'-'
        INT 21H
        
        PWHILE:
            POP DX
            ADD DL,30H
            INT 21H
        
        LOOP PWHILE:  
        
        POP CX

        mov ah,2
        mov dl,0dh
        int 21h
        mov dl,0ah
        int 21h

        pop ax
        pop bx
        pop cx
        pop dx
    
RET
SHOW ENDP
)";

string printInit=R"(printVar dw ?  
    FLAG DW ?
    DIGITS DW ?
)";