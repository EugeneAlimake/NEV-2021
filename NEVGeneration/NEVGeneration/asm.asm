.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib C:/Users/thesi/Desktop/NEV-2021/NEVlib/Debug/NEVlib.lib

	EXTERN _printS :PROC
	EXTERN _printN :PROC
	EXTERN _pow :PROC
	EXTERN _compare :PROC
	EXTERN _pause :PROC
	ExitProcess PROTO :DWORD

.stack 4096

.const
	L1 BYTE 'C:/Users/thesi/Desktop/NEV-2021/NEVlib/Debug/NEVlib.lib', 0
	L2 BYTE 'The first value is more than the second', 0
	L3 BYTE 'The second value is more than the first', 0
	L4 BYTE 'The first and second value are equal or the second value more', 0
	L5 BYTE 'The first and second value are not equal', 0
	L6 WORD 1
	L7 WORD 2
	L8 BYTE 'Output of values c and a:', 0
	L9 BYTE 'hi', 0
	L10 BYTE 'Hello world', 0
	L11 BYTE 'Output of line str1 and str2:', 0
	L12 BYTE 'lexicographic string comparison str3 and str4:', 0
	L13 BYTE 'hello', 0
	L14 BYTE 'hello ', 0
	L15 BYTE 'accessing the function ~min~:', 0
	L16 BYTE 'accessing the function ~max~:', 0
	L17 BYTE 'accessing the function ~more~:', 0
	L18 WORD 300
	L19 BYTE 'accessing the function ~equal~, when a=111(binary):', 0
	L20 WORD 7
	L21 BYTE 'accessing the function ~equal~, when a!=111(binary) and <111:', 0
	L22 WORD 3
	L23 WORD 0

.data
	minres WORD 0
	maxres WORD 0
	moreres DWORD 0
	eqorminres DWORD 0
	mainstr1 DWORD 0
	mainstr2 DWORD 0
	mainstr3 DWORD 0
	mainstr4 DWORD 0
	maina WORD 0
	mainb WORD 0
	mainc WORD 0
	maind WORD 0
	mainres WORD 0

.code
min PROC mina : WORD, minb : WORD
	mov ax, minb
	cmp ax, mina
	jl p0
	jg p1
	je p1
p0:
	push minb
	pop minres
	jmp ife0
p1:
	push mina
	pop minres
ife0:
	push minres
	pop eax
	ret
min ENDP

max PROC maxa : WORD, maxb : WORD
	mov ax, maxb
	cmp ax, maxa
	jg p2
	jl p3
	je p3
p2:
	push maxb
	pop maxres
	jmp ife1
p3:
	push maxa
	pop maxres
ife1:
	push maxres
	pop eax
	ret
max ENDP

more PROC morea : WORD, moreb : WORD
	mov ax, morea
	cmp ax, moreb
	jg p4
	jl p5
	je p5
p4:
	push offset L2
	pop moreres
	jmp ife2
p5:
	push offset L3
	pop moreres
ife2:
	push moreres
	pop eax
	ret
more ENDP

eqormin PROC eqormina : WORD, eqorminb : WORD
	mov ax, eqormina
	cmp ax, eqorminb
	je p6
	jl p6
	jg p7
p6:
	push offset L4
	pop eqorminres
	jmp ife3
p7:
	push offset L5
	pop eqorminres
ife3:
	push eqorminres
	pop eax
	ret
eqormin ENDP


main PROC
	push L6
	pop mainc
	push L6
	pop eax
	push L7
	pop ebx
	add eax, ebx
	push eax
	pop maina
	movzx ecx, L7
p8:
	push mainc
	pop ebx
	push L6
	pop eax
	sub ebx, eax
	push ebx
	pop mainc
loop p8
	push offset L8
	call _printS
	push mainc
	call _printN
	push maina
	call _printN
	push offset L9
	pop mainstr1
	push offset L10
	pop mainstr2
	push offset L11
	call _printS
	push mainstr1
	call _printS
	push mainstr2
	call _printS
	push offset L12
	call _printS
	push offset L13
	pop mainstr3
	push offset L14
	pop mainstr4
	push mainstr4
	push mainstr3
	call _compare
	push eax
	pop mainres
	mov ax, mainres
	cmp ax, L6
	je p9
	jg p10
	jl p10
p9:
	push offset L15
	call _printS
	movzx eax, mainc
	push eax
	movzx eax, mainb
	push eax
	call min
	push eax
	pop maind
	jmp ife4
p10:
	push offset L16
	call _printS
	movzx eax, mainc
	push eax
	movzx eax, mainb
	push eax
	call max
	push eax
	pop maind
ife4:
	push maind
	call _printN
	push maina
	pop mainb
	mov ax, maina
	cmp ax, mainb
	je p11
	jg p11
	jl p12
p11:
	movzx eax, L7
	push eax
	movzx eax, mainc
	push eax
	call _pow
	push eax
	pop mainb
	push mainb
	call _printN
p12:
	push offset L17
	call _printS
	movzx eax, L18
	push eax
	movzx eax, mainb
	push eax
	call more
	push eax
	pop mainstr1
	push mainstr1
	call _printS
	push offset L19
	call _printS
	push L20
	pop maina
	movzx eax, L20
	push eax
	movzx eax, maina
	push eax
	call eqormin
	push eax
	pop mainstr2
	push mainstr2
	call _printS
	push offset L21
	call _printS
	push L22
	pop maina
	movzx eax, L20
	push eax
	movzx eax, maina
	push eax
	call eqormin
	push eax
	pop mainstr2
	push mainstr2
	call _printS
	push 0
	call _pause
	call ExitProcess
main ENDP
end main