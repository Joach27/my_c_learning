.intel_syntax noprefix
.global str_lower

# -----------------------------
# pwn college
# -----------------------------

str_lower:
    xor rcx, rcx                # i = 0

    test rdi, rdi               # src_addr == NULL ?
    je done

while_loop:
    mov dl, byte ptr [rdi]      # dl = *rdi [str_addr] valeur stockée à l'adresse qui est dans rdi

    test dl, dl                 # fin de chaîne ?
    je done

    cmp dl, 0x5a                # 'Z'
    jg next                     # si > 'Z', on ne traite pas

    push rdi                    # sauver rdi
    xor rdi, rdi                # nettoyer rdi
    mov dil, dl                 # mettre dl en dil (1er argument)
    mov rbx, 0x403000           # mettre l'adresse de la fonction foo dans rbx 
    call rbx                    # appel à foo
    mov dl, al                  # résultat dans dl
    pop rdi                     # restaurer rdi
    mov [rdi], dl               # *rdi = résultat
    inc rcx                     # compteur++

    # on ne saute pas ici !

next:
    inc rdi                     # avancer dans la chaîne
    jmp while_loop

done:
    mov rax, rcx                # retour : nb de modifs
    ret
