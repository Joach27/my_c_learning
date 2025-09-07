section .data
msg_zero db "Le nombre est zero", 10   # Message pour zéro
msg_pos db "Le nombre est positif", 10 # Message pour positif
msg_neg db "Le nombre est negatif", 10 # Message pour négatif

section .text
global _start

_start:
    # Initialisation de eax avec une valeur exemple
    mov eax, 5         # Remplacer par -5, 0, ou tout autre nombre pour tester
    
    cmp eax, 0         # Compare eax à 0
    je  zero           # Si eax == 0, saute à "zero"
    jl  negatif        # Si eax < 0, saute à "negatif"
    jg  positif        # Si eax > 0, saute à "positif"

zero:
    # Code pour le cas où eax == 0
    mov rdi, msg_zero  # Préparer le message
    call afficher_message
    jmp fin             # Saute à la fin

positif:
    # Code pour le cas où eax > 0
    mov rdi, msg_pos   # Préparer le message
    call afficher_message
    jmp fin             # Saute à la fin

negatif:
    # Code pour le cas où eax < 0
    mov rdi, msg_neg   # Préparer le message
    call afficher_message
    jmp fin             # Saute à la fin

afficher_message:
    # Affiche le message pointé par rdi (paramètre passé à la fonction)
    mov rax, 1         # Code système pour écrire
    mov rsi, rdi       # Le message à afficher
    mov rdx, 22        # Longueur du message (ajustez en fonction de la taille du message)
    syscall            # Appel système pour afficher
    ret                # Retour de la fonction

fin:
    # Sortie propre du programme
    mov rax, 60        # Code de sortie du programme
    xor rdi, rdi       # Code de sortie 0
    syscall            # Appel système pour terminer
