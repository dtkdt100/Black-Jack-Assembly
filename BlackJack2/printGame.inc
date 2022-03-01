.code

; Displays the first card of the dealer
PrintDealerCardsFirst proc far
	invoke StdOut, addr DEALERHAS		; Print dealer has:
	mov ebx, offset DealerCards
	mov eax, [ebx]
	printf ("%u", eax)					; Print the fisrt card (the second card is hidden)
	invoke StdOut, addr DEALERHAS2		; Print "?" because ^^^
	call Downline
	ret
PrintDealerCardsFirst endp

; Prints the dealer
PrintDealerCardsLast proc far
	mov ebx, offset DealerCards
	mov edx, offset DEALERHAS
	call PrintCards
	ret
PrintDealerCardsLast endp


PrintPlayersCards proc far
	mov ebx, offset PlayerCards
	mov edx, offset YOUHAVE1
	call PrintCards
	ret
PrintPlayersCards endp

; ebx -> the offset of the cards
; edx -> the offset of the message
PrintCards proc far 
    invoke StdOut, edx
	push ebx
	WhileHasCards:
		mov eax, [ebx]
		printf ("%u", eax)	
		invoke StdOut, addr YOUHAVE2
		add ebx, JUMP
	xor eax, eax
	cmp [ebx], eax
	jne WhileHasCards
	pop ebx
	call PrintSum
	ret	
PrintCards endp

; ebx -> the offset of the cards
PrintSum proc far
	invoke StdOut, ADDR SUM
	call SumCards
	push eax
	printf ("%u", eax)
	call Downline
	pop eax
	ret
PrintSum endp
