.data?
RandSeed dd ?

.code

; Choose random card
RandomCard proc far
	NeedToChooseCard:
		call RandomDeck
		call RandomIndex
		add ebx, esi
	xor eax, eax
	cmp [ebx], eax			; Chekcs if this card is not alrealy selected
	je NeedToChooseCard
	mov edx, [ebx]
	xor eax, eax
	mov [ebx], eax			; Mov 0 to the card slot. It has been selected
	ret
RandomCard endp

; ebx -> random offset of a deck
RandomDeck proc far
	mov ebp, esp
	push 4							; Generate random between 0-3
	call RandomBetweenTwoNumbers
	cmp esi, 0
	je else1
		cmp esi, 1
		je else2
			cmp esi, 2
			je else3
				cmp esi, 3
				je else4
				jmp Done

				else4:
					mov ebx, offset Spades
					jmp Done

			else3:
				mov ebx, offset Hearts
				jmp Done

		else2:
			mov ebx, offset Diamonds
			jmp Done

	else1:
		mov ebx, offset Clubs	

	Done:

	mov esp, ebp
	ret
RandomDeck endp

; esi -> random index
RandomIndex proc far
	mov ebp, esp
	push 13
	call RandomBetweenTwoNumbers
	mov eax, JUMP
	mul esi
	mov esi, eax
	mov esp, ebp
	ret
RandomIndex endp


; push number
; esi -> random between 0, number-1
RandomBetweenTwoNumbers proc far
	push ebp
	mov ebp, esp
	push eax
	mov eax, [ebp+FIRSTP]
	push  edx                         ; Preserve EDX
    imul  edx,RandSeed,08088405H      ; EDX = RandSeed * 0x08088405 (decimal 134775813)
    inc   edx
    mov   RandSeed, edx               ; New RandSeed
    mul   edx                         ; EDX:EAX = EAX * EDX
    mov   esi, edx                    ; Return the EDX from the multiplication to esi
    pop   edx
	pop eax
	pop ebp
	ret RETP
RandomBetweenTwoNumbers endp
