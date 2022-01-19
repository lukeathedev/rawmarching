; name: gdt.s
; desc: Defines the Global Descriptor Table necessary
; for Protected (32-bit) mode

; This is a very simple GDT that just werks

gdt_start: ; Each section has a quadword
  gdt_null: ; Mandatory null descriptor
    dd 0x0
    dd 0x0

  gdt_code: ; Code segment
    dw 0xFFFF ; Limit (0-15)
    dw 0x0    ; Base (0-15)
    db 0x0    ; Base (16-23)
    db 0b10011010 ; Flags
    db 0b11001111 ; Flags + Limit (16-19)
    db 0x0    ; Base (24-31)

  gdt_data: ; Data segment
    dw 0xFFFF ; Limit (0-15)
    dw 0x0    ; Base (0-15)
    db 0x0    ; Base (16-23)
    db 0b10010010 ; Flags
    db 0b11001111 ; Flags + Limit (16-19)
    db 0x0    ; Base (24-31)

  gdt_end: ; To calculate descriptor size

gdt_descriptor: ; This is what the CPU uses to determine GDT
  dw gdt_end - gdt_start - 1 ; Size
  dd gdt_start               ; Address

NULL_SEG equ gdt_null - gdt_start ; 0x00
CODE_SEG equ gdt_code - gdt_start ; 0x08
DATA_SEG equ gdt_data - gdt_start ; 0x10
