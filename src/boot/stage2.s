; name: stage2.s
; desc: Responsible for setting up protected mode

[BITS 16]
[ORG 0x7E00] ; Right after the boot sector

; Globals
BOOT_DRIVE db 0x0

jmp stage2

stage2:
  mov si, 0 ; Weird duplicated string bug fix

  pusha
  mov ah, 0x01
  mov cx, 0x2607 ; Hidden cursor
  int 0x10
  popa

  mov si, STR_LOADED_STAGE_2
  call rm_print

  mov [BOOT_DRIVE], dl ; Save boot drive number

  ; Check if A20 is enabled
  call check_a20
  test ax, ax
  jnz .a20_enabled

  ; Try enabling through BIOS
  mov ax, 0x2401
  int 0x15

  ; Check if successful
  call check_a20
  test ax, ax
  jnz .a20_enabled

  ; Try enabling through FAST A20
  mov si, STR_FAST_A20_TRY
  call rm_print

  in al, 0x02
  or al, 2
  out 0x92, al

  ; Check if successful
  call check_a20
  test ax, ax
  jnz .a20_enabled

  .a20_error:
    mov si, STR_A20_FAIL
    call rm_print

    ; Do not continue
    cli
    hlt

  .a20_enabled:
    mov si, STR_A20_ENABLED
    call rm_print


  ; Load kernel
  mov si, STR_KERNEL_LOAD
  call rm_print

  ; PAY ATTENTION TO SECTORS IN CASE KERNEL GROWS TOO BIG!!!
  mov al, 8
  mov cl, 4 ; If stage2 grows, this must change
  mov dl, [BOOT_DRIVE]

  ; Load kernel at 0x10000
  mov bx, 0x1000
  mov es, bx
  xor bx, bx
  call disk_load

  ; Use BIOS to switch video mode
  xor ah, ah
  mov al, 0x13
  int 0x10

  ; Switch to pmode
  ; mov si, STR_PMODE_TRY
  ; call rm_print

  cli
  lgdt [gdt_descriptor]

  ; Setting bit 0 of cr0 officially switches us to pmode
  mov eax, cr0
  or eax, 1
  mov cr0, eax

  ; Far jump to clear instruction pipeline
  jmp CODE_SEG:init_pm

[BITS 32]
init_pm:
  ; Populate segment registers with new data
  mov ax, DATA_SEG
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  ; Move stack out of the way
  mov ebp, 0x90000
  mov esp, ebp

  ; Jump to kernel previously loaded
  call 0x10000
  hlt

; Includes
%include "rmode/scrio.s"
%include "rmode/disk.s"
%include "rmode/a20.s"

%include "pmode/gdt.s"

; Constants
STR_LOADED_STAGE_2 db `[INFO]  Loaded stage2 successfully\r\n`, 0
STR_A20_ENABLED    db `[INFO]  A20 Gate is enabled\r\n`, 0
STR_FAST_A20_TRY   db `[INFO]  Attempting to use FAST A20\r\n`, 0
STR_A20_FAIL       db `[ERROR] A20 Gate could not be enabled\r\n`, 0
STR_KERNEL_LOAD    db `[INFO]  Loading kernel at 0x10000\r\n`, 0
STR_PMODE_TRY      db `[INFO]  Switching to protected mode\r\n`, 0

; stage2 1KB padding
times 1024 - ($ - $$) db 0
