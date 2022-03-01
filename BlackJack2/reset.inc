.code

Reset proc far
	mov ebx, offset PlayerCards
	call ResetCards
	mov ebx, offset DealerCards
	call ResetCards
	call resetAllDecks
	ret
Reset endp

; ebx -> the cards that needs to be reset
ResetCards proc far
	xor eax, eax
	WhileCardNotZero:
		mov [ebx], eax
		add ebx, JUMP
	cmp [ebx], eax
	jne WhileCardNotZero
	ret
ResetCards endp


; Reset the decks after the game is over
resetAllDecks proc far
	mov ebx, offset Clubs
	call resetDeck
	mov ebx, offset Diamonds
	call resetDeck
	mov ebx, offset Hearts
	call resetDeck
	mov ebx, offset Spades
	call resetDeck
	ret
resetAllDecks endp

; ebx -> offset of a deck
; Reset single deck
resetDeck proc far
	mov eax, FIRSTNUMBER
	mov ecx, CARDSINDECK
	mov esi, ebx
	resLoop:
		mov [esi], eax

		add esi, JUMP
		inc eax
	loop resLoop
	ret
resetDeck endp