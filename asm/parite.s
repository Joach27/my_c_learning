.intel_syntax noprefix
.global _start

.section .data
msg_pair:    .asciz "pair\n"
msg_impair:  .asciz "impair\n"

.section .text

_start:
    # === Entrée ===
    mov rdi, 42          # Choisis ici l'entier x (ex: 42)

    # === Test de parité ===
    and rdi, 1           # rdi = 0 si pair, 1 si impair
    xor rax, rax         # rax = 0
    xor rax, 1           # rax = 1
    xor rax, rdi         # rax = 1 si pair, 0 si impair

    # === Sélection du message à afficher ===
    mov rsi, offset msg_impair
    test rax, rax        # est-ce que rax == 0 ?
    jz afficher          # si oui, c’est impair → msg_impair
    mov rsi, offset msg_pair  # sinon, c’est pair → msg_pair

afficher:
    # write(1, rsi, strlen)
    mov rax, 1           # syscall: write
    mov rdi, 1           # fd = 1 (stdout)
    mov rdx, 5           # longueur du message ("pair\n" ou "impair\n")
    syscall

    # === Quitter le programme ===
    mov rax, 60          # syscall: exit
    xor rdi, rdi         # code de sortie: 0
    syscall
    