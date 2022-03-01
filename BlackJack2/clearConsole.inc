ClearConsole MACRO c$:=<32>
  push esi
  push ecx
  invoke GetStdHandle, STD_OUTPUT_HANDLE
  xchg eax, esi
  sub esp, CONSOLE_SCREEN_BUFFER_INFO
  invoke GetConsoleScreenBufferInfo, esi, esp
  if 0
	pop ax	; One byte longer
	pop dx
	cwde
	mul dx
  else
	pop eax
	cwde
	mul word ptr [esp-2]
  endif
  invoke FillConsoleOutputCharacter, esi, c$, eax, 0, esp
  invoke SetConsoleCursorPosition, esi, 0
  pop edx
  add esp, CONSOLE_SCREEN_BUFFER_INFO-8
  pop ecx
  pop esi
ENDM