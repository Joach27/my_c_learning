.intel_syntax noprefix
.global _start

.section .data
str: .asciz "hello"       # Chaîne terminée par \0

.section .text

# strlen(s) : renvoie la longueur dans rax
strlen:
    xor rax, rax          # rax = 0 (compteur de longueur)
    test rdi, rdi         # vérifie si le pointeur est NULL
    jz .done              # si NULL, retourne 0

.loop:
    cmp byte ptr [rdi + rax], 0  # compare l'octet à l'offset rax avec 0
    je .done                     # si égal à 0, on a trouvé la fin
    inc rax                      # sinon, incrémente le compteur
    jmp .loop                    # et continue

.done:
    ret                          # retourne la longueur dans rax

# Point d'entrée
_start:
  mov rdi, OFFSET FLAT:str

  call strlen             # rax = strlen(rdi)

  mov rdi, rax      # <- assure un code de sortie propre
  mov rax, 60       # syscall exit
  syscall
