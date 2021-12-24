.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ../../NEVlib/Debug/NEVlib.lib

	EXTERN _printS :PROC
	EXTERN _printN :PROC
	EXTERN _pow :PROC
	EXTERN _compare :PROC
	EXTERN _pause :PROC
	ExitProcess PROTO :DWORD

.stack 4096

.const
	L1 BYTE '../../NEVlib/Debug/NEVlib.lib', 0
	L2 BYTE 'First argument more than second', 0
	L3 BYTE 'Second argument more than first', 0
	L4 BYTE 'First argument more than second', 0
	L5 BYTE 'Second argument more than first', 0
	L6 WORD 3
	L7 WORD 73
	L8 BYTE 'Hello world', 0
	L9 BYTE 'Hello world', 0
	L10 WORD 1
	L11 BYTE 'strings are  equal', 0
	L12 BYTE 'strings are not equal', 0
	L13 WORD 2
	L14 WORD 300
	L15 WORD 7
	L16 WORD 0

.data
	minres WORD 0
	moreres DWORD 0
	pukres DWORD 0
	mainstr1 DWORD 0
	mainstr2 DWORD 0
	maina WORD 0
	mainb WORD 0
	mainc WORD 0
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

more PROC morea : WORD, moreb : WORD
	mov ax, morea
	cmp ax, moreb
	jg p2
	jl p3
	je p3
p2:
	push offset L2
	pop moreres
	jmp ife1
p3:
	push offset L3
	pop moreres
ife1:
	push moreres
	pop eax
	ret
more ENDP

puk PROC puka : WORD, pukb : WORD
	mov ax, puka
	cmp ax, pukb
	je p4
	jl p4
	jg p5
p4:
	push offset L4
	pop pukres
	jmp ife2
p5:
	push offset L5
	pop pukres
ife2:
	push pukres
	pop eax
	ret
puk ENDP


main PROC
	push L6
	pop mainb
	push L7
	pop mainc
	push offset L8
	pop mainstr1
	push offset L9
	pop mainstr2
	push mainstr2
	push mainstr1
	call _compare
	push eax
	pop mainres
	mov ax, mainres
	cmp ax, L10
	je p6
	jg p7
	jl p7
p6:
	push offset L11
	call _printS
	movzx eax, mainc
	push eax
	movzx eax, mainb
	push eax
	call min
	push eax
	pop maina
	jmp ife3
p7:
	push offset L12
	call _printS
ife3:
	mov ax, maina
	cmp ax, mainb
	je p8
	jg p8
	jl p9
p8:
	movzx eax, L13
	push eax
	movzx eax, mainc
	push eax
	call _pow
	push eax
	pop mainb
	push mainb
	call _printN
p9:
	movzx eax, L14
	push eax
	movzx eax, mainb
	push eax
	call more
	push eax
	pop mainstr1
	movzx eax, L15
	push eax
	movzx eax, maina
	push eax
	call puk
	push eax
	pop mainstr2
	push maina
	call _printN
	push mainstr1
	call _printS
	push mainstr2
	call _printS
	push 0
	call _pause
	call ExitProcess
main ENDP
end main