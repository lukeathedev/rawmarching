; name: scrio.s
; desc: Screen I/O routines for real mode

[BITS 16]

; BH <- Screen color: 4 MSB -> BG, 4 LSB -> FG
; https://en.wikipedia.org/wiki/BIOS_color_attributes
rm_clear:
  pusha

  ; Set cursor to 0,0
  mov ah, 0x02

  push bx
  xor bh, bh
  xor dx, dx

  int 0x10
  pop bx

  ; Clear screen
  mov ah, 0x06
  xor al, al

  xor cx, cx
  mov dx, 0xFFFF

  int 0x10

  popa
ret

; SI <- Null-terminated string address
rm_print:
  pusha

  .next:
    mov al, [si]
    inc si

    test al, al
    jz .end

    call rm_putchar
    jmp .next

  .end:
    popa
ret

; AL <- Character to print
rm_putchar:
  pusha

  mov ah, 0x0E
  xor bx, bx

  int 0x10

  popa
ret

; DX <- Hex value
rm_print_hex:
  pusha

  mov al, '0'
  call rm_putchar
  mov al, 'x'
  call rm_putchar

  mov cx, 4

  .next:
    mov bx, dx

    push cx
    dec cx
    .shift:
      test cx, cx
      jz .shift_end

      shr bx, 4
      dec cx

      jmp .shift
    .shift_end:

    pop cx
    and bx, 0xF

    mov si, STR_HEX_CHARS
    add si, bx
    mov al, [si]
    call rm_putchar

    dec cx

    test cx, cx
    jz .end

    jmp .next

  .end:
    popa
ret

; Constants
STR_HEX_CHARS db `0123456789ABCDEF`, 0
