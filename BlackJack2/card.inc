.code

; ebx -> the offset of the cards
; Save a random card
ChooseCardAndSave proc far
	push ebx
    call RandomCard
    pop ebx
	call SaveToLast
	ret
ChooseCardAndSave endp

; ebx -> the offset of the cards
; edx -> card value you want to add
SaveToLast proc far
	xor eax, eax
	sub ebx, 4
	loop1:
		add ebx, 4
	cmp [ebx], eax ; Chekcs for an empty spot in the array
	jne loop1
	mov [ebx], edx
	ret
SaveToLast endp

; ebx -> the offset of the cards
; eax -> the sum of all cards
SumCards proc far
	xor eax, eax
	mov ecx, MAXMEMORY
	loop1:
		add eax, [ebx]
		add ebx, JUMP
	loop loop1
	ret
SumCards endp 
