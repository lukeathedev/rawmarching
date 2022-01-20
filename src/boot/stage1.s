; name: stage1.s
; desc: Responsible for loading stage2.s

[BITS 16]
[ORG 0x7C00]

jmp main

main:
  mov bh, 0b00000111 ; Light gray on black
  call rm_clear

  mov si, STR_LOADING_STAGE_2
  call rm_print

  ; https://en.wikipedia.org/wiki/INT_13H#INT_13h_AH=02h:_Read_Sectors_From_Drive
  xor ax, ax
  mov ds, ax
  cld

  ; TODO: use disk_load routine

  mov ah, 0x02
  mov al, 63   ; 63 Sectors
  mov ch, 0x00 ; Cylinder 0
  mov cl, 0x02 ; Sector 2
  mov dh, 0x00 ; Head 0

  xor bx, bx
  mov es, bx     ; Segment 0
  mov bx, 0x7E00 ; Offset 0x7E00

  int 0x13

  ; TODO: Error checking

  jmp 0x7E00 ; Jump to sector

; Includes
%include "rmode/scrio.s"

; Constants
STR_LOADING_STAGE_2 db `[INFO]  Loading stage2 at 0x7E00\r\n`, 0

times 510 - ($ - $$) db 0
dw 0xAA55
