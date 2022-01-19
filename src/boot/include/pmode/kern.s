[BITS 32]

mov edx, 0xb8000
mov al, 'X'
mov ah, 0b00000110
mov [edx], ax

jmp $
