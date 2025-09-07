.intel_syntax noprefix
.global _start

.section .data
msg_pair:    .asciz "pair\n"
msg_impair:  .asciz "impair\n"

.section .text

_start:
    # === récupérer argv[1] ===
    mov rsi, [rsp + 16]    # argv[1] (rsp + 8 = argc, rsp + 16 = argv[0], +24 = argv[1])
    # rsi ← pointeur vers la chaîne d’argument

    # === convertir la chaîne ASCII en entier ===
    xor rdi, rdi           # rdi = 0 → valeur accumulée

atoi_loop:
    mov al, byte ptr [rsi] # lire le caractère
    cmp al, 0              # fin de chaîne ?
    je check_parity
    sub al, '0'            # convertir ASCII → chiffre
    imul rdi, rdi, 10      # rdi *= 10
    add rdi, rax           # rdi += chiffre
    inc rsi                # avancer
    jmp atoi_loop

check_parity:
    # === tester parité comme avant ===
    and rdi, 1           # rdi = 0 si pair, 1 si impair
    xor rax, rax
    xor rax, 1
    xor rax, rdi         # rax = 1 si pair, 0 si impair

    # === choisir le message ===
    mov rsi, offset msg_impair
    test rax, rax
    jz afficher
    mov rsi, offset msg_pair

afficher:
    # write(1, rsi, 5)
    mov rax, 1           # syscall: write
    mov rdi, 1           # fd = stdout
    mov rdx, 5           # longueur du message
    syscall

    # exit(0)
    mov rax, 60
    xor rdi, rdi
    syscall
