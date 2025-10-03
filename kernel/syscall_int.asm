[bits 32]
[extern syscall_handler]

global syscall_int
syscall_int:
    cli
    push byte 0
    push byte 128
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ; Debug: Write directly to video memory
    mov edi, 0xB8000
    mov esi, debug_msg
    mov ah, 0x07 ; White on black
.loop:
    lodsb
    cmp al, 0
    je .done
    mov [edi], ax
    add edi, 2
    jmp .loop
.done:
    push esp
    call syscall_handler
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    sti
    iret

section .data
debug_msg: db "Debug: syscall_int reached", 0

section .note.GNU-stack noalloc noexec nowrite progbits