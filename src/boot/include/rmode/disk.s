; name: disk.s
; desc: Real mode disk routines

; AL <- Sector count
; CL <- Sector number
; DL <- Drive to read
; ES:BX <- Address to read to
; AX -> 0 if success
disk_load:
  pusha

  mov ah, 0x02
  xor ch, ch ; Cyl 0

  xor dh, dh ; Head 0

  int 0x13

  ; jc .error

  .end:
    popa
    xor ax, ax
    ret

  .error:
    popa
    mov ax, 1
ret
