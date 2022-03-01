.data

Answer db 1 DUP(0)

.code

; edx -> the offset of the message
; eax -> the decimal number
ReadDecFromUser proc far
    invoke StdOut, edx                  ; Prints the message
    call Downline
    WhileInput:
        invoke StdIn, addr Answer, 1    ; Only a byte  space for this read
        sub Answer, 30h                 ; Convert to decimal
        mov eax, 2                      ; The user can only right 0 or 1
        cmp [Answer], al
        jb GoodInput
        jmp WhileInput                  

    GoodInput:
        mov al, [Answer]                ; Saves the answer to eax
	ret

ReadDecFromUser endp