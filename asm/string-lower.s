.intel_syntax noprefix
.global str_lower

str_lower:
    xor rcx, rcx               # compteur = 0

.loop:
    movzx rax, byte ptr [rdi]  # lire octet
    test rax, rax
    je .done

    cmp rax, 0x41              # 'A'
    jl .skip_call
    cmp rax, 0x5A              # 'Z'
    jg .skip_call

    inc rcx                    # compteur++

    mov rsi, rdi               # sauvegarder l’adresse dans rsi
    mov rdi, rax               # caractère à passer à foo
    call foo
    mov byte ptr [rsi], al     # écrire le résultat
    mov rdi, rsi               # restaurer rdi

.skip_call:
    inc rdi                    # avancer dans la chaîne
    jmp .loop

.done:
    mov rax, rcx
    ret
