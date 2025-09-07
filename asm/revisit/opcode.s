; Fichier : interpreter.asm
; Assemble avec : nasm -f elf64 interpreter.asm && ld -o interpreter interpreter.o

section .data
    ; Table d'instructions (opcodes à interpréter)
    program:     db 0x00, 0x02, 0x00, 0x01, 0xFF   ; +1, *2, +1, -1, HALT

    ; Jump table – 256 entrées possibles (indexées par opcode)
    jtable:
        dq op_inc        ; 0x00
        dq op_dec        ; 0x01
        dq op_double     ; 0x02
        times 0xFF - 3 dq unknown_op ; remplir avec handler par défaut
        dq op_halt       ; 0xFF

section .text
    global _start

_start:
    xor rax, rax              ; registre à manipuler
    lea rsi, [rel program]    ; pointeur sur le programme
.loop:
    movzx rdi, byte [rsi]     ; charger opcode actuel (1 byte → rdi)
    add rsi, 1                ; passer au suivant
    cmp rdi, 0xFF
    ja .invalid_opcode        ; au cas où

    jmp [rel jtable + rdi*8]  ; saut indirect via jump table

.invalid_opcode:
    jmp op_unknown            ; fallback pour opcode invalide (ne devrait pas arriver ici)

; === Instructions (handlers) ===

op_inc:
    inc rax
    jmp .loop

op_dec:
    dec rax
    jmp .loop

op_double:
    add rax, rax
    jmp .loop

op_unknown:
    ; traitement d’erreur si opcode non défini
    mov rdi, 1
    mov rsi, err_msg
    mov rdx, err_len
    mov rax, 1
    syscall
    jmp op_halt 

op_halt:
    ; Affiche le résultat final de rax et termine
    ; Pour simplifier, on sort sans impression. On aurait pu utiliser write + itoa otherwise
    mov rax, 60     ; syscall exit
    xor rdi, rdi    ; code de retour
    syscall

section .rodata
    err_msg: db "Unknown opcode encountered", 10
    err_len equ $ - err_msg
