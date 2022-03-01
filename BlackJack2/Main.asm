.586
.model flat,stdcall
option casemap:none

include \masm32\include\masm32rt.inc

include const.inc
include random.inc
include reset.inc
include printGame.inc
include readFromUser.inc
include clearConsole.inc
include card.inc
include clearConsole.inc


.data
Clubs dword 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
Diamonds dword 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
Hearts dword 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
Spades dword 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
;			 0, 4, 8, 12,16,20,24,28,32,36, 40, 44, 48 

DealerCards dword MAXMEMORY dup(0)
PlayerCards dword MAXMEMORY dup(0)

.code

Downline proc 
    print (cfm$("\n"))
    ret
Downline endp

ChooseDealerFirstCards proc
    mov ebx, offset DealerCards
	call ChooseCardAndSave
	call ChooseCardAndSave
	call PrintDealerCardsFirst
    ret
ChooseDealerFirstCards endp

ChoosePlayerFirstCards proc
    mov ebx, offset PlayerCards
    call ChooseCardAndSave
    ret
ChoosePlayerFirstCards endp

ChooseDealerLastCards proc ; When the player is standing, the dealer has to take cards until he has 17 or more
	mov ebx, offset DealerCards
	
	AddCard:
		push ebx 
		call SumCards
		pop ebx 
		cmp eax, 17
		jae DoneWithChoosing
		push ebx 
		call ChooseCardAndSave
		pop ebx 
		jmp AddCard


    DoneWithChoosing:
        call PrintDealerCardsLast

	ret
ChooseDealerLastCards endp

CheckWinner proc
    push eax ; push sum of dealer cards
    mov ebx, offset PlayerCards
    call SumCards ; puts in eax the sum of the player cards
    pop ecx ; pop to ecx the sum of dealer cards
    cmp eax, ecx ; dealer / player sum
    ret
CheckWinner endp

DoneGame proc
    call Downline
    call Downline
    invoke StdOut, addr PLAYAGAIN
    call ReadDecFromUser
    cmp eax, 1                      ; 0-play again
    ret
DoneGame endp

start:
	rdtsc
	mov [RandSeed], eax
	call ChooseDealerFirstCards
    call ChoosePlayerFirstCards


    ChooseCardsForPlayer:
        call ChooseCardAndSave
        call PrintPlayersCards              ; eax = sum of player's cards
        cmp eax, 21                         ; Checks if the player went over 21. If yes he loses.
        ja Lose

	HitStand:
        mov edx, offset HITORSTANDPLAYER
        call ReadDecFromUser                ; Saves in eax
        cmp eax, 0                          ; 0-hit, 1-stand
        jne DonePlayerGame                  ; Stand
        mov ebx, offset PlayerCards         ; Hit
        jmp ChooseCardsForPlayer


    DonePlayerGame:
        call ChooseDealerLastCards
        cmp eax, 21
        ja Win
        call CheckWinner
        jae Win
        jmp Lose

    Lose:
        invoke StdOut, addr YOULOSE
        jmp DoneGameL
    Win:
        invoke StdOut, addr YOUWIN
        jmp DoneGameL

    DoneGameL:
        call DoneGame
        je Finish
        ClearConsole                    ; Play again
        call Reset
        jmp start

    Finish:
    invoke ExitProcess,0

end start