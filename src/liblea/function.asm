GLOBAL leaFunctionCallTrampoline
SECTION .text

; leaFunctionCallTrampoline
;
; LeaState*         state
; const void*       cfunc
; const LeaValue*   args
; uint16_t          argCount

leaFunctionCallTrampoline:
    mov rax, rdx
    mov r10, r8
    mov r11, r9

    mov rdx, [r10 + 0x00]
    mov r8,  [r10 + 0x08]
    mov r9,  [r10 + 0x10]

.docall:
    sub rsp, 32
    call rax
    add rsp, 32
    ret
