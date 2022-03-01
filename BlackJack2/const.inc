.const
MAXMEMORY equ 12		; Worst case: 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3
						;				   4	+	   8	+	   9   = 21
						; If any other cards will be add, it will pass the 21 and Game Over

; Card
FIRSTNUMBER equ 1
CARDSINDECK equ 13


; Stack frame jumps
FIRSTP equ 12
JUMP equ 4
RETP equ 2

; Messages
HITORSTANDPLAYER BYTE "Hit(0) or stand(1)", 0
PLAYAGAIN BYTE "Play again? yes(0) / no(1)", 0

YOULOSE BYTE "You lose!", 0
YOUWIN BYTE "You Win!!!", 0

DEALERHAS BYTE "Dealer has: ", 0
DEALERHAS2 BYTE ", ?", 0

YOUHAVE1 BYTE "You have: ", 0
YOUHAVE2 BYTE ", ", 0
SUM BYTE "sum=", 0