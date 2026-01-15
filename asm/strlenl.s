.intel_syntax noprefix
.global strlenl

strlenl:
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