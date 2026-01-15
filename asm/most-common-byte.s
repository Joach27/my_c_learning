.intel_syntax noprefix
.global most_common_byte

most_common_byte:
    push rbp                       # Sauvegarder l'ancien rbp
    mov rbp, rsp                   # Créer la nouvelle base de pile (stack frame)
    sub rsp, 512                   # Allouer 512 octets (256 * 2) pour les compteurs sur la pile

    # -----------------------------------------
    # Phase 1 : Initialiser tous les compteurs à 0
    # -----------------------------------------
    xor rcx, rcx                   # rcx = 0 (index de boucle)

zero_loop:
    cmp rcx, 512                   # Si rcx >= 512 (256 * 2), on a fini d'initialiser
    jge count_loop_start

    mov ax, 0                      # AX = 0 (valeur 16 bits à écrire)
    mov [rbp + rcx - 512], ax      # Écrire 0 à l'offset courant (compteur = 0)

    add rcx, 2                     # rcx += 2 (chaque compteur est un mot de 2 octets)
    jmp zero_loop

# -----------------------------------------
# Phase 2 : Compter la fréquence de chaque octet
# -----------------------------------------
count_loop_start:
    xor rcx, rcx                   # rcx = i = 0 (index du tableau source)

count_loop:
    cmp rcx, rsi                   # si i >= size, fin de boucle
    jge find_max_init

    movzx r8, byte ptr [rdi + rcx]    # r8 = src[i] (octet courant)
    mov r9, r8                         # r9 = curr_byte
    shl r9, 1                          # r9 = curr_byte * 2 (chaque compteur fait 2 octets)

    movzx r10, word ptr [rbp + r9 - 512]  # r10 = compteur[curr_byte] # Accès au compteur pour l'octet courant : base du tableau (rbp - 512) + offset (curr_byte * 2)
    add r10, 1                             # incrémenter le compteur
    mov ax, r10w                           # mettre la partie basse dans AX
    mov [rbp + r9 - 512], ax               # stocker compteur mis à jour

    inc rcx                            # i += 1
    jmp count_loop

# -----------------------------------------
# Phase 3 : Trouver l'octet le plus fréquent
# -----------------------------------------
find_max_init:
    xor rbx, rbx                   # rbx = b = 0 (byte qu'on teste)
    xor rcx, rcx                   # rcx = max_freq = 0
    xor rax, rax                   # rax = max_freq_byte = 0

find_max_loop:
    cmp rbx, 256                   # si b > 255, fin de boucle
    jge end_function

    mov r8, rbx                    # r8 = b
    shl r8, 1                      # r8 = b * 2 (offset pour accéder au compteur)

    movzx r9, word ptr [rbp + r8 - 512]   # r9 = compteur[b]

    cmp r9, rcx                    # si compteur[b] > max_freq
    jle skip_update                # sinon on saute

    mov rcx, r9                    # max_freq = compteur[b]
    mov rax, rbx                   # max_freq_byte = b

skip_update:
    inc rbx                        # b += 1
    jmp find_max_loop

# -----------------------------------------
# Fin : restaurer la stack et retourner max_freq_byte
# -----------------------------------------
end_function:
    mov rsp, rbp                  # Restaurer le pointeur de pile
    pop rbp                       # Restaurer l'ancien rbp
    ret                           # Retourner max_freq_byte dans rax
